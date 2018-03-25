CROSS   ?=avr-
CC      :=$(CROSS)gcc
# CXX     :=$(CROSS)g++
LD      :=$(CROSS)g++
SIZE    :=$(CROSS)size
OBJCOPY :=$(CROSS)objcopy
OBJDUMP :=$(CROSS)objdump
SIZE    :=$(CROSS)size

SRCDIR=Logger
BUILDDIR=Other/build

TARGET?=a
MMCU?=
AVRDUDE_FLAGS?=

SOURCES=$(shell find . -name '*.c')
# INCLUDES=$(wildcard $(SRCDIR)/**/*.h)
INCLUDES=

# # SETTINGS=settings.h

# OBJECTS=$(SOURCES:.cpp=.o)
# OBJECTS:=$(SOURCES:.c=.o)
OBJECTS:=$(patsubst %.c,$(BUILDDIR)/%.o,$(SOURCES))

CSTD?=c99
COPT=-O2 -fdata-sections -ffunction-sections
CFLAGS=-mmcu=$(MMCU) -std=$(CSTD) $(COPT) -Wall
CFLAGS+=$(addprefix -I,$(INCLUDES))
# CFLAGS+=-include "$(SETTINGS)"

# CXXSTD?=c++98
# CXXOPT=$(COPT) -fno-exceptions -fno-rtti
# CXXFLAGS=-mmcu=$(MMCU) -std=$(CXXSTD) $(CXXOPT) -Wall
# CXXFLAGS+=$(addprefix -I,$(INCLUDES))
# CXXFLAGS+=-include "$(SETTINGS)"

LDFLAGS=-mmcu=$(MMCU) -Os -std=$(CSTD) -Wl,--gc-sections -Wl,-Map=$(BUILDDIR)/$(TARGET).map,--cref


.PHONY: all avrdude clean

all: $(BUILDDIR)/$(TARGET).hex $(BUILDDIR)/$(TARGET).lst size

rebuild: clean all

build_flash: all size avrdude

$(BUILDDIR)/$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -lm -o $@

$(BUILDDIR)/$(TARGET).hex: $(BUILDDIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom -R .fuse -R .lock -R .signature $< $@

$(BUILDDIR)/$(TARGET).bin: $(BUILDDIR)/$(TARGET).elf
	$(OBJCOPY) -O binary -R .eeprom -R .fuse -R .lock -R .signature $< $@

# %.o: %.cpp
# 	$(CXX) -o $@ $(CXXFLAGS) -MMD -MP -MF $(@:%.o=%.d) $< -c

$(BUILDDIR)/%.o: %.c
	mkdir -p "$(@D)"
	$(CC) -o $@ $(CFLAGS) -MMD -MP -MF $(@:%.o=%.d) $< -c

$(BUILDDIR)/$(TARGET).lst: $(BUILDDIR)/$(TARGET).elf
	$(OBJDUMP) -h -S $< > $@

size:
	$(SIZE) -C --mcu=$(MMCU) $(BUILDDIR)/$(TARGET).elf

avrdude:
	avrdude $(AVRDUDE_FLAGS) -U flash:w:$(BUILDDIR)/$(TARGET).hex

clean:
	-rm -f $(addprefix $(BUILDDIR)/$(TARGET), .elf .hex .bin .lst .map)

