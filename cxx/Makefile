TARGET    := coreutils
OBJS      := main.o \
             cmds/true.o cmds/false.o

CXXFLAGS  := $(CXXFLAGS) -std=c++20 -Wall
LDFLAGS   := $(LDFLAGS)

ifdef OPT
	CXXFLAGS  += -O3
	LDFLAGS   += -Wl,-O2 -Wl,--as-needed -Wl,-S
endif

ifdef STATIC
	LDFLAGS   += -static
endif

.PHONY: all clean

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^
