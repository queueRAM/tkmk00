################ Target Executable and Sources ###############

TARGET := tkmk00test

SRC_FILES  := main.c   \
              n64graphics.c \
              tkmk00.c \
              utils.c

OBJ_DIR     = ./obj

##################### Compiler Options #######################

WIN64_CROSS = x86_64-w64-mingw32-
WIN32_CROSS = i686-w64-mingw32-
#CROSS     = $(WIN32_CROSS)
CC        = $(CROSS)gcc
LD        = $(CC)
AR        = $(CROSS)ar

INCLUDES  = 
DEFS      = 
# Release flags
# CFLAGS    = -m32 -Wall -Wextra -O2 -g -ffunction-sections -fdata-sections $(INCLUDES) $(DEFS) -MMD
# LDFLAGS   = -m32 -s -Wl,--gc-sections
# Debug flags
CFLAGS    = -m32 -Wall -Wextra -O0 -g $(INCLUDES) $(DEFS) -MMD
LDFLAGS   = -m32
LIBS      = -lpng

OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))
DEP_FILES = $(OBJ_FILES:.o=.d)

######################## Targets #############################

default: all

all: $(TARGET)

$(OBJ_DIR)/%.o: %.c Makefile
	@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(TARGET): $(OBJ_FILES)
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(OBJ_FILES) $(DEP_FILES)
	rm -f $(TARGET) $(TARGET).exe
	-@[ -d $(OBJ_DIR) ] && rmdir --ignore-fail-on-non-empty $(OBJ_DIR)

.PHONY: all clean default

#################### Dependency Files ########################

-include $(DEP_FILES)
