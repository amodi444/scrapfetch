PREFIX ?= /usr
BINDIR ?= $(PREFIX)/bin

all: scrapfetch

scrapfetch: scrapfetch.c
	gcc -o scrapfetch scrapfetch.c

install: scrapfetch
	install -Dm755 scrapfetch $(DESTDIR)$(BINDIR)/scrapfetch

clean:
	rm -f scrapfetch
