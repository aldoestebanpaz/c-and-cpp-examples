TARGET = using-c-from-cpp-example

SDIR = src
CSOURCES = $(shell find $(SDIR) -type f -iname *.cpp)

ODIR = obj
OBJECTS = $(patsubst $(SDIR)/%,$(ODIR)/%,$(CSOURCES:.cpp=_cpp.o))

CC = g++
LD = g++
LDFLAGS =
DBGFLAGS = -g -O0
CFLAGS = -std=c++17 $(DBGFLAGS) -W -Wall  -Wextra -Werror -pedantic
LIBS =
# -lpthread

.PHONY: all clean

all: $(ODIR)/$(TARGET)

$(ODIR)/$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

$(ODIR)/%_cpp.o: $(SDIR)/%.cpp
	@test -d $(ODIR) || mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm $(OBJECTS) $(ODIR)/$(TARGET)
