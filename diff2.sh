rm 0 1
./vm_champs/corewar -v 4 vm_champs/champs/jumper.cor vm_champs/champs/jumper.cor vm_champs/champs/examples/helltrain.cor> 1
./cmake-build-debug/corewar vm_champs/champs/jumper.cor vm_champs/champs/jumper.cor vm_champs/champs/examples/helltrain.cor> 0
diff 0 1
