# definitions.mk

GPP       := 	g++
AR	  :=	ar
HOME_DIR  := 	$(subst /make/definitions.mk,,$(realpath $(lastword $(MAKEFILE_LIST))))
ifneq "$(findstring $(firstword $(MAKEFILE_LIST)), Makefile)" ""
    WORK_DIR := $(subst $(HOME_DIR)/,,$(CURDIR))
else
    WORK_DIR := $(subst /Makefile,,$(subst $(HOME_DIR)/,,$(firstword $(MAKEFILE_LIST))))
endif

ABS_WORK_DIR := $(HOME_DIR)/$(WORK_DIR)

INC_DIRS  =	-Iinclude
SRC_DIR   =	$(ABS_WORK_DIR)
LIB_DIRS  =
LIB_LINK  =
CPPFLAGS  =
ARFLAGS   =	
SRC_FILES =  	$(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES =  	$(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRC_FILES))

BUILD_EXE		=	$(GPP) $^ $(LIB_DIRS) $(LIB_LINK) -o $@
BUILD_AR		=	$(AR) $(ARFLAGS) $@ $^
COMPILE_CPP		=	$(GPP) $(CPPFLAGS) -c $<

MAKE_CPP_SRC 		= 	$(SRC_DIR)/%.cpp

# unit testing
UNITTEST_DIR		=	$(HOME_DIR)/test/UnitTest++
UNITTEST_INC_DIRS  	=	-I$(UNITTEST_DIR)/src \
				-I$(HOME_DIR)/test/include
UNITTEST_SRC_DIR	= 	$(HOME_DIR)/test/src
UNITTEST_TEST_DIR	=       $(ABS_WORK_DIR)/test
UNITTEST_SRC_FILES	= 	$(wildcard $(UNITTEST_TEST_DIR)/*.cpp)
UNITTEST_OBJ_FILES	= 	unittest.o \
				$(patsubst $(UNITTEST_TEST_DIR)/%.cpp, %.o, $(UNITTEST_SRC_FILES))
MAKE_UNITTEST_SRC	=	$(UNITTEST_TEST_DIR)/%.cpp

UNITTEST_CPPFLAGS	=	-g \
				-Wall \
				$(UNITTEST_INC_DIRS)
UNITTEST_LIB_DIRS	=	-L$(UNITTEST_DIR)
UNITTEST_LINK		=	-lUnitTest++
UNITTEST_COMPILE	=	$(GPP) $(UNITTEST_CPPFLAGS) -c $<
UNITTEST_EXE		=	$(GPP) $^ $(UNITTEST_LIB_DIRS) $(UNITTEST_LINK) -o $@

BOOST_INC = /usr/local/include
BOOST_LIB = /usr/local/lib

# declare PHONY
.PHONY : clean

