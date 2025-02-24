include				$(shell git rev-parse --show-toplevel)/Makefiles/setup.mk


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
