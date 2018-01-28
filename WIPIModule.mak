#============================================================================
#  Name:
#    MAKEFILE
#
#  Description:
#
#    Makefile for ADS
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

EXETYPE   	= elf#                   		# File type
BIN1_EXT	= _APP1#
BIN2_EXT	= _APP2#
TARGET    	= obj#
MAKE_TARGET1    = $(TARGET)\APP1#               	# Target name
MAKE_TARGET2    = $(TARGET)\APP2#               	# Target name
ELF_NAME	= $(TARGET)\$(BINARY)#
BIN1_NAME	= $(ELF_NAME)$(BIN1_EXT)#
BIN2_NAME	= $(ELF_NAME)$(BIN2_EXT)#

#LIB_DIR		= C:\Program Files\WIPI SDK\Lib#	# Library directory
#INC_DIR		= C:\Program Files\WIPI SDK\Include#	# Include directory
SCL_FILE1       = "$(LIB_DIR)/WIPIMake1.scl"#
SCL_FILE2       = "$(LIB_DIR)/WIPIMake2.scl"#
TARGET_OBJ      = "$(LIB_DIR)"#                   	# Object directory

APP_OBJS 	= $(patsubst %.c,obj/%.o,$(SRC_FILES))
ASM_OBJS 	= $(patsubst %.s,obj/%.o,$(SRC_FILES))
WIPI_OBJS	= ./WIPIstub.o#
//WIPI_OBJS	= "$(LIB_DIR)/WIPIstub.o"#

APP_LINKS	= $(filter %.o, $(APP_OBJS) $(ASM_OBJS) $(WIPI_OBJS))#

INCS		= -I"$(INC_DIR)" -I"$(INC_DIR)/API" -I"$(INC_DIR)/API/WFC" -I"$(INC_DIR)/HAL"

#-------------------------------------------------------------------------------
# Taret type definitions
#CC          = tcc#                                 # ARM SDT Thumb 16-bit inst. set ANSI C compiler
ASM         = armasm#                               # ARM SDT assembler
LD          = armlink#                              # ARM SDT linker
HEXTOOL     = fromelf#                              # ARM SDT utility to create hex file from image
OBJ_CMD     = -o#                                   # Command line option to specify output filename
CPU         = #-cpu ARM7TDMI#                        # ARM7TDMI target processor
PCSZ        = 32bit#                                # Program counter (PC) size
STACKCHK    = noswst#(default=noswst)               # No software stack checking support
FRAMEPTR    = nofp#(default=nofp)                   # No frame pointer
FLOATPNT    = softfp#(default=softfp)               # Use software floating point library
INTRWORK    = interwork#(default=nointerwork)       # ARM/Thumb interworking support
NARROW      = narrow#                               # Use caller parameter narrowing
REENTRNT    = nonreentrant#                         # No support for re-entrancy
APCS        = -apcs /$(STACKCHK)/$(INTRWORK)#/ropi
OUT         = -c#                                   # Object file output only
#DBG         = -g -dwarf2#                           # Enable DWARF2 format debug tables
OPT         = -Ospace -O2#                          # Full compiler optimization for space
#OPT         = -Ospace -O0#                                  # No compiler optimization
END         = -littleend#(defualt=Littleend)        # Compile for little endian memory architecture
ZA          = -za1#(default=za0)                    # LDR may only access 32-bit aligned addresses
ZAS         = -zas4#(default=zas4)                  # Min byte alignment for structures
ZAP         = -zap0#(default=zap1)                  # Struct ptrs NOT assumed to be aligned per -zas
ZAT         = -zat1#(default=zap1:thumb)            # Min byte alignment for top-level static objects
ZZT         = -zzt0#                                # Force uninitialized variables to ZI data area
ZC          = -zc -Ec#                              # make char signed
CODE        = $(END) $(ZC) -D_TG_PHONE_ #
INC         = -I. -I$(TARGET_OBJ) $(INCS) $(USER_INCS)#
#PRAGMA     = -zpcontinue_after_hash_error#
MSG         = -Wb#                                  # No warnings for bit fields
CHK         = -fa#                                  # Check for data flow anomolies
#MAP         = -map#                                 # Memory map of all object file areas
#INFO        = -info sizes,totals,veneers#           # Info on object size and interworking
XREF        = -xref#                                # List cross-references between files
VERB        = -verbose#                             # Print verbose output messages
#LIST        = -list $(MAKE_TARGET1).map#            # Direct map and info output to file
#SYM         = -symbols -symdefs $(MAKE_TARGET1).sym## Direct symbol table to file
#LIST2        = -list $(MAKE_TARGET2).map#            # Direct map and info output to file
#SYM2         = -symbols -symdefs $(MAKE_TARGET2).sym## Direct symbol table to file
REMV        = -noremove#                            # does not perform unused section elimination
LINK1       = -scatter $(SCL_FILE1)#                # Use scatter load description file
LINK2       = -scatter $(SCL_FILE2)#                # Use scatter load description file
ENTRY       = -entry startClet#
#CLIB        = $(ARMLIB)/armlib/c_t__un.l#           # ARM embedded ANSI C library
#CLIB        = $(LIB_DIR)/c_t__un.l#           # ARM embedded ANSI C library
CLIB        =
THURM       = -16				# Assemble 16 bit Thumb instructions
KEEP        = -keep
LIBS        = $(CLIB) $(USER_LIBS)#
CFLAGS      = $(OUT) $(INC) $(CPU) $(APCS) $(CODE) $(CHK) $(DBG) $(OPT) $(USER_CFLAGS)
SFLAGS      = $(INC) $(CPU) $(APCS) $(END) $(KEEP) $(THURM) $(DBG) $(USER_SFLAGS)
LFLAGS1     = $(MAP) $(INFO) $(LIST) $(SYM) $(LINK1) $(REMV) $(ENTRY)
LFLAGS2     = $(MAP) $(INFO) $(LIST2) $(SYM2) $(LINK2) $(REMV) $(ENTRY)

#SRC_FILE    = $(@:%.o=%.c)#                         # Input source file specification
#OBJ_FILE    = $(OBJ_CMD) $(@)#                      # Output obj file specification
#SRC_CFILE   = $(SRC_DIR)/$(notdir $(SRC_FILE))#		# C File of src without directory

#-------------------------------------------------------------------------------
# Default target
all:    $(TARGET)/exist $(MAKE_TARGET2).$(EXETYPE) TARGET_B2 $(ELF_NAME).$(EXETYPE) TARGET_B1

#-------------------------------------------------------------------------------
# Exist Target
$(TARGET)/exist :
		@echo =============================================================================
		@-if not exist $(TARGET)/exist mkdir $(TARGET)
		@echo Building $(TARGET) > $(TARGET)\exist

#-------------------------------------------------------------------------------
# Image file target
$(MAKE_TARGET2).$(EXETYPE) : $(LG_OBJS) $(APP_LINKS)
		@echo -----------------------------------------------------------------------------
		@echo                               Linking...                                    
		@echo -----------------------------------------------------------------------------
		@echo $(LD) -$(EXETYPE) $(LFLAGS2) $(OBJ_CMD) $@ $(LIBS) $(APP_LINKS)
		@$(LD) -$(EXETYPE) $(LFLAGS2) $(OBJ_CMD) $@ $(LIBS) $(APP_LINKS)
		
TARGET_B2:
		@$(HEXTOOL)  -bin -o $(BIN2_NAME).bin $(MAKE_TARGET2).$(EXETYPE)
		@rm $(MAKE_TARGET2).$(EXETYPE)

$(ELF_NAME).$(EXETYPE) : $(LG_OBJS) $(APP_LINKS)
		@echo $(LD) -$(EXETYPE) $(LFLAGS1) $(OBJ_CMD) $@ $(LIBS) $(APP_LINKS)
		@$(LD) -$(EXETYPE) $(LFLAGS1) $(OBJ_CMD) $@ $(LIBS) $(APP_LINKS)
		
TARGET_B1:
		@$(HEXTOOL)  -bin -o $(BIN1_NAME).bin $(ELF_NAME).$(EXETYPE)
#		@rm $(BINARY).$(EXETYPE)
		@echo -----------------------------------------------------------------------------
		@echo .

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
