OUTPUT=main
EXT=cpp
CPPC=g++
INCDIR=./include 
OBJECTS=./depsAndObjects/main.o ./depsAndObjects/clock.o ./depsAndObjects/filework.o ./depsAndObjects/inputs.o ./depsAndObjects/algs.o 
STATICdepend=
SHAREDdepend=
SHAREDFLAG=
ENTRY=main
DEPOBJDIR=./depsAndObjects
STATLIBS=./staticLibs
SHLIBS=./sharedLibs
ContFile=./code.cpp
TSTfile=./testFile
ANSfile=./answerFile
TSTlogs=./logs
TSTgarbage=./tstFile ./ansFile ./mainFile ./genTest 
ANALgarbage=./analFile 
STATICLIBGEN_name=static
SHAREDLIBGEN_name=shared
C++standart=-std=c++23
OPT=-O3
DEPFLAGS=-MP -MD
GENERALFLAGS=$(C++standart) -g3 -w
STLIBGEN=$(STATLIBS)/lib$(STATICLIBGEN_name).a
SHLIBGEN=$(SHLIBS)/lib$(SHAREDLIBGEN_name).so
CFLAGS=$(GENERALFLAGS) $(OPT) $(DEPFLAGS)
DEPFILES=$(patsubst %.o, %.d, $(OBJECTS))
LIBSTATIC_files=$(foreach D, $(STATLIBS), $(wildcard $(D)/lib*.a))
LIBSHARED_files=$(foreach D, $(SHLIBS), $(wildcard $(D)/lib*.so))
LIBSTATIC_names=
LIBSHARED_names=
ifneq ($(LIBSHARED_files), )
	LIBSHARED_names:=$(patsubst $(SHLIBS)/lib%.so, %, $(LIBSHARED_files))
else
	LIBSHARED_names:=
endif
ifneq ($(LIBSTATIC_files), )
	LIBSTATIC_names:=$(patsubst $(STATLIBS)/lib%.a, %, $(LIBSTATIC_files))
else
	LIBSTATIC_names:=
endif
ISSHARED=
ISSTATIC=
ifneq ($(strip $(LIBSHARED_files)), )
	ISSHARED:=$(foreach D,$(SHLIBS),-L$(D))
else
	ISSHARED:=$(ISSHARED)
endif
ifneq ($(strip $(LIBSTATIC_files)), )
	ISSTATIC:=$(foreach D,$(STATLIBS),-L$(D))
else
	ISSTATIC:=$(ISSTATIC)
endif
INCLUDESHARED:=
ifeq ($(ISSHARED),$(foreach D,$(SHLIBS),-L$(D)))
	INCLUDESHARED:=export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(SHLIBS)
else
	INCLUDESHARED:=
endif
all:$(OUTPUT)
	@echo ========= SUCCESS ==========
libstatic:$(STATICdepend)
	@echo ========= SUCCESS ==========
libshared:$(SHAREDdepend)
	@echo ========= SUCCESS ==========
$(OUTPUT):$(STATICdepend) $(SHAREDdepend) $(OBJECTS)
	$(CPPC) $(OBJECTS) -Wl,--defsym=main=$(ENTRY) $(ISSTATIC) $(ISSHARED) $(foreach D,$(LIBSTATIC_names),-l$(D)) $(foreach D,$(LIBSHARED_names),-l$(D)) -o $@
	$(INCLUDESHARED)
mrproper:
	rm -rf $(OBJECTS) $(DEPFILES) $(TSTgarbage) $(ANALgarbage)
purge:
	rm -rf $(OBJECTS) $(DEPFILES) $(STLIBGEN) $(SHLIBGEN) $(ContFile) $(TSTfile) $(ANSfile) $(TSTlogs) $(TSTgarbage) $(ANALgarbage)
$(STLIBGEN):$(OBJECTS)
	ar rc $(STLIBGEN) $(OBJECTS)
	ranlib $(STLIBGEN)
$(SHLIBGEN):$(OBJECTS)
	$(CPPC) -shared -o $(SHLIBGEN) $(OBJECTS)
$(DEPOBJDIR)/%.o:./%.$(EXT)
	$(CPPC) $(CFLAGS) $(foreach D,$(INCDIR),-I$(D)) $(SHAREDFLAG) -c $< -o $@
$(DEPOBJDIR)/%.o:./lib/%.$(EXT)
	$(CPPC) $(CFLAGS) $(foreach D,$(INCDIR),-I$(D)) $(SHAREDFLAG) -c $< -o $@

-include $(DEPFILES)
