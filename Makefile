CPP = g++
SFML = -lsfml-graphics -lsfml-window -lsfml-system


main: main.o
	$(CPP) -o $@ $^ $(SFML)

%.o : %.CPP
	$(CPP) -o $@ -c $< 