CC = g++ 
CFLAGS = -Wall 
DEPS = config.h
OBJ = createfile.o deletefile.o commandModeStart.o navigation.o ls.o main.o 
%.o: %.cpp $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

