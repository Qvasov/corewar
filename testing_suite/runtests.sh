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

date > trace

echo "--- [RUNNING ASM CHECKS] ---";

bash asmtest.sh resources/op
bash asmtest.sh resources/ocp
bash asmtest.sh resources/overflow
bash asmtest.sh resources/battle
bash asmtest.sh resources/champ
bash asmtest.sh resources/long
bash asmtest.sh resources/asm
bash asmtest.sh resources/overflow
bash asmtest.sh resources/asm/valid
bash asmtest.sh resources/asm/error

echo "--- [RUNNING OPERATIONS CHECKS] ---";

bash test.sh -o -a -v 15 resources/op neo.cor $1
bash test.sh -o -a -v 15 resources/ocp neo.cor $1
bash test.sh -o -a -v 15 resources/overflow neo.cor $1

echo "--- [RUNNING BATTLE CHECKS] ---";

bash test.sh -o -a -v 15 -f 4 resources/battle neo.cor $1

echo "--- [RUNNING FIGHTS] ---";

bash test.sh -o -a -v 15 -f 2 resources/champ neo.cor $1

rm asmtrace
rm champions
rm original
rm lines
rm file
rm our
