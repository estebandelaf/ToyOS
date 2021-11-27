ROOTDIR		= $(shell pwd)/../..
CC		= gcc
CFLAGS		= -ggdb -Wall -ansi -pedantic -I$(ROOTDIR)/include -lpthread
LIB		= $(ROOTDIR)/lib/libdSystem.a

all: $(APP)

$(APP): $(APP).o
	$(CC) $(CFLAGS) $(APP).o -o $(APP) $(LIB)

clean:
	rm -f *.o *~ $(APP)
