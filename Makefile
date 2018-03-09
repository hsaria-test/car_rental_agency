
TARGET=libcarrentalagency.a

MAKEFILE_DIR = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
SRC_DIR = $(MAKEFILE_DIR)/src

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

CXX=g++
CPPFLAGS=-std=c++11 -Wall -I$(SRC_DIR)
LDFLAGS=-L/usr/local/lib -lgtest -lgtest_main -lpthread

$(TARGET): $(OBJS)
	@echo $(OBJS) $(SRC_DIR)
	$(AR) -rc $@ $^
 
clean:
	$(RM) $(TARGET)
	$(RM) $(OBJS)


TEST_DIR = $(MAKEFILE_DIR)/unit_test
TEST_SRCS = $(SRCS) $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst %.cpp,%.o,$(TEST_SRCS))
TEST_TARGET = test

.PHONY: unit_test
unit_test: $(TEST_TARGET) 
	./$^

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) -o $@ $(TEST_OBJS) $(CPPFLAGS) $(LDFLAGS)
