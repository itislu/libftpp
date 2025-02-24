# ******************************* MAKE SETUP ********************************* #

MAKEFLAGS		+=	-j -s
SHELL			:=	/bin/bash
PWD				:=	$(shell pwd)
GLOBAL_MK		:=	$(abspath $(lastword $(MAKEFILE_LIST)))
REPO_ROOT		:=	$(abspath $(dir $(abspath $(dir $(GLOBAL_MK)))))
REPO_SUBDIR		:=	$(patsubst /%,%,$(subst $(REPO_ROOT),,$(PWD)))


# ******************************** SUBMAKE *********************************** #

MAKECMDGOALS	?=	all

#	Find all immediate subdirectories containing Makefiles
SUBDIRS			:=	$(patsubst %/,%,$(dir $(wildcard */Makefile)))

.PHONY			:	$(MAKECMDGOALS)
$(MAKECMDGOALS)	:	$(SUBDIRS)
					echo -e "──────────────────────────────────────────────────────────────"

#	Recursively call make in subdirectories
.PHONY			:	$(SUBDIRS)
$(SUBDIRS)		:
					echo -e "──────────────────────────────────────────────────────────────"
					MSG_PREFIX="[$@]" $(MAKE) -C $@ $(MAKECMDGOALS)
