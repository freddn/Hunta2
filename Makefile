all:
	@echo You must select a system.
	@echo make system where system is one of the following:
	@echo linux
	@echo slackware
	@echo freebsd
	@echo dragonfly

linux:
	$(MAKE) -f config/makefile.linux

slackware:
	$(MAKE) -f config/makefile.slackware

freebsd:
	$(MAKE) -f config/makefile.freebsd

dragonfly:
	$(MAKE) -f config/makefile.dragonfly
