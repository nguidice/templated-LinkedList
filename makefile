COURSE = cs310
SEMESTER = spring2024
CP_NUMBER = 3
LASTNAME = Guidice
GITUSERID = nguidice
EXE = gll

REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar

# FLAGS = -Wall -Wextra -g
FLAGS = -Wall -Wextra -g
CC = g++
BIN = bin
OBJ = obj
GFILES = goofy.h GLL.h GLL.cpp
TESTS = $(BIN)/gll_int_test $(BIN)/gll_implicit $(BIN)/gll_explicit

all: $(BIN)/$(EXE) $(TESTS)

# ------------------------------------------------------------------------
# Builds the .o for the isGoofy() functions for string and int
$(OBJ)/goofy.o: goofy.cpp
	$(CC) $(FLAGS) -c goofy.cpp -o $@

# ------------------------------------------------------------------------
# Builds the .o for a simple Thing class
$(OBJ)/Thing.o: Thing.cpp
	$(CC) $(FLAGS) -c Thing.cpp -o $@

# ------------------------------------------------------------------------
# gll_driver
$(BIN)/$(EXE): $(OBJ)/gll_driver.o $(OBJ)/goofy.o $(OBJ)/Thing.o
	$(CC) $(FLAGS) $(OBJ)/gll_driver.o $(OBJ)/goofy.o $(OBJ)/Thing.o \
		-o $@ 

$(OBJ)/gll_driver.o: gll_driver.cpp $(GFILES) 
	$(CC) $(FLAGS) -c gll_driver.cpp -o $@

# ------------------------------------------------------------------------
# gll_int_test
$(BIN)/gll_int_test: $(OBJ)/gll_int_test.o $(OBJ)/goofy.o
	$(CC) $(FLAGS) $(OBJ)/gll_int_test.o $(OBJ)/goofy.o -o $@

$(OBJ)/gll_int_test.o: gll_int_test.cpp $(GFILES) $(OBJ)/goofy.o
	$(CC) $(FLAGS) -c gll_int_test.cpp -o $@

# ------------------------------------------------------------------------
# Flexible template instantiation
#
# gll_implicit comprises two rules that build the executable gll_implicit
# All of the GLL source files are compiled by including from within mygll.cpp
# mygll.cpp #includes GLL.h which #includes GLL.cpp
# mygll.cpp #includes Thing.h - GLL's can be used with your own class
# mygll.cpp #includes goofy.h so that GLL's can be used with string and int
#
# Using this method of compilation, GLLs can be instantiated with new types
# as long as the implementations of the types are linked into the executable
# (like Thing is here)
#
# This is the method used by gll_int_test above
#
$(BIN)/gll_implicit: $(OBJ)/gll_implicit.o $(OBJ)/goofy.o $(OBJ)/Thing.o 
	$(CC) $(FLAGS) $(OBJ)/gll_implicit.o $(OBJ)/goofy.o $(OBJ)/Thing.o -o $@

$(OBJ)/gll_implicit.o: mygll.cpp $(GFILES)
	$(CC) $(FLAGS) -c mygll.cpp -o $@
# ------------------------------------------------------------------------

# ------------------------------------------------------------------------
# Limited template instantiation
#
# This example builds a .o file for GLLs of strings, ints, and Things ONLY
#
# This method of compilation and program building loses the ability to 
# instantiate the GLL template for any type other than those placed in the
# file gll_limited.cpp
#
# You may build your own version of mygll.o and link that against these
# other four .o files (used below) to see how my code works on your 
# test program.  But of course it will only work with GLL's of ints, strings,
# and Things.
#
$(OBJ)/gll_limited.o: gll_limited.cpp $(GFILES)
	$(CC) $(FLAGS) -DEXPLICIT_GLL_INSTANTIATION \
		-c gll_limited.cpp -o $@

$(OBJ)/gll_explicit.o: mygll.cpp $(GFILES)
	$(CC) $(FLAGS) -DEXPLICIT_GLL_INSTANTIATION \
		-c mygll.cpp -o $@

$(BIN)/gll_explicit: $(OBJ)/gll_limited.o $(OBJ)/gll_explicit.o \
		$(OBJ)/goofy.o $(OBJ)/Thing.o
	$(CC) $(FLAGS) $(OBJ)/gll_explicit.o $(OBJ)/gll_limited.o \
		$(OBJ)/goofy.o $(OBJ)/Thing.o -o $@ 
# ------------------------------------------------------------------------

tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) $(TESTS) *.tar.gz
