#==== Main Options =============================================================

MCU = atmega32
F_CPU = 8000000
TARGET_NAME = EmbeddedMallWithIoT


#==== Programming Options (avrdude) ============================================

AVRDUDE_PROGRAMMER = usbasp

AVRDUDE_FLAGS := -p $(MCU) -c $(AVRDUDE_PROGRAMMER)
SHELL = C:\cygwin64\bin\sh.exe
#============== C files in thier respective Directories ========================
SRCS = 	../main.c \
		../OS/OS.c\
		../OS/OStimer.c

INCS =	../OS/
#INCS = OS/ \
#		Includes/

#===============================================================================
#==== Targets ==================================================================
# Prepare target files path and name
TARGET := Targets/$(TARGET_NAME)


# Convert c files to Object files in OBJ
OBJ := $(SRCS:.c=.o)
# include path
INCLUDE := $(foreach dir, $(dir $(SRCS)), -I$(dir))
INCLUDE += $(foreach dir, $(dir $(INCS)), -I$(dir))

#================================================================================

#==== Compile Options ==========================================================

CFLAGS := -mmcu=$(MCU)
CFLAGS += -DF_CPU=$(F_CPU)UL
CFLAGS += -D__AVR_ATmega32__
CFLAGS += -Os
#CFLAGS += -mint8
#CFLAGS += -mshort-calls
CFLAGS += -funsigned-char
CFLAGS += -funsigned-bitfields
CFLAGS += -fpack-struct
CFLAGS += -fshort-enums
#CFLAGS += -fno-unit-at-a-time
CFLAGS += -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
#CFLAGS += -Wunreachable-code
#CFLAGS += -Wsign-compare
CFLAGS += -std=gnu99
CFLAGS += $(INCLUDE)

#=======  Build Tools   ===========================================================
CC := avr-gcc
OBJCOPY := avr-objcopy
AVRDUDE := avrdude
REMOVE := rm -f
SIZE := avr-size --format=avr --mcu=$(MCU)

#to do all, there is a prerequisites the hex file, if the hex file doesn't exist, make will
#look for a rule to build the hex file
all: $(TARGET).hex 
	
# Rule to build the hex file, requires the elf file to exist as a prerequisite, if the elf doesn't exit
# look for a rule to build it
%.hex: %.elf
	@echo '****************** Generating $@ file  *********************'
	@$(OBJCOPY) -O ihex -j .text -j .data $^ $@
	@$(SIZE) $^
# Rule to build the elf file, requires all the objects files to exist and up to date, otherwise look for
# a rule to build the object files
$(TARGET).elf: $(OBJ)
	@echo '********************  Linking $(OBJ) **********************'
	@$(CC) $(CFLAGS) -o $(TARGET).elf $(OBJ)
	
# Rule to build objects from c files
%.o:%.c
	@echo '**************  Building $< *****************************'
	@$(CC) $(CFLAGS) -MD -c $< -o $@
	@$(CC) $(CFLAGS) -S $< -o $*.s

# Rule for the python generated C file (GenMenu.c and GenMenu.h)
Menu/menu.c: Menu/GenMenu.c

Menu/GenMenu.c: Menu/inputScript.txt
		python Menu/MenuGen.py


program: all
	$(AVRDUDE) $(AVRDUDE_FLAGS) -u -U flash:w:$(TARGET).hex
	
fuse:
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U lfuse:w:0xe4:m -U hfuse:w:0xd9:m

clean:
	$(REMOVE) $(TARGET).hex
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(OBJ) $(SRCS:.c=.s)
	$(REMOVE) $(SRCS:.c=.d)
#remove the generated files
#	$(REMOVE) Menu/GenMenu.*
	
#-include $(SRCS:.c=.d)
-include $(subst .c,.d,$(SRCS))
#Rule to build the dependency files

	
%.d: %.c
	@$(CC) -M $(CFLAGS) $< > $@.$$$$ ;\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;\
	rm -f $@.$$$$