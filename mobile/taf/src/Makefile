
TOPDIR	:= ..

include ${TOPDIR}/make.rules

DIRS = libutil libparse jce2cpp jce2java jce2kjava jce2symcpp jce2c jce2cs jce2php libhessian hce2cpp ${TOPDIR}/jce libservant liblog libpatch libconfig libnotify libnodeF stat property log config notify patch patchclient node registry adminclient queryStatServer
DIRS_LIB = libutil libparse jce2cpp jce2java jce2kjava jce2symcpp libhessian hce2cpp ${TOPDIR}/jce libservant liblog libpatch libconfig libnotify libnodeF

all:
	@for dir in $(DIRS); do make -C $$dir; echo; done

clean:
	@for dir in $(DIRS); do make -C $$dir clean; echo; done

cleanall:
	@for dir in $(DIRS); do make -C $$dir cleanall; echo; done

install:
	@echo "do nothing"

uninstall:
	@echo "do nothing"

libonly:
	@for dir in $(DIRS_LIB); do make -C $$dir; echo; done

