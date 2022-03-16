ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

install:
	cp -r ./include/hy $(PREFIX)/include

.PHONY: test
test:
	cd test && $(MAKE) $@

.PHONY: clean
clean:
	cd test && $(MAKE) $@


