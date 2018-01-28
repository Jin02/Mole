#============================================================================
#  Name:
#    MAKEFILE
#
#  Description:
#
#    Makefile for GCC
#
# Copyright (c) INNOACE Inc.  All Rights Reserved.
#----------------------------------------------------------------------------
#============================================================================
#
#                        EDIT HISTORY FOR MODULE
#
# when       who     what, where, why
# -------    ---     --------------------------------------------------------
# 05/03/2003 INNO    Create
#
#============================================================================

#-------------------------------------------------------------------------------
# Target file name

include config.min
include WIPIObjs.lst

TARGET          = obj#						# Object directory
EXETYPE         = elf#						# File type
ELF_NAME	= $(TARGET)\$(BINARY)#				# Target name
#LIB_DIR		= C:\Program Files\WIPI SDK\Lib#		# Library directory
#INC_DIR		= C:\Program Files\WIPI SDK\Include#		# Include directory
TARGET_OBJ      = "$(LIB_DIR)"#					# Object directory
APP_OBJS 	= $(patsubst %.c,obj/%.o,$(SRC_FILES))
ASM_OBJS 	= $(patsubst %.s,obj/%.o,$(SRC_FILES))
WIPI_OBJS	= #"$(LIB_DIR)/WIPIstubGcc.o"#
APP_LINKS	= $(filter %.o, $(APP_OBJS) $(ASM_OBJS) $(WIPI_OBJS))#
INCS		= -I"$(INC_DIR)" -I"$(INCAPI_DIR)" -I"$(INCAPI_DIR)/WFC" -I"$(INC_DIR)/GIGA"

#-------------------------------------------------------------------------------
# Taret type definitions
CC	    = arm-elf-gcc#
ASM         = arm-elf-as#					# ARM SDT assembler
LD	    = arm-elf-ld#
HEXTOOL     = arm-elf-objdump#					# ARM SDT utility to create hex file from image


#-------------------------------------------------------------------------------
# Compile Option definitions
OUT         = -c#                                   # Object file output only
OPT         = -O2#                                  # Full compiler optimization
INC         = -I. -I$(TARGET_OBJ) $(INCS) $(USER_INCS)#
GAPCS	    = -mapcs#
ENUM	    = -fshort-enums#
NOCOMM	    = -fno-common
THUMB       = -mthumb#
INTERWORK   = -mthumb-interwork#
CFLAGS	    = $(OUT) $(INC) $(GAPCS) $(ENUM) $(NOCOMM) $(THUMB) $(INTERWORK) $(OPT) $(USER_CFLAGS)

DEBUG       = --gstabs#
END         = -EL
CPU         = #-mcpu=ARM7TDMI
#APCS        = -mapcs-32
SFLAGS	    = $(INC) $(THUMB) $(DEBUG) $(END) $(CPU) $(APCS) $(USER_SFLAGS)

#-------------------------------------------------------------------------------
# Link Option definitions
OBJ_CMD     = -o#                                   # Command line option to specify output filename
REL	    = -r#
LIBPATH	    = -L. -L"$(LIB_DIR)"#
INCLIB	    = --library=gcc --library=c --library=m#
LS	    = -T WIPIGcc.ld#
NOSTDLIB    = --nostdlib#
NOGC	    = --no-gc-sections#
LOPT	    = -O2#
EXTR	    = -x -X#
MAP	    = -Map mapa#
LFLAGS_PREBUILD	    = $(LIBPATH) $(INCLIB) $(USER_LIBS) $(LS) $(NOSTDLIB) $(NOGC) $(LOPT) $(EXTR) $(MAP)
LFLAGS_RELEASE	    = $(REL) $(LIBPATH) $(INCLIB) $(USER_LIBS) $(LS) $(NOSTDLIB) $(NOGC) $(LOPT) $(EXTR) $(MAP)

#SRC_FILE    = $(@:%.o=%.c)#                         # Input source file specification
#OBJ_FILE    = $(OBJ_CMD) $(@)#                      # Output obj file specification
#SRC_CFILE   = $(SRC_DIR)/$(notdir $(SRC_FILE))#                # C File of src without directory
#-------------------------------------------------------------------------------
# Default target
all:    $(TARGET)/exist $(ELF_NAME).$(EXETYPE)

#-------------------------------------------------------------------------------
# Exist Target
$(TARGET)/exist :
		@echo =============================================================================
		@-if not exist $(TARGET)/exist mkdir $(TARGET)
		@echo Building $(TARGET) > $(TARGET)\exist

#-------------------------------------------------------------------------------
# Image file target
$(ELF_NAME).$(EXETYPE) : $(APP_LINKS)
		@echo -----------------------------------------------------------------------------
		@echo                            Check Symbol Table...
		@echo -----------------------------------------------------------------------------
		@$(LD) $(OBJ_CMD) $@ $(APP_LINKS) $(LFLAGS_PREBUILD) 
		@echo Success.
		@echo -----------------------------------------------------------------------------
		@echo                               Linking...                                    
		@echo -----------------------------------------------------------------------------
		@echo $(LD) $(OBJ_CMD) $@ $(APP_LINKS) $(LFLAGS_RELEASE)  
		@$(LD) $(OBJ_CMD) $@ $(APP_LINKS) $(LFLAGS_RELEASE) 
		@$(HEXTOOL) -h -r -t -D -s $(ELF_NAME).$(EXETYPE) > $(ELF_NAME).dump
		

#-------------------------------------------------------------------------------
# Clean Target
clean :
		@echo CLEAN TARGET
		@rm -f $(TARGET)/*.*
		@rm -rf $(TARGET)

#-------------------------------------------------------------------------------
# Comile Object Target
#$(APP_OBJS) : $(SRC_FILE)
#		@echo ...$@
#		@echo $(CC) $(CFLAGS) $(OBJ_FILE) $(SRC_CFILE)
#		@$(CC) $(CFLAGS) $(OBJ_FILE) $(SRC_CFILE)

vpath %.c \
	$(SRC_PATH)

vpath %.s \
	$(SRC_PATH)

obj/%.o : %.c
		@echo "... $@"
		@echo $(CC) $(CFLAGS) -o $@ $<
		@$(CC) $(CFLAGS) -o $@ $<

obj/%.o : %.s
		@echo "... $@"
		@echo $(ASM) $(SFLAGS) $< $@
		@$(ASM) $(SFLAGS) $< $@
