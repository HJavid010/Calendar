# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = 

# Makefile settings - Can be customized.
APPNAME = Calendar
EXT = .cpp
SRCDIR = src
OBJDIR = obj

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)
MKDIR = mkdir
RM = rm

ifneq ($(OS),Windows_NT)
  # *nix OS variables & settings
  DELOBJ = $(OBJ)
  EXE =
else
  # Windows OS variables & settings
  EXE = .exe
  DELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)
endif

########################################################################
####################### Targets beginning here #########################
########################################################################

# Default target
all: $(OBJDIR)/ $(APPNAME) 

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Creates obj folder if doesn't exist 
%/:
	$(MKDIR) $@

# Creates the dependecy rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<


# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)$(EXE)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

# run after build
.PHONY: run
run: all
	./$(APPNAME)$(EXE)
