.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		and r1, %0, r1
		ld	%100, r2
		aff	r2

live:	live %1
		zjmp %:live
