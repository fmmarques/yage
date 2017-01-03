#!/usr/bin/env make
CC:= g++

CFLAGS:= -std=c++11 -g $(shell pkg-config --cflags sdl2) 

SOURCE_DIR := src
BUILD_DIR := build
LIBRARIES_DIR := -L lib -L /usr/local/lib
INCLUDE_DIR := -I include

TARGET := $(BUILD_DIR)/arkanoid

SOURCE_EXTENSION := cpp
SOURCES := $(shell find $(SOURCE_DIR) -type f -name "*.$(SOURCE_EXTENSION)") 

OBJECTS := $(patsubst $(SOURCE_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.$(SOURCE_EXTENSION)=.o))

LIBRARIES := -pthread $(shell pkg-config --libs sdl2) 

.PHONY: clean

$(TARGET): $(OBJECTS)
	@echo " Linking $@ "
	$(CC) $^ -o $@ $(LIBRARIES)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.$(SOURCE_EXTENSION)
	@mkdir -p $(shell dirname $@) 
	@echo " Compiling $@ "
	$(CC) $(CFLAGS) -o $@ -c $(INCLUDE_DIR) $<

clean: 
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILD_DIR) $(TARGET) "
	$(RM) -r $(BUILD_DIR) $(TARGET)
