##################################
# stm32 minimal example Makefile
##################################

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
CP = arm-none-eabi-objcopy

LKR_SCRIPT = stm32_minimal.ld

CFLAGS  = -c -fno-common -O0 -g -mcpu=cortex-m3 -mthumb
LFLAGS  = -nostartfiles -T$(LKR_SCRIPT)
CPFLAGS = -Obinary

all: main.bin

main.o: main.c
	$(CC) $(CFLAGS) -o main.o main.c

main.elf: main.o
	$(LD) $(LFLAGS) -o main.elf main.o

main.bin: main.elf
	$(CP) $(CPFLAGS) main.elf main.bin

clean:
	rm -rf *.o *.elf *.bin

write:
	./write_bin.sh openocd.cfg main.elf
