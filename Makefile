#2018201005 Vatsal Soni
CC = g++ 
CFLAGS = -Wall 
DEPS = config.h
OBJ = search.o snapshot.o copy.o move.o rename.o deletedir.o createdir.o createfile.o deletefile.o commandModeStart.o navigation.o ls.o main.o 
%.o: %.cpp $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o main

