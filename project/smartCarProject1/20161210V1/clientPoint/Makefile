#LIBS = -lbcm2835
OBJS2 = smartCarClient.o

all: smartCarClient

smartCarClient: $(OBJS2)
	gcc -o $@.exe $(OBJS2) $(LIBS)

clean:
	rm -f smartCarClient.exe $(OBJS2)
