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

# variables to build source in samples dir
SAMPLES_DIR = $(ABS_WORK_DIR)/samples
ECHO_SERVER_DIR = $(SAMPLES_DIR)/echo_server
ECHO_CLIENT_DIR = $(SAMPLES_DIR)/echo_client
HTTP_SERVER_DIR = $(SAMPLES_DIR)/http_server
CTRL4_SERVER_DIR = $(SAMPLES_DIR)/control4_server

# targets below
all : libtcp_net.a echo_server echo_client http_server control4_server

libtcp_net.a : $(OBJ_FILES)
	$(BUILD_AR)

%.o : $(SRC_DIR)/%.cpp
	$(COMPILE_CPP)

echo_server :
	cd $(ECHO_SERVER_DIR) && $(MAKE) all
	
echo_client :
	cd $(ECHO_CLIENT_DIR) && $(MAKE) all

http_server :
	cd $(HTTP_SERVER_DIR) && $(MAKE) all
	
control4_server :
	cd $(CTRL4_SERVER_DIR) && $(MAKE) all
	
clean :
	rm -f *.o libtcp_net.a
	cd $(ECHO_SERVER_DIR) && $(MAKE) clean
	cd $(ECHO_CLIENT_DIR) && $(MAKE) clean
	cd $(HTTP_SERVER_DIR) && $(MAKE) clean
	cd $(CTRL4_SERVER_DIR) && $(MAKE) clean
