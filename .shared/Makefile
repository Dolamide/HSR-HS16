.PHONY: pdf html autobuild clean

BUILDDIR = _build

default: clean pdf html

pdf:
	@BUILD_PDF=TRUE sphinx-build -q -b pdf . $(BUILDDIR)/pdf/
	@echo "PDF created"

html:
	@sphinx-build -q -b html . $(BUILDDIR)/html/
	@echo "HTML created"

serve: html
	@cd _build/html && python3 -m http.server

open_pdf: pdf
	@xdg-open _build/pdf/* > /dev/null 2>&1 &

clean:
	@rm -Rf $(BUILDDIR)/*
