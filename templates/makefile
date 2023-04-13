# Makefile for symkit 1.0 by Raffaele Ancarola 
# C++ library for physics symulations

NAME := symkit
BIN := bin/lib$(NAME).so
CC := g++
CPP11 := -std=c++11

DIRS := graph engine
BACKUP := backup
INSTALL_DIR := /usr/lib

INCLUDES := include

# other required libraries
LIBS := #add libraries

SRC := $(wildcard $(patsubst %,%/*.cpp,$(DIRS)))
OBJ := $(patsubst %.cpp,bin/%.o,$(SRC))

.PHONY: dirs clean install backup restore
all: $(BIN)

# builds all binaries into the shared library

$(BIN): dirs $(OBJ) 
	@printf "\nAssembling binaries\n\n"
	$(CC) -shared -o $@ $(OBJ) $(INCLUDES) $(LIBS) $(CPP11)
	@printf "\nCompilation successfully completed\n"

# compile all sources

$(OBJ): bin/%.o : %.cpp $(SRC)
	@printf "\nCompiling $<\n"
	$(CC) -c $< -fPIC -o $@ $(INCLUDES) $(CPP11)

# phony commands implementation

# install the compiled library into your system
# be careful with this command because it could not work
install:
	chmod +x install.sh
	./install.sh $(BIN) $(INSTALL_DIR)

# generate all necessaries directories
dirs:
	mkdir -p bin $(patsubst %,bin/%,$(DIRS))
	mkdir -p $(patsubst %,%/include,$(DIRS)) $(BACKUP)
	@printf "Default directories created\n"

# clean all binaries
clean:
	rm -rfv bin/*
	@printf "Binary files cleaned\n"

# backup the project in backup/symkit.zip
backup:
	mkdir -p $(BACKUP)
	rm -rfv $(BACKUP)/*
	zip -r $(BACKUP)/symkit.zip $(DIRS)
	@printf "Backup completed\n"

# restore the last backup, backup/symkit.zip must be present
restore:
	unzip $(BACKUP)/symkit.zip -d $(BACKUP)
	rm -rfv $(DIRS)
	mv $(patsubst %,$(BACKUP)/%,$(DIRS)) . 
	@printf "Backup restored\n"

