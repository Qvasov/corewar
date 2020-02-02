rm 0 1
./vm_champs/corewar -d 2180 -v 4 vm_champs/champs/jumper.cor > 1
./cmake-build-debug/corewar vm_champs/champs/jumper.cor > 0
diff 0 1
