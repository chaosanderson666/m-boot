#
# Include the make variables (CC, etc...)
#

SHELL = /bin/sh

.SUFFIXES: 
.SUFFIXES:.S .c .o

CROSS_COMPILE = arm-linux-

AS	= $(CROSS_COMPILE)as
LD	= $(CROSS_COMPILE)ld
CC	= $(CROSS_COMPILE)gcc
AR	= $(CROSS_COMPILE)ar
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

OBJS_ASM := $(patsubst %.S,%.o,$(wildcard *.S))
OBJS_C   := $(patsubst %.c,%.o,$(wildcard *.c))

override CFLAGS  += -nostdlib -Wall -c -o
override LDFLAGS += -Tboot.lds -o

%.o:%.c
	$(CC) $(CFLAGS) $@ $^
%.o:%.S
	$(CC) $(CFLAGS) $@ $<