all:
	@echo You must select a system.
	@echo make system where system is one of the following:
	@echo linux
	@echo slackware
	@echo freebsd
	@echo dragonfly
	@echo openbsd
	@echo htests \(linux\)
	@echo Building linux by default
	$(MAKE) -f config/makefile.linux
	@echo done

linux:
	$(MAKE) -f config/makefile.linux
	@echo done

htests:
	$(MAKE) -f config/makefile.tests
	@echo done

slackware:
	$(MAKE) -f config/makefile.slackware
	@echo done

fedora:
	$(MAKE) -f config/makefile.fedora
	@echo done

freebsd:
	$(MAKE) -f config/makefile.freebsd
	@echo done

dragonfly:
	$(MAKE) -f config/makefile.dragonfly
	@echo done

openbsd:
	$(MAKE) -f config/makefile.openbsd
	@echo done

travis:
	$(MAKE) -f config/makefile.travis
	@echo done

clean:
	@echo cleaning
	@rm -f hunta2
	@rm -f test
	@rm -f src/*.o
	@rm -f src/physics/*.o
	@rm -f src/components/*.o
	@rm -f src/lua/*.o
	@rm -f src/tools/*.o
	@rm -f src/ui/*.o
	@rm -f tests/*.o
	@echo done
