PROJNAME=avr-rc5
MCU=atmega8
CC=avr-gcc
LD = avr-gcc
OBJCOPY=avr-objcopy
OBJCOPYFLAGS=-R .eeprom -O ihex

OBJECTS = main.o rc5.o

CFLAGS=-g -mmcu=$(MCU) -Wall -Wstrict-prototypes -mcall-prologues -I/usr/lib/avr/include/ -B/usr/lib/avr/lib/avr5/ -D __AVR_ATmega8__ -D F_CPU=1000000 -D __OPTIMIZE__
all: $(PROJNAME).hex
$(PROJNAME).hex: $(PROJNAME).out
	$(OBJCOPY)  $(OBJCOPYFLAGS) $< $@
$(PROJNAME).out: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROJNAME).out -Wl,-Map,$(PROJNAME).map $(OBJECTS)
%.o: %.c %.h 
	$(CC) $(CFLAGS) -Os -c $< -o $@
load: $(PROJNAME).hex
	avrdude -c usbasp -p $(MCU) -U flash:w:$(PROJNAME).hex
clean:
	rm -f *.o *.map *.out *.elf *.hex
