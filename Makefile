CC = g++ 
CFLAGS = -Wall 
DEPS = config.h
OBJ = createfile.o delete.o commandModeStart.o navigation.o ls.o main.o 
%.o: %.cpp $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^

