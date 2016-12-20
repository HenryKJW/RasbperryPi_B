# You need to "sudo apt-get install libgtkmm-3.0-dev" to build the demo_3d binary

all: myarea

MYAREA_OBJS = myarea.o main.o

CXXFLAGS = -DDMP_FIFO_RATE=9 -Wall -g -O2 `pkg-config gtkmm-3.0 --cflags --libs`

myarea: $(MYAREA_OBJS)
	$(CXX) -o $@ $^ -lm `pkg-config gtkmm-3.0 --cflags --libs`

# 'make test_3d' will give you a test_3d that is controlled via the keyboard rather
# than by moving the MPU6050.  Use the keys x, X, y, Y, z, Z, and q to exit.
# Note it is the terminal you invoked the binary from that is listening for the
# keyboard, not the window with the wireframe in it, so make sure the terminal
# has input focus.
clean:
	rm -f $(MYAREA_OBJS) myarea
