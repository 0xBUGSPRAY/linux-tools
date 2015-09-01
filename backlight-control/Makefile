
CC = gcc
CFLAGS = -g -Wall
LDLIBS = -lm

OBJS = main.o argparse.o

main: $(OBJS)

install: main
	rm -rf /usr/bin/backlightctl
	mv main backlightctl
	cp backlightctl /usr/bin/backlightctl
	chown root:root /usr/bin/backlightctl
	chmod 4755 /usr/bin/backlightctl

uninstall:
	rm -rf /usr/bin/backlightctl
	rm -rf backlightctl

clean:
	rm -rf main.o argparse.o main


