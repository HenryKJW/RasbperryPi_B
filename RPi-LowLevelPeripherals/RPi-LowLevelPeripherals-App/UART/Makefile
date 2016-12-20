LIBS = -lbcm2835
OBJS = uart.o
uart: $(OBJS)
	gcc -o $@.exe $(OBJS) $(LIBS)
clean:
	rm -f uart.exe $(OBJS)
