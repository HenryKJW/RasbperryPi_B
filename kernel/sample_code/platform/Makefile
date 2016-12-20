
EXTRA_CFLAGS += -Wall
CFILES = globalfifo.c 

obj-m += globalfifo.o
global-objs := $(CFILES:.c=.o)

all:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

