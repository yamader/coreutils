TARGET  := coreutils
OBJS    := main.o

.PHONY: all clean

all: $(TARGET)
clean:
	rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<
