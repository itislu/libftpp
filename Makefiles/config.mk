ifndef CONFIG_MK
CONFIG_MK		:=	1

include				$(shell git rev-parse --show-toplevel)/Makefiles/setup.mk
include				$(MAKEFILES_DIR)/print.mk


# ************************* DEFAULT CONFIGURATION **************************** #

MSG_PROGRESS	?=	"🔨"
COLOR_MAKE		?=	$(STY_GRE)
IS_LIB			?=	$(if $(filter %.a,$(NAME)),true)
LIBS_LOCAL		?=	
LIBS_EXTERN		?=	
CPPFLAGS		?=	


# ************************** BUILD CONFIGURATION ***************************** #

#	Dependencies

BUILDFILES		=	$(filter-out %.d,$(MAKEFILE_LIST))


#	Directories

SRC_DIR			:=	src
LIB_ROOT_DIR	:=	$(REPO_ROOT)/lib
LIB_DIRS		:=	$(dir $(LIBS_LOCAL))
INC_DIRS		:=	inc $(SRC_DIR) $(LIB_ROOT_DIR)
BUILD_DIR		:=	build
OBJ_DIR			:=	$(BUILD_DIR)/_obj
DEP_DIR			:=	$(BUILD_DIR)/_dep
DOC_DIR			:=	docs
DOCKER_DIR		:=	$(REPO_ROOT)/docker


#	Flags

MAKEFLAGS		+=	--jobs
CXX				:=	c++
CXX_VERSION		:=	$(shell $(CXX) --version | head -1)
IS_CLANG		:=	$(if $(findstring clang,$(CXX_VERSION)),true)
IS_GCC			:=	$(if $(findstring g++,$(CXX_VERSION)),true)
CXXFLAGS_STD	:=	-Wall -Wextra -Werror -Wpedantic -Wshadow -std=c++98
CXXFLAGS_DBG	:=	-ggdb3
CXXFLAGS_SAN	:=	-fsanitize=address,undefined,bounds,float-divide-by-zero
CXXFLAGS_OPT	:=	-O3 -flto$(if $(IS_GCC),=auto)
CXXFLAGS_CLANG	:=	-Wdocumentation	# Only supported by clang
CXXFLAGS		?=	$(CXXFLAGS_STD) $(CXXFLAGS_DBG) $(if $(IS_CLANG),$(CXXFLAGS_CLANG))
CPPFLAGS_OPT	:=	-D NDEBUG
CPPFLAGS		+=	$(addprefix -I,$(INC_DIRS))
DEPFLAGS		=	-M -MP -MF $@ -MT "$(OBJ_DIR)/$*.o $@"
LDFLAGS			:=	$(addprefix -L,$(LIB_DIRS))
LDLIBS			:=	$(addprefix -l,$(patsubst lib%,%,$(notdir $(basename $(LIBS_LOCAL))) $(LIBS_EXTERN)))
AR				:=	ar
ARFLAGS			:=	rcs


#	Files

SRC_EXTENSION	:=	.cpp
SRC				:=	$(shell find $(SRC_DIR) -type f -name "*$(SRC_EXTENSION)")


#	Valgrind

VALGRIND		:=	$(shell which valgrind 2>/dev/null || echo "valgrind")

VALGRINDFLAGS	=	--errors-for-leak-kinds=all \
					--leak-check=full \
					--show-error-list=yes \
					--show-leak-kinds=all \
					--trace-children=yes \
					--track-origins=yes

VALGRINDFDFLAGS	:=	--track-fds=all


#	Terminal

TERMINAL		?=	$(if $(shell command -v gnome-terminal),gnome-terminal,\
					$(if $(shell command -v terminator),terminator,\
					$(if $(shell command -v xterm),xterm,\
					)))

TERMINALTITLE	:=	$(if $(filter val,$(MAKECMDGOALS)),valgrind $(NAME),\
					$(if $(filter valfd,$(MAKECMDGOALS)),valgrind-fd $(NAME),\
					$(NAME)))

TERMINALFLAGS	?=	$(if $(filter gnome-terminal,$(TERMINAL)),--title="$(TERMINALTITLE)" --,\
					$(if $(filter terminator,$(TERMINAL)),--title="$(TERMINALTITLE)" -x,\
					$(if $(filter xterm,$(TERMINAL)),-title "$(TERMINALTITLE)" -e,\
					)))


#	Requirements

ifndef NAME
    $(error NAME is not defined)
endif


#	Default targets

.DEFAULT_GOAL	:=	all

.DEFAULT		:
					$(call PRINTLN,"$(MSG_UNKNOWN)")
					$(call PRINTLN,"$(MSG_TRY_HELP)")
					exit 2


endif
