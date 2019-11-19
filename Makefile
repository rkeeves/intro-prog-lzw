# *****************************************************
# Makefile for LzwTree
# Using -MMD to generate dependencies by the compiler
# *****************************************************
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	APP     = lzwtree
else
	APP     = lzwtree.exe
endif
SRC_DIR   = src
BUILD_DIR = ./build
CXX       = g++
CXXFLAGS  = -std=c++14 -Wpedantic -Wall -Wextra -Werror
RM        = rm -f
MKDIR     = mkdir -p
SRCS      = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEPS      = $(OBJS:%.o=%.d)

$(APP) : $(BUILD_DIR)/$(APP)

$(BUILD_DIR)/$(APP): $(OBJS)
	$(MKDIR) -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@

-include $(DEPS)

$(BUILD_DIR)/%.o : %.cpp
	$(MKDIR) -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

.PHONY : clean
clean :
	-rm $(BUILD_DIR)/$(APP) $(OBJS) $(DEPS)