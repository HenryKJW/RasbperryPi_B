LIB=libmpu6050.a
OBJS=I2Cdev.o MPU6050.o demo_dmp.o

all: $(LIB)

#LDFLAGS+=-L$(SDKSTAGE)/opt/vc/lib/ -lGLESv2 -lEGL -lopenmaxil -lbcm_host -lvcos -lvchiq_arm -lpthread -lrt -L../libs/ilclient -L../libs/vgfont
#INCLUDES+=-I$(SDKSTAGE)/usr/include/freetype2 -I$(SDKSTAGE)/usr/include -I$(SDKSTAGE)/usr/include/arm-linux-gnueabi

CFLAGS+=-DDMP_FIFO_RATE=9 -Wall -g -O2

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