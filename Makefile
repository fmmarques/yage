#!/usr/bin/env make
CC:= g++

CFLAGS += -g -Wall -Wextra -std=c++11 $(shell pkg-config --cflags sdl2)
LDFLAGS := -pthread $(shell pkg-config --libs sdl2) -gtest -gtest_main

SOURCE_DIR := src
TESTS_DIR := tests
BUILD_DIR := build

LIBRARIES_LOCATIONS := -L dependencies/unit_testing/googletest/build/googlemock:dependencies/unit_testing/googletest/build/googlemock/gtest -L lib -L /usr/local/lib
INCLUDE_LOCATIONS := -I dependencies/unit_testing/googletest/include -I include

SOURCE_EXTENSION := cpp
SOURCES := $(shell find $(SOURCE_DIR) -type f -name "*.$(SOURCE_EXTENSION)") 

TESTS := $(shell find $(TESTS_DIR) -type f -name "*.$(SOURCE_EXTENSION)")

OBJECTS := $(patsubst $(SOURCE_DIR)/%,$(BUILD_DIR)/$(SOURCE_DIR)/%,$(SOURCES:.$(SOURCE_EXTENSION)=.o)) \
           $(patsubst $(TESTS_DIR)/%,$(BUILD_DIR)/$(TESTS_DIR)%,$(TESTS:.$(SOURCE_EXTENSION)=.o))


.PHONY: all clean

all: $(OBJECTS) $(TESTS)

main: $(OBJECTS) $(TESTS)
	$(CC) $(CFLAGS) $(LIBRARIES_LOCATIONS) 

$(BUILD_DIR)/$(SRC_DIR)/%.o: $(SOURCE_DIR)/%.$(SOURCE_EXTENSION)
	@mkdir -p $(shell dirname $@) 
	@echo " Compiling $@ "
	$(CC) $(CFLAGS) -o $@ -c $(INCLUDE_LOCATIONS) $<

$(BUILD_DIR)/$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.$(SOURCE_EXTENSION)
	@mkdir -p $(shell dirname $@) 
	@echo " Compiling $@ "
	$(CC) $(CFLAGS) -o $@ -c $(INCLUDE_LOCATIONS) $<


clean: 
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILD_DIR) $(TARGET) "
	$(RM) -r $(BUILD_DIR) $(TARGET)
