FAMILY := nrf52
SOURCES := main.c uart.c buttons.c # Din hovedfil med uart, buttons, osv.
SOURCES += .build_system/system_nrf52.c
SOURCES += .build_system/gcc_startup_nrf52.S

BUILD_DIR := build
BUILD_SYS := .build_system
LINKER_SCRIPT := $(BUILD_SYS)/linker_script_nrf52.ld

GNU_PREFIX    := arm-none-eabi
CC            := $(GNU_PREFIX)-gcc
OBJCOPY       := $(GNU_PREFIX)-objcopy
OBJDUMP       := $(GNU_PREFIX)-objdump

QUIET := @

## Inkluder den katalogen der du har dine header-filer
CFLAGS += -I.
CFLAGS += -I$(BUILD_SYS)

## Compiler flags
# CPU spesifikt
CFLAGS += -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=soft
# Linker optimalisering
CFLAGS += -ffunction-sections -fdata-sections --short-enums
CFLAGS += -fno-strict-aliasing -fno-builtin
# Advarsler og ISO C99-dialekt
CFLAGS += -Wall -Werror -std=gnu99
# Chip spesifikt
CFLAGS += -DNRF52832_XXAA

## Linker flags
CFLAGS += --specs=nosys.specs -Wl,--gc-sections -T $(LINKER_SCRIPT)
# alternativt: --specs=nano.specs -lc -lnosys

.PHONY: default flash debug erase recover clean

default: $(BUILD_DIR)
	@echo Compiling project
	$(QUIET)$(CC) $(CFLAGS) $(SOURCES) -o $(BUILD_DIR)/main.elf
	@echo Creating hex file
	$(QUIET)$(OBJCOPY) -O ihex $(BUILD_DIR)/main.elf $(BUILD_DIR)/main.hex

flash:
	nrfjprog -f $(FAMILY) --sectorerase --program $(BUILD_DIR)/main.hex --verify --reset
	
debug: $(BUILD_DIR)
	@echo Compiling project with debug
	$(CC) $(CFLAGS) -ggdb -Og $(SOURCES) -o $(BUILD_DIR)/main.elf
	@echo Creating hex file
	$(OBJCOPY) -O ihex $(BUILD_DIR)/main.elf $(BUILD_DIR)/main.hex

erase: $(BUILD_DIR)
	nrfjprog -f $(FAMILY) --eraseall

clean: $(BUILD_DIR)
	$(QUIET) rm $(BUILD_DIR)/main.elf
	$(QUIET) rm $(BUILD_DIR)/main.hex

recover: $(BUILD_DIR)
	nrfjprog --recover

$(BUILD_DIR):
	$(QUIET) mkdir -p $(BUILD_DIR)
