FORK_OBJS = fork.o
SIMPLE_OBJS = simple.o

all: simple fork
simple: $(SIMPLE_OBJS)
	gcc -o $@.exe $(SIMPLE_OBJS)
fork: $(FORK_OBJS)
	gcc -o $@.exe $(FORK_OBJS)
clean:
	rm -f simple.exe fork.exe $(simple) $(fork)
