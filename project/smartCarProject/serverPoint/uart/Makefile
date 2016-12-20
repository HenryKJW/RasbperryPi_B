LIB=libBCM2835Uart.a
OBJS=uart.o status.o

all: $(LIB)

#LDFLAGS+=-L$(SDKSTAGE)/opt/vc/lib/ -lGLESv2 -lEGL -lopenmaxil -lbcm_host -lvcos -lvchiq_arm -lpthread -lrt -L../libs/ilclient -L../libs/vgfont
#INCLUDES+=-I$(SDKSTAGE)/usr/include/freetype2 -I$(SDKSTAGE)/usr/include -I$(SDKSTAGE)/usr/include/arm-linux-gnueabi

CFLAGS+= -Wall -g -O2

%.o: %.c
	@rm -f $@ 
	$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $@

%.o: %.cpp
	@rm -f $@ 
	$(CXX) $(CFLAGS) $(INCLUDES) -g -c $< -o $@

%.a: $(OBJS)
	$(AR) r $@ $^

clean:
	rm -f $(OBJS) $(LIB)
