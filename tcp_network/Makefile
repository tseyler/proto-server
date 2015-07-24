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
	
clean_echo_server :
	cd $(ECHO_SERVER_DIR) && $(MAKE) clean
	
echo_client :
	cd $(ECHO_CLIENT_DIR) && $(MAKE) all
	
clean_echo_client :
	cd $(ECHO_CLIENT_DIR) && $(MAKE) clean
	
http_server :
	cd $(HTTP_SERVER_DIR) && $(MAKE) all
	
clean_http_server : 
	cd $(HTTP_SERVER_DIR) && $(MAKE) clean
	
control4_server :
	cd $(CTRL4_SERVER_DIR) && $(MAKE) all
	
clean_control4_server :
	cd $(CTRL4_SERVER_DIR) && $(MAKE) clean
	
clean_all : clean clean_echo_server clean_echo_client clean_http_server clean_control4_server 

clean :
	rm -f *.o libtcp_net.a

