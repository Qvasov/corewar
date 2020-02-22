rm 0 1
NUM=6;
./cmake-build-debug/corewar -o -dump $1 -v $NUM \
	../aagripin_corewar/testing_suite/testers/newguy.cor \
	vm_champs/champs/jumper.cor \
	vm_champs/champs/jumper.cor \
	vm_champs/champs/jumper.cor > 0
./vm_champs/corewar -a -d $1 -v $NUM \
	../aagripin_corewar/testing_suite/testers/newguy.cor \
	vm_champs/champs/jumper.cor \
	vm_champs/champs/jumper.cor \
	vm_champs/champs/jumper.cor > 1
diff 0 1
