rm 0 1
NUM=15;
./cmake-build-debug/corewar -o -dump $1 -v $NUM \
	vm_champs/xor_d4.cor > 0
./vm_champs/corewar -a -d $1 -v $NUM \
	vm_champs/xor_d4.cor > 1
diff 0 1
