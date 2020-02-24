rm 0 1
NUM=6;
../cmake-build-debug/corewar -o -dump $1 -v $NUM \
	vm_champs_subject/ld_st_overflow.cor > 0
./corewar -a -d $1 -v $NUM \
	vm_champs_subject/ld_st_overflow.cor > 1
diff 0 1
