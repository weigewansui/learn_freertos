CC=avr-gcc
MMCU=atmega328
CFLAGS=-Wall -Os -mmcu=$(MMCU)
FREERTOS_DIR=$(shell pwd)/FreeRTOS
FREERTOS_INCLUDE=$(FREERTOS_DIR)/include
FREERTOS_SOURCE=$(FREERTOS_DIR)/%.c FreeRTOS $(FREERTOS_DIR)/portable/GCC/ATMega328/%.c

SOURCE=test.c
OBJS=$(SOURCE:%.c=%.o) 
# OBJS:=$(FREERTOS_SOURCE:%.c=%.o)
HEX=$(SOURCE:%.c=%.hex)

.PHONY: clean

all:$(HEX)


$(OBJS):$(SOURCE)
	# @mkdir -p build/objs
	@echo "compiling objects"
	@avr-gcc -g -Os  -mmcu=atmega328 -c test.c
	@avr-gcc -g -mmcu=atmega328 -o test.elf test.o

$(HEX):$(OBJS)
	@echo "linking hex files"
	@avr-objcopy -j .text -j .data -O ihex test.elf test.hex

flash: $(HEX)
	@avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:test.hex
clean:
	@rm -f *.o *.elf *.hex
