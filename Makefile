###############################################################
#                          m-boot
# Version : 1.0
# Edit by : Makefiler
# Time    : 2013-12-19
# Function: compile the mboot. 
#
###############################################################

include $(CURDIR)/config.mk

.PHONY : all
all : mboot.bin

mboot.bin : $(OBJS_ASM) $(OBJS_C)
	$(LD) $(LDFLAGS) mboot_elf $^
	$(OBJCOPY) -O binary -S mboot_elf $@
	$(OBJDUMP) -h -t -D -m arm  mboot_elf > mboot.dis

.PHONY : clean
clean: 
	$(RM) -f *.o *.bin *.dis mboot_elf
