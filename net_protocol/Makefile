# Copyright 2015 Terry Seyler.  All rights reserved.
# makefile for net_protocol

include ../make/definitions.mk

CPPFLAGS  +=	-g \
		-Wall \
		$(INC_DIRS)

UNITTEST_INC_DIRS += $(INC_DIRS)
UNITTEST_LINK += -lboost_regex

# redefine SRC_DIR
SRC_DIR   =	$(ABS_WORK_DIR)/src
INC_DIRS  += -I$(BOOST_INC)
LIB_DIRS  += -L$(BOOST_LIB) 
LIB_LINK  += 	-lboost_regex
ARFLAGS   +=	-cru

# targets below
libnet_protocol.a : $(OBJ_FILES) 
	$(BUILD_AR)

%.o : $(MAKE_CPP_SRC)
	$(COMPILE_CPP)

unittest.o : $(UNITTEST_SRC_DIR)/unittest.cpp
	$(UNITTEST_COMPILE)

%.o : $(MAKE_UNITTEST_SRC)
	$(UNITTEST_COMPILE)

unittest : $(UNITTEST_OBJ_FILES) libnet_protocol.a
		$(UNITTEST_EXE)

clean :
	rm -f *.o libnet_protocol.a unittest
