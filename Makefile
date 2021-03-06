#!/usr/bin/make -f
#
# Filename:		Makefile
# Date:			02/28/2019
# Author:		Noah Sims
# Email:		ngs170000@utdallas.edu
# Version:		2.0
# Copyright:		2019, All Rights Reserved
#
# Description:
#
#	Makefile for program3, modified from the example given by Steven Perkins
#


# The compiler to use
CXX = g++

# C pre-processor flags
CPPFLAGS = 

# compiler flags
CXXFLAGS = -Werror


# Project name.  This is used in building the file name for the backup target
PROJECTNAME = hw3

# Directory where the tarball deliverable of the project will be created
TARDIR = ~/CS3377/assignments

# C++ Source files

SRCS = program3.cc parseNums.cc

# Executable name
EXEC = program3


#
# Don't change anything below here
# ======================================================
#
OBJS = $(SRCS:cc=o)

.PHONY: all clean

all: $(EXEC)
clean:
	rm -f $(OBJS) *.d *~ $(EXEC)


# Pattern for .d files.
%.d:%.cc
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


#  This is a rule to link the files.  Pretty standard
$(EXEC): $(OBJS)
	$(CXX) -o $(EXEC) $(OBJS)

Makefile: $(SRCS:.cc=.d)


# Backup Target
backup:	clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

# Tarball deliverable
tarball: clean
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKTARNAME := $(TARDIR)/$(PROJECTNAME).tar.gz)
	@echo
	@echo Writing tarball file to: $(TARDIR)
	@echo
	@-tar zcfv $(MKTARNAME) ../$(CURDIRNAME) --exclude='*/bin' --exclude='*/etc' --exclude "../hw3/gawk" --exclude='*/include' --exclude='*/lib' --exclude='*/libexec' --exclude='*/share'
	@echo
	@echo Done!


# Include the dependency files created by the PreProcessor.  The
# dash in front of the command keeps the system from complaining
# if the files do not exist.

-include $(SRCS:.cc=.d)

