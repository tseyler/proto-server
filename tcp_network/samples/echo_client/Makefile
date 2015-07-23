# 	Copyright 2015 Terry Seyler.  All rights reserved.

# makefile for echo-client

include ../../../make/definitions.mk

CPPFLAGS  +=	-g \
		-Wall \
		$(INC_DIRS)
INC_DIRS  += -I$(BOOST_INC)
LIB_DIRS  += -L$(BOOST_LIB)
LIB_LINK  += -lboost_system -lboost_program_options -lpthread

# targets below
all: echo-client

echo-client : $(OBJ_FILES)
	$(BUILD_EXE)

%.o : $(MAKE_CPP_SRC)
	$(COMPILE_CPP)

clean :
	rm -f *.o echo-client
