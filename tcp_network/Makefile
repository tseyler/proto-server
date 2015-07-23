# makefile for libtcp_net

include ../make/definitions.mk

CPPFLAGS  +=	-g \
		-Wall \
		$(INC_DIRS)

# redefine SRC_DIR
SRC_DIR   =	$(ABS_WORK_DIR)/src
INC_DIRS  += -I$(BOOST_INC)
LIB_DIRS  += -L$(BOOST_LIB)
ARFLAGS   +=	-cru

# targets below
all : libtcp_net.a

libtcp_net.a : $(OBJ_FILES)
	$(BUILD_AR)

%.o : $(SRC_DIR)/%.cpp
	$(COMPILE_CPP)

clean :
	rm -f *.o libtcp_net.a
