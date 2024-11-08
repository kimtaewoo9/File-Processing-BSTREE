SHELL		= /bin/bash
TARGET		= test_exe

CXX			= clang++
CXXFLAGS	= -Wall -Wextra -Werror -O3 -I. -x c++ -std=c++20
LDFLAGS		= 
RM			= rm -f

ifdef SANITIZE
	CXXFLAGS += -g3
	LDFLAGS += -fsanitize=address
endif

${TARGET}:
	@${CXX} ${CXXFLAGS} -o ${TARGET} main.cpp __tree ${LDFLAGS}

all: ${TARGET}

__bstree:
	@cp __bstree/__tree .
	@${MAKE} all

__avltree:
	@cp __avltree/__tree .
	@${MAKE} all

__btree:
	@cp __btree/__tree .
	@${MAKE} all

clean:
	@${RM} *.o __tree

fclean: clean
	@${RM} ${TARGET}

.PHONY: __bstree __avltree __btree clean fclean

.NOTPARALLEL: __bstree __avltree __btree clean fclean