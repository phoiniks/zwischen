BINDIR = ../bin
VPATH = src
TARGET = zwischen
OBJS = zwischen.o
CC = gcc
CFLAGS = -std=c11 -Wall $(shell pkg-config --cflags sqlite3) -ggdb3
LDFLAGS = -lpthread -ldl
LDLIBS = $(shell pkg-config --libs sqlite3)

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBS);
	strip $(TARGET);
	mv $(TARGET) $(BINDIR);
	rm $(OBJS)
