LIBS = -lbcm2835
OBJS = i2c.o
i2c: $(OBJS)
	gcc -o $@.exe $(OBJS) $(LIBS)
clean:
	rm -f i2c.exe $(OBJS)
