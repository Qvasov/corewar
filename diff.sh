rm 0 1
NUM=31;
./cmake-build-debug/corewar -dump $1 -v $NUM \
	vm_champs/champs/jumper.cor \
	vm_champs/champs/examples/helltrain.cor > 0
./vm_champs/corewar -d $1 -v $NUM \
	vm_champs/champs/jumper.cor \
	vm_champs/champs/examples/helltrain.cor > 1
diff 0 1
