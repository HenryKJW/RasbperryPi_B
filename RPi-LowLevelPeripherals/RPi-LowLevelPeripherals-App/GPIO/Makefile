LIBS = -lbcm2835
OBJS = GpioControl.o
GpioControl: $(OBJS)
	gcc -o $@.exe $(OBJS) $(LIBS)
clean:
	rm -f GpioControl.exe $(OBJS)
