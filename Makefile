# Makefile for LzwTree
#
# !!! IF LINUX MODIFY THE EXECUTABLE'S EXTENSION
#
# I'm new to makefiles, so for sanity reasons
# I explicitly listed out targets and didnt use
# any string operations, and made echos all over.
# Also I use mingw on win, so this is why we have exe.
# *****************************************************


APP   = lzwtree
APP_EXT = .exe

CXX = g++
CXXFLAGS = -std=c++11 -Wall -I.

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

#
# Main Target
#
main: $(OBJDIR)/main.o $(OBJDIR)/args.o $(OBJDIR)/lzwsptree.o $(OBJDIR)/sptree.o $(OBJDIR)/spnode.o 
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/$(APP)$(APP_EXT) $(OBJDIR)/main.o $(OBJDIR)/args.o $(OBJDIR)/lzwsptree.o $(OBJDIR)/sptree.o $(OBJDIR)/spnode.o 
	@echo "Built app!"

#
# Dependencies
#
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(SRCDIR)/args.h $(SRCDIR)/lzwsptree.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o

$(OBJDIR)/args.o: $(SRCDIR)/args.cpp $(SRCDIR)/args.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/args.cpp -o $(OBJDIR)/args.o
	
$(OBJDIR)/lzwsptree.o: $(SRCDIR)/lzwsptree.cpp $(SRCDIR)/lzwsptree.h $(SRCDIR)/sptree.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/lzwsptree.cpp -o $(OBJDIR)/lzwsptree.o
	
$(OBJDIR)/sptree.o : $(SRCDIR)/sptree.cpp $(SRCDIR)/sptree.h $(SRCDIR)/spnode.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/sptree.cpp -o $(OBJDIR)/sptree.o
	
$(OBJDIR)/spnode.o : $(SRCDIR)/spnode.cpp $(SRCDIR)/spnode.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/spnode.cpp -o $(OBJDIR)/spnode.o
	
#
# Cleans the object directory
#
clean:
	rm -f $(OBJDIR)/*.o
	@echo "Objects cleaned!"
#
# Deletes the executable,
# then cleans the object directory
#
remove: clean
	@rm $(BINDIR)/$(APP)$(APP_EXT)
	@echo "Executable removed!"