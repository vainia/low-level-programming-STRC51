CC=sdcc --model-small
FLAGS= --code-loc 0x4000 --xram-loc 0x0000

all: main.rel lcd.rel
	$(CC) $(FLAGS) $^

%.rel: %.c
	$(CC) -c $<

clean:
	rm *.rel *.asm *.ihx .*.mem *.rst *.sym *.map *.lst *.lk *.lnk *.mem
