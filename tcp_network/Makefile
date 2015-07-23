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

SAMPLES_DIR = $(ABS_WORK_DIR)/samples
ECHO_SERVER_DIR = $(SAMPLES_DIR)/echo_server

# targets below
all : libtcp_net.a echo_server

libtcp_net.a : $(OBJ_FILES)
	$(BUILD_AR)

%.o : $(SRC_DIR)/%.cpp
	$(COMPILE_CPP)

echo_server:
	cd $(ECHO_SERVER_DIR) && $(MAKE) all
	
clean :
	rm -f *.o libtcp_net.a
	cd $(ECHO_SERVER_DIR) && $(MAKE) clean
