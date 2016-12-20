#all: pifm pifm_new

LIBS = -lm -std=c99
OBJS = pifm.c
#OBJS_New = pifm_new.c
pifm: $(OBJS)
	gcc -o $@.exe $(OBJS) $(LIBS)

#pifm_new: $(OBJS)
#	gcc -o $@.exe $(OBJS_New) $(LIBS)

clean:
	rm -f pifm.exe pifm_new.exe
