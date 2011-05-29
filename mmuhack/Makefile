TARGET  = mmuhack
INCLUDE = -I/gp2xsdk/Tools/arm-gp2x-linux/sys-include
CFLAGS  = -O2 -DMODULE -D__KERNEL__ ${INCLUDE}
CC	= arm-linux-gcc

all: ${TARGET}.o

${TARGET}.o: ${TARGET}.c

clean:
	rm -rf ${TARGET}.o

