# makefile for http-server

include ../../../make/definitions.mk

CPPFLAGS  +=	-g \
		-Wall \
		$(INC_DIRS)

INC_DIRS  +=	-I$(HOME_DIR)/tcp_network/include \
		-I$(HOME_DIR)/net_protocol/include \
		-I$(BOOST_INC)
		
LIB_DIRS  +=	-L$(HOME_DIR)/tcp_network \
		-L$(HOME_DIR)/net_protocol \
		-L$(BOOST_LIB)

LIB_LINK   += 	-ltcp_net \
		-lnet_protocol \
		-lboost_regex \
		-lboost_program_options \
		-lboost_system \
		-lpthread

# targets below
all: http-server

http-server : $(OBJ_FILES)
	$(BUILD_EXE)

%.o : $(MAKE_CPP_SRC)
	$(COMPILE_CPP)

clean :
	rm -f *.o http-server
