CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = persona_turk

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LDFLAGS = -lm
else
	LDFLAGS =
endif

all: $(TARGET)

$(TARGET): main.c functions.c functions.h
	$(CC) $(CFLAGS) main.c functions.c -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/$(TARGET)

uninstall:
	rm -f /usr/local/bin/$(TARGET)
