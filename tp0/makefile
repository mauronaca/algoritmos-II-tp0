# Argumentos
#
CXXARGS  = -g -Wall
CXXFLAGS = $(CXXARGS) -I
CXX = g++

# Carpetas del programa
#
CLASSDIR = src
TESTSDIR = pruebas
OBJSDIR = obj

# Archivos .cpp
#
CMDLINE = $(CLASSDIR)/cmdline.cpp 
COMPLEJO = $(CLASSDIR)/complejo.cpp 


$(OBJSDIR)/test.o: $(OBJSDIR)/cmdline.o $(TESTSDIR)/test.cpp
	$(CXX) $(CXXFLAGS)$(CLASSDIR) -c $(TESTSDIR)/test.cpp -o $@

$(OBJSDIR)/cmdline.o: $(CMDLINE)
	$(CXX) $(CXXFLAGS) $(CLASSDIR) -c $(CMDLINE) -o $@

# Compilar test.cpp, linkea cmdline.o y test.o. El ejecutable 
# va a parar a la carpeta /tp0/
#
test: $(OBJSDIR)/cmdline.o $(OBJSDIR)/test.o
	$(CXX) $(CXXARGS) -o $@ $(OBJSDIR)/cmdline.o $(OBJSDIR)/test.o

run_test: test // Da error pero funciona
	valgrind --leak-check=yes ./test

clean:
	$(RM) -vf $(OBJSDIR)/*.o *.exe *.t *.out *.err

