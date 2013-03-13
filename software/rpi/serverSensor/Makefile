# flags and directives
BINDIR := bin
SRCDIR := src
INCLUDE := include
DEBUG := -g -ggdb
CFLAGS := -Wall -I$(INCLUDE) -O3 -fmessage-length=0 $(DEBUG)
LDFLAGS := -pthread -lrt -lm -lboost_system
CC := arm-linux-gnueabi-g++
#CC := g++
SCP := scp
SSH := sshpass

SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(SRC:.cpp=.o)
OBJ := $(addprefix $(BINDIR)/, $(notdir $(OBJ)))

# target definitions
BIN := $(BINDIR)/$(notdir $(CURDIR))

all: $(BIN)

send: $(BIN)
	$(SSH) -p pk7svh0k $(SCP) $(BIN) root@:/usr/local/bin

slocal: $(BIN)
	$(SSH) -p pk7svh0k $(SCP) $(BIN) root@semmbox.local:/usr/local/bin

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJ)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

distclean:
	rm -f $(BIN) $(OBJ)

.PHONY: send clean distclean

