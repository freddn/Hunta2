all:
	@echo You must select a system.
	@echo make system where system is one of the following:
	@echo linux
	@echo slackware
	@echo freebsd
	@echo dragonfly
	@echo openbsd
	@echo Building linux by default
	$(MAKE) -f config/makefile.linux

linux:
	$(MAKE) -f config/makefile.linux

slackware:
	$(MAKE) -f config/makefile.slackware

freebsd:
	$(MAKE) -f config/makefile.freebsd

dragonfly:
	$(MAKE) -f config/makefile.dragonfly

openbsd:
	$(MAKE) -f config/makefile.openbsd

travis:
	$(MAKE) -f config/makefile.travis

clean:
	@echo cleaning
	@rm -f hunta2
	@rm -f src/*.o
