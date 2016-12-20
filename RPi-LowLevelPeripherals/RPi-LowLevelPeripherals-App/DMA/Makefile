LIBS = -lbcm2835 -std=c99
OBJS = test.o
test: $(OBJS)
	gcc -o $@.exe $(OBJS) $(LIBS)
clean:
	rm -f test.exe $(OBJS)
