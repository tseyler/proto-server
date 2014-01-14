# makefile for control4-server

include ../../../make/definitions.mk

CPPFLAGS  +=	-g \
		-Wall \
		$(INC_DIRS)

INC_DIRS  +=	-I$(HOME_DIR)/tcp_network/include \
		-I$(HOME_DIR)/net_protocol/include

LIB_DIRS  +=	-L$(HOME_DIR)/tcp_network \
		-L$(HOME_DIR)/net_protocol

LIB_LINK   += 	-ltcp_net \
		-lnet_protocol \
		-lboost_regex \
		-lboost_program_options \
		-lboost_system \
		-lpthread

# targets below

control4-server : $(OBJ_FILES)
	$(BUILD_EXE)

%.o : $(MAKE_CPP_SRC)
	$(COMPILE_CPP)

clean :
	rm -f *.o control4-server
