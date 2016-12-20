blk_OBJS = blk.o
nonblk_OBJS = nonblk.o
poll_OBJS = poll.c
select_OBJS = select.c


all: blk nonblk poll select
blk: $(blk_OBJS)
	gcc -o $@.exe $(blk_OBJS)

nonblk: $(nonblk_OBJS)
	gcc -o $@.exe $(nonblk_OBJS)

poll: $(poll_OBJS)
	gcc -o $@.exe $(poll_OBJS)

select: $(select_OBJS)
	gcc -o $@.exe $(select_OBJS)

clean:
	rm -f simple.exe $(blk_OBJS) $(nonblk_OBJS) &(poll_OBJS) $(select_OBJS)
