# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -MMD -MP
LDFLAGS = -lpaho-mqttpp3 -lpaho-mqtt3as

# Directories
SRC_DIR = ..
OBJ_DIR = obj
MQTT_SRC_DIR = $(SRC_DIR)/mqtt_handler
CONFIG_SRC_DIR = $(SRC_DIR)/config_handler
THIRDPARTY_DIR = $(SRC_DIR)/third_party

# Include directories
INCLUDES = -I. -I$(MQTT_SRC_DIR) -I$(CONFIG_SRC_DIR) -I$(THIRDPARTY_DIR)

# Source files
SRCS = main.cpp \
       led_handler.cpp \
       fileHandler.cpp \
       gpio.cpp \
       fileManager.cpp \
       stringFormatter.cpp \
       $(MQTT_SRC_DIR)/mqtt_handler.cpp \
       $(CONFIG_SRC_DIR)/config_handler.cpp

# Object files (place them in the obj directory)
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:%.cpp=%.o))

# Dependency files
DEPS = $(OBJS:.o=.d)

# Output binary
TARGET = led_handler

# Default target
all: $(TARGET)

# Link the binary
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Generic rule to compile all source files into object files
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(MQTT_SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(CONFIG_SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Include dependency files
-include $(DEPS)

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean

