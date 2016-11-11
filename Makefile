
CC := g++
LIBS += -lpthread
CPPFLAGS += -std=c++11

cppsrc := $(shell find -name "*.cpp")
csrc := $(shell find -name "*.c")

obj := $(csrc:.c=.o)
obj += $(cppsrc:.cpp=.o)

target := lm.bin

all: $(target)

$(target): $(obj)
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm *.o $(target) -rf
