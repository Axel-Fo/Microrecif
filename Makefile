
# Definitions de macros

CXX     = g++
CXXFLAGS = -g -Wall -std=c++17
CXXFILES = projet.cc message.cc shape.cc simulation.cc lifeform.cc gui.cc graphic.cc
LINKING = `pkg-config --cflags gtkmm-4.0`
LDLIBS = `pkg-config --libs gtkmm-4.0`
OFILES = $(CXXFILES:.cc=.o)

TEST_CXXFILES = test.cc message.cc shape.cc 
TEST_OFILES = $(TEST_CXXFILES:.cc=.o)

# Definition de la premiere regle

projet: $(OFILES)
	$(CXX) $(OFILES) $(CXXFLAGS) $(LINKING) -o projet $(LDLIBS)

# Pour creer un executable test.exe

test: $(TEST_OFILES)
	$(CXX) $(TEST_OFILES) -o test

%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LDLIBS)

projet.o: projet.cc 
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LDLIBS)

# Pour faire tous les test
runtest: 
	rm -rf result 
	mkdir -p result
	./testproject 00
	./testproject 01
	./testproject 02
	./testproject 03
	./testproject 04
	./testproject 05
	./testproject 06
	./testproject 07
	./testproject 08
	./testproject 09
	./testproject 10
	./testproject 11
	./testproject 12
	./testproject 13
	./testproject 14
	./testproject 15

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) test.cc | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f projet test *.o *.x *.cc~ *.h~ 

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
projet.o: projet.cc simulation.h lifeform.h constantes.h shape.h \
 message.h
message.o: message.cc message.h
shape.o: shape.cc shape.h
simulation.o: simulation.cc simulation.h lifeform.h constantes.h shape.h \
 message.h
lifeform.o: lifeform.cc lifeform.h constantes.h shape.h message.h
gui.o: gui.cc
graphic.o: graphic.cc
test.o: test.cc shape.h
