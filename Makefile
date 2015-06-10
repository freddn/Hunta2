all:
	@echo You must select a system.
	@echo make system where system is one of the following:
	@echo linux
	@echo freebsd
	@echo dragonfly

linux:
	$(MAKE) -f config/makefile.linux

freebsd:
	$(MAKE) -f config/makefile.freebsd

dragonfly:
	$(MAKE) -f config/makefile.dragonfly
