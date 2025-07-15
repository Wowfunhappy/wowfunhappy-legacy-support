CC = clang
CFLAGS = -Wall -fpic -fvisibility=default
LDFLAGS = -dynamiclib -framework CoreFoundation -framework Security -install_name @rpath/libWowfunhappyLegacySupport.dylib -current_version 1.0 -compatibility_version 1.0

TARGET = libWowfunhappyLegacySupport.dylib
HEADER = WowfunhappyLegacySupport.h
PREFIX ?= /usr/local

all: $(TARGET)

$(TARGET): WowfunhappyLegacySupport.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

install: $(TARGET)
	install -d $(PREFIX)/lib
	install -m 755 $(TARGET) $(PREFIX)/lib
	install -d $(PREFIX)/include
	install -m 644 $(HEADER) $(PREFIX)/include

clean:
	rm -f $(TARGET)