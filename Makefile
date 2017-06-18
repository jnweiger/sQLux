# (c) UQLX - see COPYRIGHT
#

SYS := $(shell $(CC) -dumpmachine)
EXE :=
ifneq (, $(findstring linux, $(SYS)))
	# Do linux things
	OPT_FLAGS := -DSERIAL -DNEWSERIAL -DNEWPTY -DIPDEV -DUSE_IPC -DSOUND -DUX_WAIT
else
ifneq (, $(findstring mingw, $(SYS)))
	# Do mingw things
	OPT_FLAGS := -DNO_LOCK
	EXE := .exe
else
ifneq (, $(findstring cygwin, $(SYS)))
	# Do cygwin things
else
	# Do things for others
endif
endif
endif

BUILDFLAGS := -DLINUX -DQVFS -DUSE_IOSZ -DDO_GRAB \
	-DFASTLOOP  -DSH_MEM -DXSCREEN \
	-DHAS_STPCPY -DEVM_SCR -D_GNU_SOURCE -D_XOPEN_SOURCE -DMOUSE \
	-DSWAP_LOAD_IN_MEMORY -DSWAP_STORE_IN_MEMORY

DEBUG = -ggdb

OPTFLAGS = -O2

CFLAGS = $(BUILDFLAGS) $(DEBUG) $(OPT_FLAGS)

SRC := Init.c general.c instructions_ao.c instructions_pz.c   \
	QLtraps.c QL_hardware.c QL_config.c dummies.c vm.c \
	qmtrap.c uxfile.c QL_serial.c pty.c \
	QL_files.c QL_driver.c QDisk.c trace.c version.c QLserio.c \
	QL_screen.c QL_poll.c xcodes.c QL_boot.c QL_basext.c \
	QL_cconv.c iexl_general.c QVFS.c \
	Xscreen.c QLip.c util.c xc68.c xipc.c script.c \
	QL_sound.c mach_exception.c \
	vl.c ide.c block.c unixstuff.c xqlmouse.c \
	xlmain.c uqlx_cfg.c SDL2screen.c files.c strings.c

OBJ := $(SRC:.c=.o)

DOCS := COPYRIGHT CONTRIBUTING \
	docs/socket.texi docs/uqlx.texi docs/ql.html docs/qxlwin.html

EXE_NAME = qlux

XLIBS := -lSDL2


all : $(EXE_NAME)$(EXE)

.PHONY : depend
depend : $(SRC)
	$(CC) $(CFLAGS) -MM $^ > ./Makefile.depend;

-include Makefile.depend

.c.o:
	$(CC) $(CFLAGS) -c $<

$(EXE_NAME)$(EXE) : $(OBJ)
	$(CC) $(LIBS) -o $(EXE_NAME)$(EXE) $(OBJ) $(XLIBS)

.PHONY : clean
clean :
	rm $(OBJ)

:PHONY : install
install: qm


