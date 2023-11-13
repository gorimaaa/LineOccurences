bst_dir = ../bst/
holdall_dir = ../holdall/
options_dir = ../options/

CC = gcc
CFLAGS = -std=c18 -g\
  -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings \
  -O2 \
  -I$(bst_dir) -I$(holdall_dir) -I$(options_dir)
vpath %.c $(bst_dir) $(holdall_dir) $(options_dir)
vpath %.h $(bst_dir) $(holdall_dir) $(options_dir)
objects = bst.o main.o holdall.o options.o
executable = lnid
makefile_indicator = .\#makefile\#

.PHONY: all clean

all: $(executable)

clean:
	$(RM) $(objects) $(executable)
	@$(RM) $(makefile_indicator)

$(executable): $(objects)
	$(CC) $(objects) -o $(executable)

bst.o: bst.c bst.h
main.o: main.c bst.h holdall.h
holdall.o: holdall.c holdall.h
options.o: options.c options.h

include $(makefile_indicator)

$(makefile_indicator): makefile
	@touch $@
	@$(RM) $(objects) $(executable)
