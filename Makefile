CC:=avr-gcc
MMCU:=atmega328
CFLAGS:=-Wall -Os -mmcu=$(MMCU)
FREERTOS_DIR:=FreeRTOS/Source
# FREERTOS_DEMO=$(shell pwd)/FreeRTOS/Demo/Common
FREERTOS_INCLUDE:=$(FREERTOS_DIR)/include
OTHER_INCLUE:=$(FREERTOS_DIR)/portable/GCC/ATMega328p

FREERTOS_SOURCE:=$(shell ls $(FREERTOS_DIR)/*.c) \
	               $(shell ls $(FREERTOS_DIR)/portable/GCC/ATMega328p/*.c) \
                 $(shell ls $(FREERTOS_DIR)/portable/MemMang/*.c)

# SOURCE:=test.c
# SOURCE+=$(FREERTOS_SOURCE)
# SOURCE=$(FREERTOS_SOURCE)
SOURCE:=$(FREERTOS_SOURCE)
SOURCE+=test.c
OBJS:=$(SOURCE:%.c=%.o)
OBJS:=$(patsubst %, build/OBJ/%, $(OBJS))

ELF:=build/test.elf #build/ELF/$(SOURCE:%.c=%.elf)
HEAP_C:=FREERTOS_DIR/portable/MemMang/heap_2.c
# OBJS:=$(FREERTOS_SOURCE:%.c=%.o)
HEX:=main.hex
LIB:=-I$(FREERTOS_INCLUDE) -I$(OTHER_INCLUE)

.PHONY: all clean flash

all: $(HEX)


$(HEX):$(ELF)
	@mkdir -p build/HEX
	@echo "linking hex files"
	@avr-objcopy -j .text -j .data -O ihex $(ELF) $(HEX)

build/OBJ/%.o:%.c
	@mkdir -p $(dir $@)
	@echo "compiling "$@
	@$(CC) -c $(LIB) -g -Os -mmcu=atmega328 -o $@ -c $< #whenever compile and not link, put -c!!!!!

$(ELF):$(OBJS)
	@mkdir -p $(@D)
	@echo "Linking "
	@$(CC) $(LIB) -g -mmcu=atmega328 -o build/test.elf $(OBJS) #build/OBJ/test.o

flash: $(HEX)
	@avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:main.hex

clean:
	@rm -f *.o *.elf *.hex
	@find . -name "*.o" -type f -delete
	@rm -rf build
