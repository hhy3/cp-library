ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

install:
	cp -r ./include/hy $(PREFIX)/include
