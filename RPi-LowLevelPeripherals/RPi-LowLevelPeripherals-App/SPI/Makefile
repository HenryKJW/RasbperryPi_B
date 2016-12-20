LIBS = -lbcm2835
OBJS = spi.o
spi: $(OBJS)
	gcc -o $@.exe $(OBJS) $(LIBS)
clean:
	rm -f spi.exe $(OBJS)
