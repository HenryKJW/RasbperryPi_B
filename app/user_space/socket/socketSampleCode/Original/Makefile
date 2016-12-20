#LIBS = -lbcm2835
PAR1  = -lpthread
OBJS1 = smartCarService.o
OBJS2 = smartCarClient.o
OBJS3 = multi-ConnectServer.o

all: smartCarService smartCarClient multi-ConnectServer

smartCarService: $(OBJS1)
	gcc -o $@.exe $(OBJS1) $(LIBS)

smartCarClient: $(OBJS2)
	gcc -o $@.exe $(OBJS2) $(LIBS)

multi-ConnectServer: $(OBJS3)
	gcc -o $@.exe $(OBJS3) $(LIBS) $(PAR1)

clean:
	rm -f smartCarService.exe smartCarClient.exe multi-ConnectServer.exe $(OBJS1) $(OBJS2) $(OBJS3)
