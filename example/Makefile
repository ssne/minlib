PROJECT = example
MCU = atmega16
TARGET = example.elf
CC = avr-gcc
COMMON = -mmcu=$(MCU)
CFLAGS = $(COMMON)
CFLAGS += -DF_CPU=8000000UL
CFLAGS += -Wall -pedantic -gdwarf-2 -std=c99 -fno-builtin -O2
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=example.map

HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

INCLUDES = -I"../minlibc/include" 
LIBDIRS = -L"../minlibc/lib"

LIBS = -lc 

OBJECTS = main.o 

all: $(TARGET) example.hex example.lss 

main.o: main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

.PHONY: clean
clean:
	-rm -rf $(OBJECTS) example.elf dep/* example.hex example.lss example.map

# For Windows machines
#-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

