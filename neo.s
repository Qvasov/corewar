.name	"Neo"
.comment "There is no spoon..."

start:
		st r1,:save
		st r6,-4
		ld :save,r1
prep:
		ld %6, r16
		ld %190317328, r3
stlive:
		st r1, 6
live:
		live %0
sendgarbage:
		st r3, 500
sendgarbageback:
		st r3, -390
giveadress:
		fork %490
		ld :save,r1
stlive1:
		st r1, 6
live1:
		live %0
giveadress1:
		fork %-500
		ld %6, r16
stlive2:
		st r1, 6
live2:
		live %0
giveadress2:
		lfork %860
stlive3:
		st r1, 6
live3:
		live %0
giveadress3:
		fork %:stlive
stlive4:
		st r1, 6
live4:
		live %0
giveadress4:
		lfork %1160
save: 
		st r1, r1
stlive5:
		st r1, 6
live5:
		live %0
giveadress5:
		fork %:stlive
stlive6:
		st r1, 6
live6:
		live %0
giveadress6:
		lfork %1500
stlive7:
		st r1, 6
live7:
		live %0
giveadress7:
		fork %:stlive
stlive8:
		st r1, 6
live8:
		live %0
giveadress8:
		lfork %1700
stlive9:
		st r1, 6
live9:
		live %0
giveadress9:
		fork %:stlive
stlive10:
		st r1, 6
live10:
		live %0
giveadress10:
		lfork %1900
stlive11:
		st r1, 6
live11:
		live %0
giveadress11:
		fork %:stlive
stlive12:
		st r1, 6
live12:
		live %0
giveadress12:
		lfork %2000
stlive13:
		st r1, 6
live13:
		live %0
giveadress13:
		fork %:stlive
stlive14:
		st r1, 6
live14:
		live %0
giveadress14:
		lfork %2333
stlive15:
		st r1, 6
live15:
		live %0
giveadress15:
		fork %:stlive10
stlive16:
		st r1, 6
live16:
		live %0
giveadress16:
		lfork %2600
stlive17:
		st r1, 6
live17:
		live %0
		ld %0, r10
		zjmp %:live17
