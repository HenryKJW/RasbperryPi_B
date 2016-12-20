app_OBJS = app.o

all: app
app: $(app_OBJS)
	gcc -o $@.exe $(app_OBJS)
clean:
	rm -f app.exe $(app_OBJS)
