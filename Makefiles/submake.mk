ifndef SUBMAKE_MK
SUBMAKE_MK		:=	1

include				$(shell git rev-parse --show-toplevel)/Makefiles/setup.mk
include				$(MAKEFILES_DIR)/print.mk


# ******************************** SUBMAKE *********************************** #

MAKEFLAGS		+=	--output-sync=recurse
MAKECMDGOALS	?=	all

#	Find all immediate subdirectories containing Makefiles
SUBDIRS			:=	$(patsubst %/,%,$(dir $(wildcard */Makefile)))

.PHONY			:	$(MAKECMDGOALS)
$(MAKECMDGOALS)	:	$(SUBDIRS)
					$(call PRINTLN,"──────────────────────────────────────────────────────────────")

#	Recursively call make in subdirectories
.PHONY			:	$(SUBDIRS)
$(SUBDIRS)		:
					$(call PRINTLN,"──────────────────────────────────────────────────────────────")
					MSG_PREFIX="[$@]" $(MAKE) --directory=$@ $(MAKECMDGOALS)


endif
