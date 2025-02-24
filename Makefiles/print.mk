ifndef PRINT_MK
PRINT_MK		:=	1

include				$(shell git rev-parse --show-toplevel)/Makefiles/setup.mk


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


# **************************** PRINT FUNCTIONS ******************************* #

define PRINT
if [[ -n "$(shell printf '%b' "$(1)")" ]]; then \
	echo -e -n "$(1)" \
		| awk -v prefix="$(shell printf '%b' $(MSG_PREFIX))" '{printf "%s%s", (prefix ? prefix " " : ""), $$0}'; \
fi
endef

define PRINTLN
if [[ -n "$(shell printf '%b' "$(1)")" ]]; then \
	echo -e "$(1)" \
		| awk -v prefix="$(shell printf '%b' $(MSG_PREFIX))" '{print (prefix ? prefix " " : "") $$0}'; \
fi
endef


# **************************** CUSTOM MESSAGES ******************************* #

#	Adjustments to dynamic messages

ifneq (, $(MSG_PREFIX))
MSG_PREFIX		:=	$(STY_WHI)$(MSG_PREFIX)$(STY_RES)
endif

ifneq (, $(MSG_USAGE))
MSG_USAGE		:=	"\n"$(MSG_USAGE)
endif


########################## Top-level only messages #############################
ifeq (0, $(MAKELEVEL))

#	Make status messages

MSG_MAKE_INFO	:=	$(STY_ITA)$(STY_WHI)"Make version: $(MAKE_VERSION)"$(STY_RES)

MSG_COMP_INFO	:=	$(STY_ITA)$(STY_WHI)"Compiler version: $(CXX_VERSION)"$(STY_RES)

MSG_HELP		:=	$(STY_ITA)$(STY_WHI)"Run 'make help' to see all available Makefile targets."$(STY_RES)

ifneq (, $(filter $(REBUILD_TARGETS),$(MAKECMDGOALS) $(MODE)))
MSG_START		:=	$(STY_ITA)"Rebuilding $(NAME) ... "$(STY_RES)
else
MSG_START		:=	$(STY_ITA)"Building $(NAME) ... "$(STY_RES)
endif

MSG_SUCCESS		?=	$(STY_BOL)$(STY_ITA)$($(COLOR_MAKE))"DONE!"$(STY_RES)

MSG_NO_CHANGE	:=	$(STY_ITA)$(STY_WHI)"Everything up-to-date!"$(STY_RES)

MSG_FAILURE		:=	$(STY_BOL)$(STY_ITA)$(STY_RED)"BUILD FAILED!"$(STY_RES)


#	Build modes

MSG_RUN			:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_YEL)"~~~~~~~~~~~~~~~~~~~~~~~ RUN MODE ~~~~~~~~~~~~~~~~~~~~~~~"$(STY_RES)
ifneq (, $(filter run,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(if $(MSG_MODE), "\n")$(MSG_RUN)
endif

MSG_OPT			:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_GRE)"~~~~~~~~~~~~~~~~~~~ OPTIMIZATION MODE ~~~~~~~~~~~~~~~~~~"$(STY_RES)
ifneq (, $(filter opt,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(if $(MSG_MODE), "\n")$(MSG_OPT)
endif

MSG_SAN			:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_RED)"~~~~~~~~~~~~~~~~~~~~ SANITIZER MODE ~~~~~~~~~~~~~~~~~~~~"$(STY_RES)
ifneq (, $(filter san,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(if $(MSG_MODE), "\n")$(MSG_SAN)
endif

MSG_VAL			:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_BLU)"~~~~~~~~~~~~~~~~~~~~~ VALGRIND MODE ~~~~~~~~~~~~~~~~~~~~"$(STY_RES)
ifneq (, $(filter val,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(if $(MSG_MODE), "\n")$(MSG_VAL)
endif

MSG_VALFD		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_CYA)"~~~~~~~~~~~~~~~~~~~ VALGRIND FD MODE ~~~~~~~~~~~~~~~~~~~"$(STY_RES)
ifneq (, $(filter valfd,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(if $(MSG_MODE), "\n")$(MSG_VALFD)
endif

MSG_TERM		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_YEL)"~~~~~~~~~~~~~~~~~~~ NEW TERMINAL MODE ~~~~~~~~~~~~~~~~~~"$(STY_RES)
ifneq (, $(filter term,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(if $(MSG_MODE), "\n")$(MSG_TERM)
endif

MSG_CLEAR		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_GRA)"~~~~~~~~~~~~~~~~~~~~~ CLEAR MODE ~~~~~~~~~~~~~~~~~~~~"$(STY_RES)
ifneq (, $(filter clear,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(if $(MSG_MODE), "\n")$(MSG_CLEAR)
endif


#	Clean messages

MSG_CLEAN		:=	$(STY_ITA)"Cleaning up build artifacts ... "$(STY_RES)

MSG_FCLEAN		:=	$(STY_ITA)"Cleaning up build artifacts and executable ... "$(STY_RES)

MSG_FFCLEAN		:=	$(STY_ITA)"Forcefully cleaning up build artifacts directory, executable and generated documentation ... "$(STY_RES)

endif
################################################################################


# *************************** MAKEFILE DEBUGGING ***************************** #

print-%			:
					$(call PRINTLN,$* = $(shell echo -e -n $($*)))


endif
