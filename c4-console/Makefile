# Copyright 2015 Terry Seyler.  All rights reserved.
# makefile for c4-console

include ../make/definitions.mk

ifeq ($(debug),$(ONE_VAL))
	CPPFLAGS  += -g -Wall $(INC_DIRS)
else
	CPPFLAGS  += -Wall $(INC_DIRS)
endif

INC_DIRS  += -I$(BOOST_INC)
LIB_DIRS  += -L$(BOOST_LIB)
LIB_LINK  += -lboost_system -lboost_program_options -lpthread

# targets below
all : c4-console

c4-console : $(OBJ_FILES)
	$(BUILD_EXE)

%.o : $(MAKE_CPP_SRC)
	$(COMPILE_CPP)

clean :
	rm -f *.o c4-console
