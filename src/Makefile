ARCH		= x86_64
ROOTDIR		= $(shell dirname `pwd`)
CC		= gcc
CFLAGS 		= -ggdb -Wall -ansi -pedantic -I$(ROOTDIR)/include
LIB 		= $(ROOTDIR)/lib/libToyOS.a
ARCHDEP		= $(ROOTDIR)/src/arch/$(ARCH)/spinlock.o \
			$(ROOTDIR)/src/arch/$(ARCH)/stack.o
OBJECTS		= $(ARCHDEP) \
			datatypes/structures/list.o \
			datatypes/int.o \
			datatypes/string.o \
			sync/monitor_sl.o \
			sync/semaphore_sl.o \
			system/cores_pthread.o

all: $(LIB)

$(LIB): $(OBJECTS)
	mkdir -p `dirname $(LIB)`
	ar ru $@ $(OBJECTS)
	ranlib $@

$(ROOTDIR)/src/arch/$(ARCH)/spinlock.o:
	as $(ROOTDIR)/src/arch/$(ARCH)/spinlock.s -o \
		$(ROOTDIR)/src/arch/$(ARCH)/spinlock.o

$(ROOTDIR)/src/arch/$(ARCH)/stack.o:
	as $(ROOTDIR)/src/arch/$(ARCH)/stack.s -o \
		$(ROOTDIR)/src/arch/$(ARCH)/stack.o

clean:
	rm -rf `dirname $(LIB)`
	for OBJ in $(shell find | grep .o$$); do rm -f $$OBJ; done
