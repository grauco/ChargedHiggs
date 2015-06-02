GCC=g++
CXXFLAGS=`root-config --libs --cflags` -O2 -fPIC -I../  -I./
## to use BareObjects
CXXFLAGS += -L../NeroProducer/Core/bin -lBare 
SOFLAGS=-shared

SRCDIR=src
BINDIR=bin
HPPDIR=interface

SRC=$(wildcard $(SRCDIR)/*.cpp)
OBJ=$(patsubst $(SRCDIR)/%.cpp, $(BINDIR)/%.o , $(SRC)  )
HPPLINKDEF=$(patsubst $(SRCDIR)/%.cpp, ../interface/%.hpp , $(SRC)  )



libBare.so: $(OBJ) Dict | $(BINDIR)
	$(GCC) $(CXXFLAGS) $(SOFLAGS) -o $(BINDIR)/$@ $(OBJ) $(BINDIR)/dict.o

$(OBJ) : $(BINDIR)/%.o : $(SRCDIR)/%.cpp interface/%.hpp | $(BINDIR)
	$(GCC) $(CXXFLAGS) -c -o $(BINDIR)/$*.o $<

.PHONY: Dict
Dict: $(BINDIR)/dict.o

$(BINDIR)/dict.o:
	cd $(BINDIR) && rootcint -v4 -f dict.cc -c -I../../ -I../ $(HPPLINKDEF)  ../interface/LinkDef.hpp 
	cd $(BINDIR) && $(GCC) -c -o dict.o $(CXXFLAGS) -I../../ dict.cc
$(BINDIR):
	mkdir -p $(BINDIR)

.PHONY: clean
clean:
	-rm $(OBJ)
	-rm $(BINDIR)/dict*
	-rm $(BINDIR)/libBare.so
	-rmdir $(BINDIR)
