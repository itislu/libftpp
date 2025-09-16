ifndef DOC_MK
DOC_MK			:=	1

include				$(shell git rev-parse --show-toplevel)/Makefiles/setup.mk
include				$(MAKEFILES_DIR)/print.mk


# ************************* DOCUMENTATION TARGETS **************************** #

BEAR_IMG		:=	bear
DOXYGEN_IMG		:=	doxygen
CLANG_UML_IMG	:=	clang-uml
PLANTUML_IMG	:=	plantuml
DOXYFILE		:=	$(REPO_ROOT)/Doxyfile
CLANG_UML_CFG	:=	$(REPO_ROOT)/.clang-uml
DOXYGEN_OUTDIR	:=	$(DOC_DIR)/doxygen
UML_OUTDIR		:=	$(DOC_DIR)/uml


bear			:	.bear-image
					$(call PRINTLN,Running 'bear -- make re; make fclean' ...)
					if ! docker run --rm \
						-u $(shell id -u):$(shell id -g) \
						-v $(REPO_ROOT):$(REPO_ROOT) \
						-w $(PWD) \
						$(BEAR_IMG) \
						bash -c '{ \
							bear -- make re; \
							make fclean; \
						} >/dev/null'; then \
						echo "User mapping failed, trying without specific user..." >&2; \
						docker run --rm \
							-v $(REPO_ROOT):$(REPO_ROOT) \
							-w $(PWD) \
							$(BEAR_IMG) \
							bash -c '{ \
								bear -- make re; \
								make fclean; \
							} >/dev/null'; \
					fi
					echo
					$(call PRINTLN,Generated compile_commands.json.)

.bear-image		:
					$(call PRINTLN,Building bear image ...)
					docker build -t $(BEAR_IMG) $(DOCKER_DIR)/$(BEAR_IMG)
					$(call PRINTLN,Built bear image.)

doxygen			:	.doxygen-image bear $(DOXYFILE)
					$(call PRINTLN,Running 'doxygen -q -' ...)
					mkdir -p $(DOXYGEN_OUTDIR)
					if ! docker run --rm \
						-u $(shell id -u):$(shell id -g) \
						-v $(REPO_ROOT):$(REPO_ROOT) \
						-w $(PWD) \
						$(DOXYGEN_IMG) \
						bash -c '{ \
							cat $(DOXYFILE); \
							echo PROJECT_NAME="$(if $(REPO_SUBDIR),[$(REPO_SUBDIR)] - )$(NAME)"; \
							echo OUTPUT_DIRECTORY=$(DOXYGEN_OUTDIR); \
						} | doxygen -q -'; then \
						echo "User mapping failed, trying without specific user..." >&2; \
						docker run --rm \
							-v $(REPO_ROOT):$(REPO_ROOT) \
							-w $(PWD) \
							$(DOXYGEN_IMG) \
							bash -c '{ \
								cat $(DOXYFILE); \
								echo PROJECT_NAME="$(if $(REPO_SUBDIR),[$(REPO_SUBDIR)] - )$(NAME)"; \
								echo OUTPUT_DIRECTORY=$(DOXYGEN_OUTDIR); \
							} | doxygen -q -'; \
					fi
					echo
					$(call PRINTLN,Generated Doxygen documentation in $(DOXYGEN_OUTDIR).)
					open $(DOXYGEN_OUTDIR)/html/index.html

$(DOXYFILE)		:	| .doxygen-image
					$(call PRINTLN,Running 'doxygen -g $(DOXYFILE)' ...)
					if ! docker run --rm \
						-u $(shell id -u):$(shell id -g) \
						-v $(REPO_ROOT):$(REPO_ROOT) \
						-w $(PWD) \
						$(DOXYGEN_IMG) \
						doxygen -g $(DOXYFILE); then \
						echo "User mapping failed, trying without specific user..." >&2; \
						docker run --rm \
							-v $(REPO_ROOT):$(REPO_ROOT) \
							-w $(PWD) \
							$(DOXYGEN_IMG) \
							doxygen -g $(DOXYFILE); \
					fi
					echo
					$(call PRINTLN,Created default Doxyfile. Please review and adjust settings as needed$(COMMA) then rerun.)
					exit 1

.doxygen-image	:
					$(call PRINTLN,Building doxygen image ...)
					docker build -t $(DOXYGEN_IMG) $(DOCKER_DIR)/$(DOXYGEN_IMG)
					$(call PRINTLN,Built doxygen image.)

uml				:	.clang-uml .plantuml-image
					$(MAKE) .plantuml

.clang-uml		:	.clang-uml-image bear $(CLANG_UML_CFG)
					$(call PRINTLN,Running 'clang-uml --progress --paths-relative-to-pwd --config=$(CLANG_UML_CFG) --output-directory=$(UML_OUTDIR)' ...)
					mkdir -p $(UML_OUTDIR)
					if ! docker run --rm \
						-u $(shell id -u):$(shell id -g) \
						-v $(REPO_ROOT):$(REPO_ROOT) \
						-w $(PWD) \
						$(CLANG_UML_IMG) \
						clang-uml --progress --paths-relative-to-pwd --config=$(CLANG_UML_CFG) --output-directory=$(UML_OUTDIR); then \
						echo "User mapping failed, trying without specific user..." >&2; \
						docker run --rm \
							-v $(REPO_ROOT):$(REPO_ROOT) \
							-w $(PWD) \
							$(CLANG_UML_IMG) \
							clang-uml --progress --paths-relative-to-pwd --config=$(CLANG_UML_CFG) --output-directory=$(UML_OUTDIR); \
					fi
					echo
					$(call PRINTLN,Generated PlantUML files in $(UML_OUTDIR).)

$(CLANG_UML_CFG):	| .clang-uml-image
					$(call PRINTLN,Running 'clang-uml --init' ...)
					if ! docker run --rm \
						-u $(shell id -u):$(shell id -g) \
						-v $(REPO_ROOT):$(REPO_ROOT) \
						-w $(PWD) \
						$(CLANG_UML_IMG) \
						clang-uml --init; then \
						echo "User mapping failed, trying without specific user..." >&2; \
						docker run --rm \
							-v $(REPO_ROOT):$(REPO_ROOT) \
							-w $(PWD) \
							$(CLANG_UML_IMG) \
							clang-uml --init; \
					fi
					mv .clang-uml $(CLANG_UML_CFG)
					echo
					$(call PRINTLN,Created default .clang-uml configuration file. Please review and adjust settings as needed$(COMMA) then rerun.)
					exit 1

.clang-uml-image:
					$(call PRINTLN,Building clang-uml image ...)
					docker build -t $(CLANG_UML_IMG) $(DOCKER_DIR)/$(CLANG_UML_IMG)
					$(call PRINTLN,Built clang-uml image.)

.plantuml		:	.plantuml-image
					$(call PRINTLN,Running 'plantuml -tpng -tsvg "$(UML_OUTDIR)/*.puml"' ...)
					mkdir -p $(UML_OUTDIR)
					if ! docker run --rm \
						-u $(shell id -u):$(shell id -g) \
						-v $(REPO_ROOT):$(REPO_ROOT) \
						-w $(PWD) \
						$(PLANTUML_IMG) \
						plantuml -tpng -tsvg "$(UML_OUTDIR)/*.puml"; then \
						echo "User mapping failed, trying without specific user..." >&2; \
						docker run --rm \
							-v $(REPO_ROOT):$(REPO_ROOT) \
							-w $(PWD) \
							$(PLANTUML_IMG) \
							plantuml -tpng -tsvg "$(UML_OUTDIR)/*.puml"; \
					fi
					$(call PRINTLN,Generated PNG and SVG files in $(UML_OUTDIR).)
					open $(UML_OUTDIR)
					$(call PRINTLN,Running 'plantuml -tpdf "$(UML_OUTDIR)/*.puml"' (this may take a moment) ...)
					if ! docker run --rm \
						-u $(shell id -u):$(shell id -g) \
						-v $(REPO_ROOT):$(REPO_ROOT) \
						-w $(PWD) \
						$(PLANTUML_IMG) \
						plantuml -tpdf "$(UML_OUTDIR)/*.puml"; then \
						echo "User mapping failed, trying without specific user..." >&2; \
						docker run --rm \
							-v $(REPO_ROOT):$(REPO_ROOT) \
							-w $(PWD) \
							$(PLANTUML_IMG) \
							plantuml -tpdf "$(UML_OUTDIR)/*.puml"; \
					fi
					$(call PRINTLN,Generated PDF files in $(UML_OUTDIR).)

.plantuml-image	:
					$(call PRINTLN,Building plantuml image ...)
					docker build -t $(PLANTUML_IMG) $(DOCKER_DIR)/$(PLANTUML_IMG)
					$(call PRINTLN,Built plantuml image.)


endif
