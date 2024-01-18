##### Makefile 
##### recommended compiler and make is gcc
##### for Windows please use MinGW
##### (after installing please put C:\msys64\ucrt64\bin and
##### C:\msys64\usr\bin to system environment variable "Path")

# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = 

# Makefile settings - Can be customized.
APPNAME = Calendar
EXT = .cpp
SRCDIR = src
OBJDIR = obj
BINDIR = bin

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)
MKDIR = mkdir
RM = rm


########################################################################
####################### Targets beginning here #########################
########################################################################

# Default target
all: $(OBJDIR)/ $(BINDIR)/ $(APPNAME) 

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $(BINDIR)/$@ $^ $(LDFLAGS)

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
	$(RM) $(OBJ) $(DEP) $(BINDIR)/$(APPNAME)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

# run after build
.PHONY: run
run: all
	./$(BINDIR)/$(APPNAME)
