.PHONY: clean install uninstall

CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -O2
PREFIX ?= /usr
BINDIR ?= $(PREFIX)/bin
MANDIR ?= $(PREFIX)/share/man/man1

TARGET = errexit
SOURCE = errexit.c
MANPAGE = errexit.1

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $<

install: $(TARGET)
	install -Dm755 $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)
	install -Dm644 $(MANPAGE) $(DESTDIR)$(MANDIR)/$(MANPAGE)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)
	rm -f $(DESTDIR)$(MANDIR)/$(MANPAGE)

clean:
	rm -f $(TARGET)
