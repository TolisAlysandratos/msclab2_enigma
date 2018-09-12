enigma: main.o functions.o Enigma.o Plugboard.o Reflector.o Rotor.o
	g++ main.o functions.o Enigma.o Plugboard.o Reflector.o Rotor.o -o enigma

main.o: main.cpp errors.h functions.h Enigma.h
	g++ -Wall -g -c main.cpp

functions.o: functions.cpp errors.h functions.h
	g++ -Wall -g -c functions.cpp

Enigma.o: Enigma.cpp Enigma.h errors.h functions.h
	g++ -Wall -g -c Enigma.cpp

Plugboard.o: Plugboard.cpp Plugboard.h
	g++ -Wall -g -c Plugboard.cpp

Reflector.o: Reflector.cpp Reflector.h
	g++ -Wall -g -c Reflector.cpp

Rotor.o: Rotor.cpp Rotor.h
	g++ -Wall -g -c Rotor.cpp

clean:
	rm -f main.o functions.o Enigma.o Plugboard.o Reflector.o Rotor.o enigma
