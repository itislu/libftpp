# ******************************* MAKE SETUP ********************************* #

SHELL			:=	/bin/bash
PWD				:=	$(shell pwd)
GLOBAL_MK		:=	$(abspath $(lastword $(MAKEFILE_LIST)))
REPO_ROOT		:=	$(patsubst %/,%,$(dir $(GLOBAL_MK)))
REPO_ROOT_REL	:=	$(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
REPO_SUBDIR		:=	$(patsubst /%,%,$(subst $(REPO_ROOT),,$(PWD)))


# ************************* DEFAULT CONFIGURATION **************************** #

ifeq ($(words $(MAKEFILE_LIST)), 1)
    $(error This Makefile can only be included by other Makefiles)
endif

ifndef NAME
    $(error NAME is not defined)
endif

MSG_PROGRESS	?=	"🔨"
COLOR_MAKE		?=	STY_GRE


# ************************** GLOBAL CONFIGURATION **************************** #

#	Directories

SRC_DIR			:=	src
INC_DIRS		:=	inc $(SRC_DIR)
BUILD_DIR		:=	build
OBJ_DIR			:=	$(BUILD_DIR)/_obj
DEP_DIR			:=	$(BUILD_DIR)/_dep


#	Dependencies

BUILDFILES		:=	Makefile $(GLOBAL_MK)


#	Flags

CXX				:=	c++
CXX_VERSION		:=	$(shell $(CXX) --version | head -1)
IS_CLANG		:=	$(if $(findstring clang,$(CXX_VERSION)), true)
CXXFLAGS_STD	:=	-Wall -Wextra -Werror -Wshadow --std=c++98 -pedantic
CXXFLAGS_DBG	:=	-ggdb3
CXXFLAGS_SAN	:=	-fsanitize=address,undefined,bounds,float-divide-by-zero
CXXFLAGS_OPT	:=	-O3
CXXFLAGS_CLANG	:=	-Wdocumentation	# Only supported by clang
CXXFLAGS		?=	$(CXXFLAGS_STD) $(CXXFLAGS_DBG) $(if $(IS_CLANG), $(CXXFLAGS_CLANG))
CPPFLAGS		+=	$(addprefix -I,$(INC_DIRS))
DEPFLAGS		=	-M -MP -MF $@ -MT "$(OBJ_DIR)/$*.o $@"
MAKEFLAGS		+=	-j -s


#	Valgrind

VALGRIND		:=	$(shell which valgrind)

VALGRINDFLAGS	=	--errors-for-leak-kinds=all \
					--leak-check=full \
					--show-error-list=yes \
					--show-leak-kinds=all \
					--trace-children=yes \
					--track-origins=yes

VALGRINDFDFLAGS	:=	--track-fds=all


#	Terminal

TERMINAL		?=	$(if $(shell command -v gnome-terminal), gnome-terminal, \
					$(if $(shell command -v terminator), terminator, \
					$(if $(shell command -v xterm), xterm, \
					)))

TERMINALTITLE	:=	$(if $(filter val,$(MAKECMDGOALS)), valgrind $(NAME), \
					$(if $(filter valfd,$(MAKECMDGOALS)), valgrind-fd $(NAME), \
					$(NAME)))

TERMINALFLAGS	?=	$(if $(filter gnome-terminal,$(TERMINAL)), --title="$(TERMINALTITLE)" --, \
					$(if $(filter terminator,$(TERMINAL)), --title="$(TERMINALTITLE)" -x, \
					$(if $(filter xterm,$(TERMINAL)), -title "$(TERMINALTITLE)" -e, \
					)))


#	Files

SRC_EXTENSION	:=	.cpp
SRC				:=	$(shell find $(SRC_DIR) -type f -name "*$(SRC_EXTENSION)" -printf "%P\n")
OBJ				:=	$(SRC:%$(SRC_EXTENSION)=$(OBJ_DIR)/%.o)
DEP				:=	$(SRC:%$(SRC_EXTENSION)=$(DEP_DIR)/%.d)


#	Subdirectories

OBJ_SUBDIRS		:=	$(sort $(dir $(OBJ)))
DEP_SUBDIRS		:=	$(sort $(dir $(DEP)))


# *************************** BUILD PREPARATION ****************************** #

export				CXX CXXFLAGS MAKECMDGOALS MAKEFLAGS

PHONY_TARGETS	:=	all run opt san val valfd term clear modes re clean fclean ffclean
ENV_VARIABLES	:=	MODE ARGS TERMINAL
HELP_TARGETS	:=	help help-print \
					$(addprefix help-,$(PHONY_TARGETS) $(ENV_VARIABLES)) \
					$(addsuffix -help,$(PHONY_TARGETS) $(ENV_VARIABLES))
PHONY_TARGETS	+=	$(HELP_TARGETS)
export .PHONY	:	$(PHONY_TARGETS)

REBUILD_TARGETS	:=	opt san re
CLEAN_TARGETS	:=	clean fclean ffclean

.DEFAULT		:
					$(MAKE) help

.DEFAULT_GOAL	:=	all


# ********************************* MODES ************************************ #

ENV				:=

ifeq (run, $(filter run,$(MAKECMDGOALS) $(MODE)))
RUN				:=	true
endif

ifeq (opt, $(filter opt,$(MAKECMDGOALS) $(MODE)))
CXXFLAGS		:=	$(CXXFLAGS_STD) $(CXXFLAGS_OPT)
RECOMPILE		:=	true
endif

ifeq (san, $(filter san,$(MAKECMDGOALS) $(MODE)))
CXXFLAGS		+=	$(CXXFLAGS_STD) $(CXXFLAGS_DBG) $(CXXFLAGS_SAN)
RECOMPILE		:=	true
endif

ifeq (val, $(filter val,$(MAKECMDGOALS) $(MODE)))
ENV				+=	$(VALGRIND) $(VALGRINDFLAGS)
RUN				:=	true
endif

ifeq (valfd, $(filter valfd,$(MAKECMDGOALS) $(MODE)))
ENV				+=	$(VALGRIND) $(VALGRINDFLAGS) $(VALGRINDFDFLAGS)
NEW_TERM		:=	true
RUN				:=	true
endif

ifeq (term, $(filter term,$(MAKECMDGOALS) $(MODE)))
NEW_TERM		:=	true
RUN				:=	true
endif

ifeq (clear, $(filter clear,$(MAKECMDGOALS) $(MODE)))
CLEAR			:=	true
endif

ifdef ARGS
RUN				:=	true
endif


# ***************************** BUILD TARGETS ******************************** #

all				:
					if $(MAKE) --question $(NAME); then \
						echo -e -n $(MSG_NO_CHANGE); \
						echo -e -n $(MSG_HELP); \
					else \
						echo -e -n $(MSG_MODE); \
						echo -e -n " "$(MSG_INFO); \
						echo -e -n " "$(MSG_HELP); \
						echo -e -n $(MSG_START); \
						if $(MAKE) $(NAME); then \
							echo; \
							echo -e -n $(MSG_SUCCESS); \
						else \
							echo; \
							echo -e -n $(MSG_FAILURE); \
							exit 42; \
						fi; \
					fi; \
					echo -e -n $(MSG_USAGE)

run opt san val valfd term clear: modes

modes			:
					if [ "$(RECOMPILE)" = "true" ]; then \
						MAKELEVEL=$$(( $(MAKELEVEL) - 1 )) MSG_SUCCESS="" MSG_USAGE="" $(MAKE) re; \
						MAKELEVEL=$$(( $(MAKELEVEL) - 1 )) $(MAKE) clean; \
					else \
						MAKELEVEL=$$(( $(MAKELEVEL) - 1 )) MSG_USAGE="" $(MAKE) all; \
					fi
					if [ "$(CLEAR)" = "true" ]; then \
						clear; \
					fi
					if [ "$(NEW_TERM)" = "true" ] && [ -n "$(TERMINAL)" ]; then \
						$(TERMINAL) $(TERMINALFLAGS) bash -c \
							"trap '' SIGINT; \
							$(ENV) ./$(NAME) $(ARGS); \
							exec $(shell echo $$SHELL)"; \
					elif [ "$(RUN)" = "true" ]; then \
						$(ENV) "./$(NAME)" $(ARGS); \
					else \
						echo -e -n $(MSG_USAGE); \
					fi

re				:
					$(MAKE) fclean
					MAKELEVEL=$$(( $(MAKELEVEL) - 1 )) $(MAKE) all


# ***************************** BUILD PROCESS ******************************** #

#	Dependency files inclusion

ifeq (, $(filter $(HELP_TARGETS) $(REBUILD_TARGETS) $(CLEAN_TARGETS),$(MAKECMDGOALS)))
    ifneq (, $(wildcard $(OBJ_DIR)))
        -include	$(DEP)
    endif
endif


#	Executable linkage

$(NAME)			:	$(OBJ)
					$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)


#	Source file compilation

$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%$(SRC_EXTENSION) $(BUILDFILES) | $(OBJ_SUBDIRS)
					$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ \
						&& echo -e -n $(MSG_PROGRESS)


#	Pre-processing and dependency file creation

$(DEP_DIR)/%.d	:	$(SRC_DIR)/%$(SRC_EXTENSION) $(BUILDFILES) | $(DEP_SUBDIRS)
					$(CXX) $(CPPFLAGS) $(DEPFLAGS) $(CXXFLAGS) $<


#	Directory structure mirroring of source files for build artifacts

$(OBJ_SUBDIRS) \
$(DEP_SUBDIRS)	:
					mkdir -p $@


# ***************************** CLEAN TARGETS ******************************** #

clean			:
					echo -e -n $(MSG_CLEAN)
					rm -f $(OBJ) $(DEP)
                    ifneq (, $(wildcard $(OBJ_DIR)))
						-find $(OBJ_DIR) -type d -empty -delete
                    endif
                    ifneq (, $(wildcard $(DEP_DIR)))
						-find $(DEP_DIR) -type d -empty -delete
                    endif
					echo -e -n $(MSG_SUCCESS)

fclean			:
					echo -e -n $(MSG_FCLEAN)
					$(MAKE) clean
					rm -f $(NAME)
					echo -e -n $(MSG_SUCCESS)

ffclean			:
					echo -e -n $(MSG_FFCLEAN)
					$(MAKE) fclean
					rm -rf $(OBJ_DIR) $(DEP_DIR)
					echo -e -n $(MSG_SUCCESS)


# ****************************** HELP TARGETS ******************************** #

help			:
					echo -e "Targets:"
					echo -e "  all              Build the project (default target)"
					echo -e "  run              Build and run the project"
					echo -e "  opt              Rebuild the project with optimizations"
					echo -e "  san              Rebuild the project with sanitizers"
					echo -e "  val              Build and run the project with valgrind"
					echo -e "  valfd            Build and run the project with valgrind and file descriptor tracking"
					echo -e "  term             Build and run the project in a new terminal window"
					echo -e "  clear            Build the project and clear the terminal"
					echo -e "  re               Rebuild the project"
					echo -e "  clean            Remove build artifacts"
					echo -e "  fclean           Remove build artifacts and executable"
					echo -e "  ffclean          Remove build artifacts and executable without checking for unknown files"
					echo -e "  print-%          Print the value of a Makefile variable (replace % with variable name)"
					echo -e "  help             Display this message"
					echo -e "  help-% | %-help  Display more information for a specific target (replace % with target name)"
					echo
					echo -e "Environment Variables:"
					echo -e "  MODE             Build mode to combine multiple targets"
					echo -e "  ARGS             If specified, the program will run with those arguments after compilation."
					echo -e "  TERMINAL         Terminal emulator to use for targets opening a new terminal window"
					echo
					echo -e "Usage: make [\\$(STY_UND)target\\$(STY_RES)] [MODE=\"<\\$(STY_UND)mode1\\$(STY_RES)> [\\$(STY_UND)mode2\\$(STY_RES)] [...]\"] [ARGS=\"'<\\$(STY_UND)arg1\\$(STY_RES)>' '[\\$(STY_UND)arg2\\$(STY_RES)]' '[...]'\"] [TERMINAL=<\\$(STY_UND)terminal\\$(STY_RES)>]"

help-all		:
					echo -e "Build the project."
					echo -e "This is the default target when no target is specified."

help-run		:
					echo -e "Build the project and run the executable."
					echo -e "Arguments to the program can be passed via the ARGS variable."
					echo
					echo -e "Usage: make run [ARGS=\"'<\\$(STY_UND)arg1\\$(STY_RES)>' '[\\$(STY_UND)arg2\\$(STY_RES)]' '[...]'\"]"

help-opt		:
					echo -e "Rebuild the project with the following compiler optimization flags:"
					echo -e "  $(CXXFLAGS_OPT)"

help-san		:
					echo -e "Rebuild the project with the following sanitizer flags:"
					echo -e "  $(CXXFLAGS_SAN)"

help-val		:
					echo -e "Build the project and run the executable with valgrind."
					echo -e "Arguments to the program can be passed via the ARGS variable."
					echo
					echo -e "The following valgrind flags are used:"
					echo -e "$(VALGRINDFLAGS)" | tr ' ' '\n' | sed 's/^/  /'
					echo
					echo -e "Usage: make val [ARGS=\"'<\\$(STY_UND)arg1\\$(STY_RES)>' '[\\$(STY_UND)arg2\\$(STY_RES)]' '[...]'\"]"

help-valfd		:
					echo -e "Build the project and run the executable with valgrind and file descriptor tracking."
					echo -e "A new terminal window is opened to avoid inheriting open file descriptors."
					echo -e "Arguments to the program can be passed via the ARGS variable."
					echo
					echo -e "The following valgrind flags are used:"
					echo -e "$(VALGRINDFLAGS)" | tr ' ' '\n' | sed 's/^/  /'
					echo -e "File descriptor specific flags:"
					echo -e "$(VALGRINDFDFLAGS)" | tr ' ' '\n' | sed 's/^/  /'
					echo
					echo -e "Usage: make valfd [ARGS=\"'<\\$(STY_UND)arg1\\$(STY_RES)>' '[\\$(STY_UND)arg2\\$(STY_RES)]' '[...]'\"]"

help-term		:
					echo -e "Build the project and run the executable in a new terminal window."
					echo -e "The terminal emulator used is determined by the TERMINAL variable."
					echo -e "Arguments to the program can be passed via the ARGS variable."
					echo
					echo -e "The following terminal emulator is used by default:"
					echo -e "  $(TERMINAL)"
					echo
					echo -e "Usage: make term [TERMINAL=<\\$(STY_UND)terminal\\$(STY_RES)>] [ARGS=\"'<\\$(STY_UND)arg1\\$(STY_RES)>' '[\\$(STY_UND)arg2\\$(STY_RES)]' '[...]'\"]"

help-clear		:
					echo -e "Build the project and clear the terminal."

help-re			:
					echo -e "Rebuild the project."

help-clean		:
					echo -e "Remove build artifacts."

help-fclean		:
					echo -e "Remove build artifacts and the executable."

help-ffclean	:
					echo -e "Remove build artifacts and the executable without checking for unknown files."

help-print		:
					echo -e "Print the value of a Makefile variable by appending the variable name to print-..."
					echo -e "Useful for Makefile debugging."
					echo
					echo -e "Usage: make print-<\\$(STY_UND)variable name\\$(STY_RES)>"

help-help		:
					echo -e "Display more information for a specific target by appending or prepending help."
					echo
					echo -e "Usage: make help-<\\$(STY_UND)target\\$(STY_RES)> | make <\\$(STY_UND)target\\$(STY_RES)>-help"

help-MODE MODE-help:
					echo -e "Build mode to combine with other targets."
					echo -e "Multiple modes can be combined by separating them with a space."
					echo
					echo -e "Usage: make <\\$(STY_UND)target\\$(STY_RES)> MODE=\"<\\$(STY_UND)mode1\\$(STY_RES)> [\\$(STY_UND)mode2\\$(STY_RES)] [...]\""

help-ARGS ARGS-help:
					echo -e "If specified, the program will run with those arguments after compilation."
					echo
					echo -e "Usage: make <\\$(STY_UND)target\\$(STY_RES)> ARGS=\"'<\\$(STY_UND)arg1\\$(STY_RES)>' '[\\$(STY_UND)arg2\\$(STY_RES)]' '[...]'\""

help-TERMINAL TERMINAL-help:
					echo -e "Override the default terminal emulator for targets opening a new terminal window."
					echo
					echo -e "Usage: make <\\$(STY_UND)target\\$(STY_RES)> TERMINAL=<\\$(STY_UND)terminal\\$(STY_RES)>"

%-help:
					$(MAKE) help-$(subst -help,,$@)


# ********************************* COLORS *********************************** #

STY_RES			:=	"\e[0m"
STY_BOL			:=	"\e[1m"
STY_ITA			:=	"\e[3m"
STY_UND			:=	"\e[4m"
STY_RED			:=	"\e[31m"
STY_GRE			:=	"\e[32m"
STY_YEL			:=	"\e[33m"
STY_BLU			:=	"\e[34m"
STY_MAG			:=	"\e[35m"
STY_CYA			:=	"\e[36m"
STY_WHI			:=	"\e[37m"
STY_GRA			:=	"\e[90m"
STY_WHI_BRI		:=	"\e[97m"
STY_BLA_BG		:=	"\e[40m"
STY_RED_BG		:=	"\e[41m"
STY_GRE_BG		:=	"\e[42m"
STY_YEL_BG		:=	"\e[43m"
STY_BLU_BG		:=	"\e[44m"
STY_MAG_BG		:=	"\e[45m"
STY_CYA_BG		:=	"\e[46m"
STY_WHI_BG		:=	"\e[47m"
STY_GRA_BG		:=	"\e[100m"
STY_WHI_BRI_BG	:=	"\e[107m"


# **************************** CUSTOM MESSAGES ******************************* #

########################## Top-level only messages #############################
ifeq (0, $(MAKELEVEL))

#	Make status messages

MSG_INFO		:=	$(STY_ITA)$(STY_WHI)"Make version: $(MAKE_VERSION)\n\
					Compiler version: $(CXX_VERSION)"$(STY_RES)"\n"

MSG_HELP		:=	$(STY_ITA)$(STY_WHI)"Run 'make help' to see all available Makefile targets."$(STY_RES)"\n"

ifneq (, $(filter $(REBUILD_TARGETS),$(MAKECMDGOALS) $(MODE)))
MSG_START		:=	$(STY_ITA)"Rebuilding $(NAME) ... "$(STY_RES)
else
MSG_START		:=	$(STY_ITA)"Building $(NAME) ... "$(STY_RES)
endif

MSG_SUCCESS		?=	$(STY_BOL)$(STY_ITA)$($(COLOR_MAKE))"DONE!"$(STY_RES)"\n"

MSG_NO_CHANGE	:=	$(STY_ITA)$(STY_WHI)"Everything up-to-date!"$(STY_RES)"\n"

MSG_FAILURE		:=	$(STY_BOL)$(STY_ITA)$(STY_RED)"BUILD FAILED!"$(STY_RES)"\n"


#	Build modes

MSG_RUN			:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_YEL)"~~~~~~~~~~~~~~~~~~~~~~~ RUN MODE ~~~~~~~~~~~~~~~~~~~~~~~"$(STY_RES)"\n"
ifneq (, $(filter run,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_RUN)
endif

MSG_OPT			:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_GRE)"~~~~~~~~~~~~~~~~~~~ OPTIMIZATION MODE ~~~~~~~~~~~~~~~~~~"$(STY_RES)"\n"
ifneq (, $(filter opt,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_OPT)
endif

MSG_SAN			:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_RED)"~~~~~~~~~~~~~~~~~~~~ SANITIZER MODE ~~~~~~~~~~~~~~~~~~~~"$(STY_RES)"\n"
ifneq (, $(filter san,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_SAN)
endif

MSG_VAL			:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_BLU)"~~~~~~~~~~~~~~~~~~~~~ VALGRIND MODE ~~~~~~~~~~~~~~~~~~~~"$(STY_RES)"\n"
ifneq (, $(filter val,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_VAL)
endif

MSG_VALFD		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_CYA)"~~~~~~~~~~~~~~~~~~~ VALGRIND FD MODE ~~~~~~~~~~~~~~~~~~~"$(STY_RES)"\n"
ifneq (, $(filter valfd,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_VALFD)
endif

MSG_TERM		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_YEL)"~~~~~~~~~~~~~~~~~~~ NEW TERMINAL MODE ~~~~~~~~~~~~~~~~~~"$(STY_RES)"\n"
ifneq (, $(filter term,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_TERM)
endif

MSG_CLEAR		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_GRA)"~~~~~~~~~~~~~~~~~~~~~ CLEAR MODE ~~~~~~~~~~~~~~~~~~~~"$(STY_RES)"\n"
ifneq (, $(filter clear,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_CLEAR)
endif


#	Clean messages

MSG_CLEAN		:=	$(STY_ITA)"Cleaning up build artifacts ... "$(STY_RES)"\n"

MSG_FCLEAN		:=	$(STY_ITA)"Cleaning up build artifacts and executable ... "$(STY_RES)"\n"

MSG_FFCLEAN		:=	$(STY_ITA)"Forcefully cleaning up build artifacts directory and executable ... "$(STY_RES)"\n"

endif
################################################################################


# *************************** MAKEFILE DEBUGGING ***************************** #

print-%			:
					echo -e $* = $($*)


# ********************************* NOTES ************************************ #
