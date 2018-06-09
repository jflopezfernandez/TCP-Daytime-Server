
###############################################################################
#
#
#                         DAYTIME SERVER SERVICE DAEMON
#
#
###############################################################################

vpath %.c src
vpath %.h include

CC       := gcc

CPPFLAGS := -I include
CFLAGS   := -std=c11 -Wall -Wextra -pedantic

COMPILE  := $(CC) $(CPPFLAGS) $(CFLAGS)

SOURCES  := main.c \
	          error.c

OBJECTS  := $(patsubst %.c,%.o,$(SOURCES))

PROGRAM  := echo

$(PROGRAM): $(OBJECTS)
	$(COMPILE) -o $@ $^

#$(OBJECTS): $(SOURCES)
#	$(COMPILE) -c -o $@ $^

%.o: %.c
	$(COMPILE) -c -o $@ $^

clean:
	rm -rf *.o $(PROGRAM)

