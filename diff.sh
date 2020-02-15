rm 0 1
NUM=7;
./cmake-build-debug/corewar -dump $1 -v $NUM vm_champs/champs/Gagnant.cor > 0
./vm_champs/corewar -d $1 -v $NUM vm_champs/champs/Gagnant.cor > 1
diff 0 1
