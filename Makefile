#!/usr/bin/env make
CC:= g++
CFLAGS += -g -Wall -Wextra -pedantic -std=c++11 $(shell pkg-config --cflags sdl2)
LDFLAGS := -pthread $(shell pkg-config --libs sdl2) -gtest -gtest_main

SOURCE_DIR := src
TESTS_DIR := tests
BUILD_DIR := build

LIBRARIES_LOCATIONS := -Ldependencies/googletest/build -Ldependencies/googletest/build/googlemock/gtest -Llib -L/usr/local/lib
INCLUDE_LOCATIONS := -Idependencies/googletest/googletest/include -Idependencies/googletest/googlemock/include -I include

SOURCE_EXTENSION := cpp
SOURCES := $(shell find $(SOURCE_DIR) -type f -name "*.$(SOURCE_EXTENSION)") 

TESTS := $(shell find $(TESTS_DIR) -type f -name "*.$(SOURCE_EXTENSION)")

OBJECTS := $(patsubst $(SOURCE_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.$(SOURCE_EXTENSION)=.o)) \
           $(patsubst $(TESTS_DIR)/%,$(BUILD_DIR)/$(TESTS_DIR)/%,$(TESTS:.$(SOURCE_EXTENSION)=.o))


.PHONY: all main clean

all: $(OBJECTS) $(TESTS) 

yage: $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE_LOCATIONS) $(LIBRARIES_LOCATIONS) -o $@ $< 

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.$(SOURCE_EXTENSION)
	@mkdir -p $(shell dirname $@) 
	@tput setf 4
	@tput bold
	@echo "Compiling $@ "
	@tput sgr0
	$(CC) $(CFLAGS) -o $@ -c $(INCLUDE_LOCATIONS) $<

$(BUILD_DIR)/$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.$(SOURCE_EXTENSION)
	@mkdir -p $(shell dirname $@) 
	@tput setf 4
	@tput bold
	@echo "Compiling $@ "
	@tput sgr0
	$(CC) $(CFLAGS) -o $@ -c $(INCLUDE_LOCATIONS) $<


clean: 
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILD_DIR) $(TARGET) "
	$(RM) -r $(BUILD_DIR) $(TARGET)
