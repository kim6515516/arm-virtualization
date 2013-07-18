ARMASM = 
ARMLINK = 
FROMELF = 

%.axf: %.S
	${ARMASM} $< -o $<.o --debug --cpu 7-A
	${ARMLINK} $<.o -o $@ --ro-base 0
	${FROMELF} --text -c -s --output=$@.lst $@

all: demo.axf vectors.axf semihosting.axf endian.axf fib.axf

clean:
	rm -vf *.o *.axf *.lst
