obj-m += hello.o

all:
	make -C kernelsourcedir/linux-3.14 M=$(PWD)	modules

clean:
	make -C kernelsourcedir/linux-3.14 M=$(PWD)	clean