# ******************************* MAKE SETUP ********************************* #

MAKEFLAGS		+=	-j -s
SHELL			:=	/bin/bash
PWD				:=	$(shell pwd)
MAKEFILES_DIR	:=	$(abspath $(dir $(lastword $(MAKEFILE_LIST))))
REPO_ROOT		:=	$(abspath $(dir $(MAKEFILES_DIR)))
REPO_SUBDIR		:=	$(patsubst /%,%,$(subst $(REPO_ROOT),,$(PWD)))


#	Special characters for Make

COMMA			:=	,
SPACE			:=	$() $()


# *************************** MAKEFILE DEBUGGING ***************************** #

print-%			:
					echo -e $* = $($*)
