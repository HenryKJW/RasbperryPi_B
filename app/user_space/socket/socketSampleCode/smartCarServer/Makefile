#LIBS = -lbcm2835
PAR1  = -lpthread
OBJS1 = smartCarService.o
OBJS3 = multi-ConnectServer.o

all: smartCarService multi-ConnectServer

smartCarService: $(OBJS1)
	gcc -o $@.exe $(OBJS1) $(LIBS)

multi-ConnectServer: $(OBJS3)
	gcc -o $@.exe $(OBJS3) $(LIBS) $(PAR1)

clean:
	rm -f smartCarService.exe multi-ConnectServer.exe $(OBJS1) $(OBJS3)
