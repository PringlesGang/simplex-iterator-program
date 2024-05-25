INC_DIR = ./
SRC_DIR = ./
SOURCES = $(sort $(shell find $(SRC_DIR) -name '*.cpp'))
OBJECTS = $(SOURCES:.cpp=.o)
DEPS = $(OBJECTS:.o=.d)
TARGET = simplex
CXX = g++
CFLAGS = -Wall -Wextra -Wpedantic -std=c++11
CPPFLAGS = $(addprefix -I, $(INC_DIR))

.PHONY: all clean debug release
release: CFLAGS += -O3 -DNDEBUG
release: all
debug: CFLAGS += -O0 -DDEBUG -ggdb3
debug: all
all: $(TARGET)
clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET)
$(TARGET): $(OBJECTS)
	$(CXX) $(CFLAGS) $(CPPFLAGS) -o $@ $^
-include $(DEPS)
%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -MMD -o $@ -c $<
