TARGET = $(OBJ:.o=_unittest)

CXXFLAGS := -g -Iinclude --std=c++14 -pthread

SRC := $(wildcard *.cpp)
DEP := $(SRC:.cpp=.d)
OBJ := $(SRC:.cpp=.o)

CXXFLAGS += -MMD

all: $(TARGET)

%_unittest: %.o
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	$(RM) *.o *.d *_unittest

cleanall: clean
	$(RM) tags

.PHONY: all clean cleanall
.SECONDARY: $(OBJ)

sinclude $(DEP)
