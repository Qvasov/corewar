rm 0 1
./cmake-build-debug/corewar -dump 0 -v 6 \
	vm_champs/champs/jumper.cor \
	vm_champs/champs/examples/helltrain.cor \
	vm_champs/champs/examples/helltrain.cor \
	vm_champs/champs/jumper.cor > 0
./vm_champs/corewar -d 0 -v 6 \
	vm_champs/champs/jumper.cor \
	vm_champs/champs/examples/helltrain.cor \
	vm_champs/champs/examples/helltrain.cor \
	vm_champs/champs/jumper.cor > 1
diff 0 1
