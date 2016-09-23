.PHONY: pdf html autobuild clean

BUILDDIR = _build

default: pdf html

pdf:
	@BUILD_PDF=TRUE sphinx-build -q -b pdf . $(BUILDDIR)/pdf/
	@echo "PDF created"

html:
	@sphinx-build -q -b html . $(BUILDDIR)/html/
	@echo "HTML created"

autobuild:
	@sphinx-autobuild --open-browser . $(BUILDDIR)/html/

clean:
	@rm -Rf $(BUILDDIR)/*
