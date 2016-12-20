LIBS = -L../../lib/ -lbcm2835
OBJS = pwm.o
pwm: $(OBJS)
	gcc -o $@.exe $(OBJS) $(LIBS)
clean:
	rm -f pwm.exe $(OBJS)
