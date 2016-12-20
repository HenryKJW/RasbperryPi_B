app_OBJS = app.o
SIMPLE_OBJS = simple.o

all: app
app: $(app_OBJS)
	gcc -o $@.exe $(app_OBJS)
clean:
	rm -f simple.exe $(app_OBJS)
