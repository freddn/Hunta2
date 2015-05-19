all:
	@echo You must select a system.
	@echo "Try 'make linux' or 'make freebsd'."

linux:
	$(MAKE) -f config/makefile.linux

freebsd:
	$(MAKE) -f config/makefile.freebsd
