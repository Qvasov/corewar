rm 0 1
NUM=4;
./cmake-build-debug/corewar -dump $1 -v $NUM \
	vm_champs/sti_2.cor > 0
./vm_champs/corewar -d $1 -v $NUM \
	vm_champs/sti_2.cor > 1
diff 0 1
