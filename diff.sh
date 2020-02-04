rm 0 1
./cmake-build-debug/corewar vm_champs/champs/jumper.cor vm_champs/champs/examples/helltrain.cor vm_champs/champs/examples/helltrain.cor vm_champs/champs/jumper.cor> 0
./vm_champs/corewar -d 19198 -v 6 vm_champs/champs/jumper.cor vm_champs/champs/examples/helltrain.cor vm_champs/champs/examples/helltrain.cor vm_champs/champs/jumper.cor> 1
diff 0 1
