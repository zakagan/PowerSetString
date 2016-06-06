#~ PowerSetString Makefile ~#


### Definitions Section ###

# Name of the executable to create
EXECUTABLE = PowerSetString
SOURCE_DIR = src
OBJECT_DIR= build

# The command to run for the C++ compiler (here used for C) and linker
CC = gcc

# Basic compiler arguments
CFLAGS = -g -c -Wall
	
# Basic linker arguments
LDFLAGS = -g

OBJECTS = PowerSetString.o HashMap.o SinglyLinkedList.o WordSort.o Parsing.o
OBJ_FILES = $(addprefix $(OBJECT_DIR)/, $(OBJECTS))

# Create the object_files directory only if it does not exist. 
	
all: setup $(EXECUTABLE)

rebuild: clean all

setup: | $(OBJECT_DIR)	

$(OBJECT_DIR):
	mkdir -p $@	

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -rf $(OBJECT_DIR) $(EXECUTABLE)


