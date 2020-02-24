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
FILE=$(echo $1)

initial_check()
{
	diff $FILE/$CHAMPION originalasm/$CHAMPION > file;
	WORDCOUNT=$(cat file | wc -l);
	if [ $WORDCOUNT = "0" ]
	then
		printf "${GREEN}▓${NC}";
	else
		PROBLEM=1;
	fi;
}

check_on_vm()
{
	PROBLEM=0;
	(./originals/corewar -d 1$ARG $FILE/$CHAMPION > asmour; ) #& pid=$!
#	( sleep 20 && pkill -HUP $pid ) 2>null & watcher=$!
#	wait $pid 2>null;
#	if ps -p $watcher 2>null;
#	then
#		pkill -HUP -P $watcher
#		wait $watcher
#	else
#	    echo "your_code timeout"
#		echo "timeout" >> our
#	fi;
	(./originals/corewar -d 1$ARG originalasm/$CHAMPION > asmoriginal;)  # & pid=$!
#	( sleep 20 && pkill -HUP $pid ) 2>null & watcher=$!
#	wait $pid 2>null; 
#	if ps -p $watcher 2>null;
#	then
#		pkill -HUP -P $watcher
#		wait $watcher
#	else
#	    echo "original_code timeout"
#		echo "timeout" >> original
#	fi;
	diff asmoriginal asmour > file;
	diff asmoriginal asmour >> asmtrace;
	WORDCOUNT=$(cat file | wc -l);
	if [ $WORDCOUNT = "0" ]
	then
		printf "${GREEN}▓${NC}";
	else
		PROBLEM=1;
	fi;
}

encode()
{
	cp $FILE/$CHAMPION originalasm;
	./originals/asm originalasm/$CHAMPION;
	./asm -a $FILE/$CHAMPION;
}

find_s()
{
	ls $FILE > lines
	grep .s lines > champions
	CHAMPIONS=$( cat champions | wc -l; )
	CHAMPIONS=$(( $CHAMPIONS + 1));
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
		check_on_vm
	else 
		printf "${RED} PROBLEM ${NC}\n"
		return ;
	fi;
	if [ $PROBLEM -eq "0" ]
	then
		printf "${GREEN} NO PROBLEM ${NC}\n"
	else 
		printf "${RED} PROBLEM ${NC}\n"
	fi;
}

echo $2
find_s

while [ $ORDER -lt $CHAMPIONS ];
do
	printf "${RED} Creating $CHAMPION ${NC}\n" >> asmtrace;
	CHAMPION=$( sed -n "$ORDER"p champions )
	echo $CHAMPION
		ARG=" ";
		encode
	ORDER=$(( $ORDER + 1));
done;

find_champions
ORDER=1;

while [ $ORDER -lt $CHAMPIONS ];
do
	printf "${RED} testing $CHAMPION ${NC}\n" >> asmtrace;
	CHAMPION=$( sed -n "$ORDER"p champions )
	echo $CHAMPION
		ARG=" ";
		echo "--- [PRIMARY DIFF TEST] ---";
		analyze
	ORDER=$(( $ORDER + 1));
done;

rm asmour
rm asmoriginal
