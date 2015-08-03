CC=gcc
GDK=gdk-2.0
CFLAGS=`pkg-config --cflags cairo $(GDK)` -D_GNU_SOURCE -DTRACE -Wall -Wextra
LDLIBS=`pkg-config --libs cairo $(GDK)` -ldl

build: coqidefix.so

clean:
	$(RM) coqidefix.so

help:
	pkg-config --exists gdk-2.0 && echo gdk-2.0

run: build
	LD_PRELOAD=./coqidefix.so coqide Example.v

%.so: %.c
	$(CC) $(CFLAGS) -fpic -o $@ -shared $< $(LDLIBS)

.PHONY: build clean help run
