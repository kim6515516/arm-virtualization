all: brot.axf wfi.axf

%.o: %.c
	armcc -g -O2 -c -o $@ $<
%.o: %.s
	armasm -g -o $@ $^
%.axf: %.o
	armlink --ro-base 0x8000 -o $@ $^

brot.o: brot.c
brot.axf: brot.o

wfi.o: wfi.s
wfi.axf: wfi.o
