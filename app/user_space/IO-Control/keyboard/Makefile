#LIBS = -lbcm2835
OBJS2 = keyboard.o

all: keyboard

keyboard: $(OBJS2)
	gcc -o $@.run $(OBJS2) $(LIBS)

clean:
	rm -f keyboard.run $(OBJS2)
