# makefile for c4-console

include ../make/definitions.mk

CPPFLAGS  +=	-g \
		-Wall \
		$(INC_DIRS)

LIB_LINK   +=   -lboost_system \
		-lboost_program_options \
		-lpthread

# targets below

c4-console : $(OBJ_FILES)
	$(BUILD_EXE)

%.o : $(MAKE_CPP_SRC)
	$(COMPILE_CPP)

clean :
	rm -f *.o c4-console
