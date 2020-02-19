rm 0 1
NUM=23;
./cmake-build-debug/corewar -dump $1 -v $NUM \
	vm_champs/champs/jumper.cor \
	vm_champs/newguy.cor > 0
./vm_champs/corewar -d $1 -v $NUM \
	vm_champs/champs/jumper.cor \
	vm_champs/newguy.cor > 1
diff 0 1
