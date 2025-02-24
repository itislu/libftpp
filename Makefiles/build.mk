ifndef BUILD_MK
BUILD_MK		:=	1

include				$(shell git rev-parse --show-toplevel)/Makefiles/setup.mk
include				$(MAKEFILES_DIR)/print.mk


# *************************** BUILD PREPARATION ****************************** #

export				CXX CXXFLAGS MAKECMDGOALS MAKEFLAGS


#	Build artifacts

OBJ				:=	$(SRC:%$(SRC_EXTENSION)=$(OBJ_DIR)/%.o)
DEP				:=	$(SRC:%$(SRC_EXTENSION)=$(DEP_DIR)/%.d)
OBJ_SUBDIRS		:=	$(sort $(dir $(OBJ)))
DEP_SUBDIRS		:=	$(sort $(dir $(DEP)))


#	Target categories

BUILD_TARGETS	:=	all run val valfd term clear modes
REBUILD_TARGETS	:=	opt san re
DOC_TARGETS		:=	bear doxygen uml
CLEAN_TARGETS	:=	clean fclean ffclean
PHONY_TARGETS	:=	$(BUILD_TARGETS) $(REBUILD_TARGETS) $(DOC_TARGETS) $(CLEAN_TARGETS)
ENV_VARIABLES	:=	MODE ARGS TERMINAL
HELP_TARGETS	:=	help help-print \
					$(addprefix help-,$(PHONY_TARGETS) $(ENV_VARIABLES)) \
					$(addsuffix -help,$(PHONY_TARGETS) $(ENV_VARIABLES))
HIDDEN_TARGETS	:=	.bear-image .doxygen-image .clang-uml .clang-uml-image .plantuml .plantuml-image


#	Phony targets

PHONY_TARGETS	+=	$(HELP_TARGETS) $(HIDDEN_TARGETS)
export .PHONY	:	$(PHONY_TARGETS)


# ***************************** BUILD TARGETS ******************************** #

all				:
					if $(MAKE) --question $(NAME); then \
						$(call PRINTLN,"$(MSG_NO_CHANGE)"); \
						$(call PRINTLN,"$(MSG_HELP)"); \
					else \
						$(call PRINTLN,"$(MSG_MODE)"); \
						$(call PRINTLN," $(MSG_MAKE_INFO)"); \
						$(call PRINTLN," $(MSG_COMP_INFO)"); \
						$(call PRINTLN," $(MSG_HELP)"); \
						$(call PRINT,"$(MSG_START)"); \
						if $(MAKE) $(NAME); then \
							echo; \
							$(call PRINTLN,"$(MSG_SUCCESS)"); \
						else \
							echo; \
							$(call PRINTLN,"$(MSG_FAILURE)"); \
							exit 42; \
						fi; \
					fi; \
					$(call PRINTLN,"$(MSG_USAGE)")

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
						$(call PRINTLN,"$(MSG_USAGE)"); \
					fi

re				:
					$(MAKE) fclean
					MAKELEVEL=$$(( $(MAKELEVEL) - 1 )) $(MAKE) all


# ***************************** BUILD PROCESS ******************************** #

#	Dependency files inclusion

#	Include if building or if no target specified
ifneq (, $(or $(filter $(BUILD_TARGETS),$(MAKECMDGOALS)),$(if $(MAKECMDGOALS),,all)))
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


# ***************************** CLEAN TARGETS ******************************** #

clean			:
					$(call PRINTLN,"$(MSG_CLEAN)")
					rm -f $(OBJ) $(DEP)
                    ifneq (, $(wildcard $(OBJ_DIR)))
						-find $(OBJ_DIR) -type d -empty -delete
                    endif
                    ifneq (, $(wildcard $(DEP_DIR)))
						-find $(DEP_DIR) -type d -empty -delete
                    endif
					$(call PRINTLN,"$(MSG_SUCCESS)")

fclean			:
					$(call PRINTLN,"$(MSG_FCLEAN)")
					$(MAKE) clean
					rm -f $(NAME)
					$(call PRINTLN,"$(MSG_SUCCESS)")

ffclean			:
					$(call PRINTLN,"$(MSG_FFCLEAN)")
					$(MAKE) fclean
					rm -rf $(OBJ_DIR) $(DEP_DIR) $(DOXYGEN_OUTDIR) $(UML_OUTDIR)
					$(call PRINTLN,"$(MSG_SUCCESS)")


endif
