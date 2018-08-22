CC = g++ 
CFLAGS = -Wall 
DEPS = config.h
OBJ = ls.o main.o 
%.o: %.cpp $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^

