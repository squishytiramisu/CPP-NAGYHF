PROG = main
###CFILES = econio.c
PROG_O = $(PROG).o alapanyag.o Koktel.o koktel_tarolo.o  menurendszer.o econio.o
PROG_H = alapanyag.h Koktel.h koktel_tarolo.h menurendszer.h econio.h gtest_lite.h


MTRACE_O = memtrace.o
MTRACE_H = memtrace.h

CXX= g++

CXXFLAGS= -pedantic -Wall -DMEMTxdRACE -g
LDFLAGS = -g

OBJS = $(PROG_O) $(MTRACE_O)
HEADS = $(PROG_H) $(MTRACE_H)
LIBS= $(PROG_L) $(MEMCHK_L)

.PHONY: all
all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)

##$(OBJS):$(HEADS)

.phony: run
run:$(PROG)
	./$(PROG)
