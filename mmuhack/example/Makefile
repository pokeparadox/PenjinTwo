CXXFLAGS = -O2 -Wall -I..
CC       = arm-linux-gcc
CXX      = arm-linux-g++

TARGET   = hackbench
OBJS     = ${TARGET}.o ../flush_uppermem_cache.o

all: ${TARGET}

${TARGET}: ${OBJS}

.s.o:
	$(CXX) -c -o $@ $^

clean:
	$(RM) ${OBJS} ${TARGET}

