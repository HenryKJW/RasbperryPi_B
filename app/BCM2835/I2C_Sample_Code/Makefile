LIBS = -lbcm2835
OBJS = BCM2835_i2c.o
BCM2835_i2c: $(OBJS)
	gcc -o $@.exe $(OBJS) $(LIBS)
clean:
	rm -f BCM2835_i2c.exe $(OBJS)
