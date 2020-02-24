#!/bin/bash

echo "--- [ANALYSING COREWAR] ---";

# Colors
RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
MAGENTA='\033[1;35m'
UNDERLINE='\033[4m'
NC='\033[0m'

CYCLES=0;
PROBLEM=0;
CHAMPIONS=0;
ORDER=1;
TIMEOUT=10;
OPT_A="";
OPT_V="";
OPT_O="";
FIGHT=1;

get_problem()
{
	PROBLEM=$(( $PROBLEM + 2));
	printf "${RED} PROBLEM ON CYCLE ${NC}\n" >> trace;
	./originals/corewar -a -d $PROBLEM -v 6$ARG $FILE/$CHAMPION > original;
	$COREWAR -dump $PROBLEM -v 6$ARG $FILE/$CHAMPION > our;
#	THIS=$( echo "$PROBLEM" )
#	cat original | grep -w "$THIS" -B 15 -A 100 > original1;
#	cat our | grep -w "$THIS" -B 15 -A 100 > our1;
#	printf "${RED} ______ORIGINAL______ ${NC}\n" >> trace;
#	cat original1 >> trace;
#	printf "${RED} ______OUR___________ ${NC}\n" >> trace;
#	cat our1 >> trace;
	diff original our >> trace;
}	
	
thorough_check()
{
	if [ $CYCLES -lt "100" ]
	then	
		CYCLES=0;	
		PROBLEM=100;
	else
		CYCLES=$(( $CYCLES - 100))
	fi;
	printf "${RED} PROBLEM IN BETWEEN $CYCLES AND $PROBLEM ${NC}\n"
	echo "--- [HIGH DETAIL DIFF TEST] ---";
	while [ $CYCLES -lt $PROBLEM ];
	do
		./originals/corewar -d $CYCLES $OPT_A$ARG $FILE/$CHAMPION > original;
		$COREWAR -dump $CYCLES $OPT_O$ARG $FILE/$CHAMPION > our;
		diff original our > file;
	WORDCOUNT=$(cat file | wc -l);
	if [ $WORDCOUNT = "0" ]
	then
		printf "${GREEN}▓${NC}";
		CYCLES=$(( $CYCLES + 1));
	else
		printf "${RED}▓${NC}";
		PROBLEM=$CYCLES;
	fi;
	done;
	printf "${RED} PROBLEM ON CYCLE $PROBLEM ${NC}\n"
	
}

detail_check()
{
	if [ $CYCLES -lt "2500" ]
	then	
		CYCLES=0;
		PROBLEM=2500;
	else
		CYCLES=$(( $CYCLES - 2500))
	fi;
	printf "${RED} PROBLEM IN BETWEEN $CYCLES AND $PROBLEM ${NC}\n"
	while [ $CYCLES -lt $PROBLEM ];
	do
		./originals/corewar -d $CYCLES $OPT_A$ARG $FILE/$CHAMPION > original;
		$COREWAR -dump $CYCLES $OPT_O$ARG $FILE/$CHAMPION > our;
		diff original our > file;
	WORDCOUNT=$(cat file | wc -l);
	if [ $WORDCOUNT = "0" ]
	then
		printf "${GREEN}▓${NC}";
		CYCLES=$(( $CYCLES + 100));
	else
		printf "${RED}▓${NC}";
		PROBLEM=$CYCLES;
	fi;
	done;
}

primary_check()
{
	echo "--- [DETAILED DIFF TEST] ---";
	PROBLEM=0;
	while [ $CYCLES -lt "50000" ];
	do
		./originals/corewar -d $CYCLES $OPT_A$ARG $FILE/$CHAMPION > original;
		$COREWAR -dump $CYCLES $OPT_O$ARG $FILE/$CHAMPION > our;
		diff original our > file;
	WORDCOUNT=$(cat file | wc -l);
	if [ $WORDCOUNT = "0" ]
	then
		printf "${GREEN}▓${NC}";
		CYCLES=$(( $CYCLES + 2500));
	else
		printf "${RED}▓${NC}";
		PROBLEM=$CYCLES;
		return 
	fi;
	done;
}

timeout_fct()
{
	local bin=$1
	local tmp_out=$2

	{ $bin $OPT_O$OPT_V$ARG $FILE/$CHAMPION; } > out 2>&1 &
	local pid=$!
	sleep $TIMEOUT &
	local pid_sleep=$!
	while ps -p $pid_sleep > /dev/null
		do
		if ! ps -p $pid > /dev/null; then
			kill $pid_sleep > /dev/null 2>&1
		fi
		done
	if ps -p $pid > /dev/null; then
		kill $pid && killall `basename $bin` > /dev/null 2>&1
		printf "${RED}timeout${NC}";
		TIME=1;
		return 1;
	fi
	TIME=0;
}

initial_check()
{
	TIME=0;
	printf "${RED} testing $CHAMPION with $ARG ${NC}\n" >> trace;
	timeout_fct $COREWAR $OUR 2> /dev/null
	if [ $TIME = "0" ] 
	then
		ORIG=$( ./originals/corewar $OPT_A$OPT_V$ARG $FILE/$CHAMPION; )
		diff <(echo "$ORIG") out > file
		WORDCOUNT=$( cat file | wc -l );
		if [ $WORDCOUNT = "0" ]
		then
			printf "${GREEN}▓${NC}";
		else
			if [ $WORDCOUNT -lt "2500" ]
			then
				diff <(echo "$ORIG") out >> trace;
			else 
				echo "GIANT DIFF" >> trace;
			fi;
			PROBLEM=1;
		fi;
	else 
		PROBLEM=1;
		echo "Timeout" >> trace;
	fi;
}

find_champions()
{
	ls $FILE > lines
	grep .cor lines > champions
	CHAMPIONS=$( cat champions | wc -l; )
	CHAMPIONS=$(( $CHAMPIONS + 1));
}

analyze()
{
	CYCLES=0;
	PROBLEM=0;
	initial_check
	if [ $PROBLEM -eq "0" ]
	then
		printf "${GREEN} NO PROBLEM ${NC}\n"
	else 
		printf "${RED} PROBLEM ${NC}\n"
		if [ $TIME = "0" ]
		then
			primary_check
			if [ $CYCLES = "50000" ]
			then
				printf "${GREEN} ACTUALLY, PROBLEMS IN VERBOSITY :) $PROBLEM ${NC}\n"
			else
				detail_check
				thorough_check
			fi;
		fi;
	fi;
}

print_usage()
{
		echo "usage:"
		echo "./$0 [-oav:f:] folder champion corewar"
		echo "flag -o: run our corewar in original mode. With this option off, it will differ from the original output"
		echo "flag -a: run original corewar with flag -a, this is set as default for our corewar"
		echo "flag -v NBR: run both our and the original corewar with flag -v and same options as in original"
		echo "flag -f NBR multiple fights for each champion, the default is 1"
		echo "example:"
		echo "./$0 "testers ./testers/jumper.cor ./to_test/corewar
		echo "> run tests of your corewar program with all champions from the testers folder against jumper.cor"
		echo "options:"
		echo "    folder 	folder with champions to test against"
		echo "    champion 	path to the champion to be used as reference"
		echo "    corewar  	path to your corewar executable"
}

print_usage_and_exit()
{
		print_usage
			exit 1
}

print_usage_error_and_exit()
{
		printf "error: %s\n\n" "$1"
		print_usage_and_exit
}

[ $# -lt 3 ] && print_usage_and_exit
while getopts "ohav:f:" opt
do
		case "$opt" in
		o)
			OPT_O="-o "
			;;
		a)
			OPT_A="-a "
			;;
		v)
			if echo $OPTARG | grep -E "^[0-9]+$" > /dev/null 2>&1; then
				if [ $OPTARG -ge 1 -a $OPTARG -le 31 ]; then
					OPT_V="-v $OPTARG"
				else
					printf "%s\n\n" "Error: -v arg should be between 1 and 31 (inclusive)"
					print_usage_and_exit
				fi
			else
				printf "%s\n\n" "Error: -v arg should be a number"
				print_usage_and_exit
			fi
			;;
		f)
			if echo $OPTARG | grep -E "^[0-9]+$" > /dev/null 2>&1; then
				[ "$opt" = "f" ] && FIGHT=$OPTARG
			else
				printf "Invalid number or fight, fight mode disabled...\n"
			fi
			;;
		h|*)
			print_usage_and_exit
			;;
	esac
done
shift $((OPTIND - 1))

FILE=$(echo $1);
TESTER=$2;
COREWAR=$3;

find_champions

while [ $ORDER -lt $CHAMPIONS ];
do
	CHAMPION=$( sed -n "$ORDER"p champions )
	echo $CHAMPION
	ARG=" ";
	analyze
	if [ $FIGHT -gt "1" ]	
	then
	echo "$CHAMPION with $TESTER";
	ARG=$(echo " $TESTER");
	analyze
	fi
	if [ $FIGHT -gt "2" ]	
	then
	echo "$CHAMPION with $TESTER $TESTER";
	ARG=$(echo " $TESTER $TESTER");
	analyze
	fi;
	if [ $FIGHT -gt "3" ]	
	then
	echo "$CHAMPION with $TESTER $TESTER $TESTER";
	ARG=$(echo " $TESTER $TESTER $TESTER");
	analyze
	fi;
	ORDER=$(( $ORDER + 1));
done;

rm out
rm file
rm champions
