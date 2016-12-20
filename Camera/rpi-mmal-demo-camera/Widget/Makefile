LIB=libmpu6050widget.a
OBJS=MPU6050_Widget.o

all: $(LIB)

#LDFLAGS+=-L$(SDKSTAGE)/opt/vc/lib/ -lGLESv2 -lEGL -lopenmaxil -lbcm_host -lvcos -lvchiq_arm -lpthread -lrt -L../libs/ilclient -L../libs/vgfont
INCLUDES+=-I/opt/vc/src/hello_pi/libs/vgfont -I/home/pi/git_server/Camera/userland -I/opt/vc/include/interface/vcos/pthreads

CFLAGS+=-DDMP_FIFO_RATE=9 -Wall -g -O2 -lm

%.o: %.c
	@rm -f $@ 
	$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $@ -Wno-deprecated-declarations

%.o: %.cpp
	@rm -f $@ 
	$(CXX) $(CFLAGS) $(INCLUDES) -g -c $< -o $@ -Wno-deprecated-declarations

%.a: $(OBJS)
	$(AR) r $@ $^

#%.bin: $(OBJS)
#	$(CC) -o $@ -Wl,--whole-archive $(OBJS) $(LDFLAGS) -Wl,--no-whole-archive -rdynamic

clean:
	rm -f $(OBJS) $(LIB)
