# makefile for libtcp_net

include ../make/definitions.mk


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


ifeq ($(debug),$(ONE_VAL))
	CPPFLAGS  += -g -Wall $(INC_DIRS)
else
	CPPFLAGS  += -Wall $(INC_DIRS)
endif

# targets below
help :
	@echo Possible targets are:
	@echo all
	@echo clean_all
	@echo libtcp_net
	@echo clean
	@echo echo_server
	@echo clean_echo_server
	@echo echo_client
	@echo clean_echo_client
	@echo http_server
	@echo clean_http_server
	@echo control4_server
	@echo clean_control4_server

	
all : libtcp_net echo_server echo_client http_server control4_server
	
libtcp_net : libtcp_net.a

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

%.o : $(SRC_DIR)/%.cpp
	$(COMPILE_CPP)
	
libtcp_net.a : $(OBJ_FILES)
	$(BUILD_AR)
clean :
	rm -f *.o libtcp_net.a

