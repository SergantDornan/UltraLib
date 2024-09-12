ANAL=algs
OUTPUT=prog
TST=test

ANALENTRY=entry
TSTENTRY=entry

ROOTDIR=.
SOURCEDIR=./lib
DEPOBJDIR =./depsAndObjects
STATLIBS=./staticLibs
SHLIBS=./sharedLibs
Static_lib_folder_code=./staticLibsSource
Shared_lib_folder_code=./sharedLibsSource
lib_code_source=/source
lib_code_headers=/header

SOURCEANAL=./algAnal/source
SOURCETST=./tests/source

INCANAL=./algAnal/header
INCTST=./tests/header

INCDIRS=. ./include/ $(INCANAL) $(INCTST)

STATICLIBGEN_name=static
SHAREDLIBGEN_name=shared
CPPC=g++
C++standart=-std=c++20
OPT=-O2
DEPFLAGS=-MP -MD
GENERALFLAGS=$(C++standart) -g3

OUTPUTS=$(OUTPUT) $(ANAL) $(TST)
SOURCESTATIC=$(Static_lib_folder_code)$(lib_code_source)
SOURCESHARED=$(Shared_lib_folder_code)$(lib_code_source)
INCDIRSTATIC=$(Static_lib_folder_code)$(lib_code_headers)
INCDIRSHARED=$(Shared_lib_folder_code)$(lib_code_headers)
STLIBGEN=$(STATLIBS)/lib$(STATICLIBGEN_name).a
MAINLIB=lib$(MAINLIBNAME).a
SHLIBGEN=$(SHLIBS)/lib$(SHAREDLIBGEN_name).so

CFLAGS=$(GENERALFLAGS) $(OPT) $(DEPFLAGS)

CFILESROOT=$(foreach D, $(ROOTDIR), $(wildcard $(D)/*.cpp))
CFILESSOURCE=$(foreach D, $(SOURCEDIR), $(wildcard $(D)/*.cpp))

STATICCFILES=$(foreach D, $(SOURCESTATIC), $(wildcard $(D)/*.cpp))
SHAREDCFILES=$(foreach D, $(SOURCESHARED), $(wildcard $(D)/*.cpp))

OBJECTSSTATIC=$(patsubst $(Static_lib_folder_code)$(lib_code_source)%.cpp, $(DEPOBJDIR)%.o, $(STATICCFILES))
OBJECTSSHARED=$(patsubst $(Shared_lib_folder_code)$(lib_code_source)%.cpp, $(DEPOBJDIR)%.o, $(SHAREDCFILES))

OBJECTS=$(patsubst $(ROOTDIR)%.cpp, $(DEPOBJDIR)%.o, $(CFILESROOT)) $(patsubst $(SOURCEDIR)%.cpp, $(DEPOBJDIR)%.o, $(CFILESSOURCE))
DEPFILES=$(patsubst $(ROOTDIR)%.cpp, $(DEPOBJDIR)%.d, $(CFILESROOT)) $(patsubst $(SOURCEDIR)%.cpp, $(DEPOBJDIR)%.d, $(CFILESSOURCE)) $(patsubst $(SOURCESTATIC)/%.cpp, $(DEPOBJDIR)/%.d, $(STATICCFILES)) $(patsubst $(SOURCESHARED)/%.cpp, $(DEPOBJDIR)/%.d, $(SHAREDCFILES)) $(patsubst $(SOURCEANAL)/%.cpp, $(DEPOBJDIR)/%.d, $(ANALCFILES)) $(patsubst $(SOURCETST)/%.cpp, $(DEPOBJDIR)/%.d, $(TSTCFILES))  
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

ANALCFILES=$(foreach D, $(SOURCEANAL), $(wildcard $(D)/*.cpp))
TSTCFILES=$(foreach D, $(SOURCETST), $(wildcard $(D)/*.cpp))
ANALOBJECTS=$(patsubst $(SOURCEANAL)%.cpp, $(DEPOBJDIR)%.o, $(ANALCFILES))
TSTOBJECTS=$(patsubst $(SOURCETST)%.cpp, $(DEPOBJDIR)%.o, $(TSTCFILES))

ANALdepend=
STATICdepend=
SHAREDdepend=
TSTdepend=

ifneq ($(strip $(STATICCFILES)), )
	STATICdepend:=$(STLIBGEN)
else
	STATICdepend:=
endif

ifneq ($(strip $(SHAREDCFILES)), )
	SHAREDdepend:=$(SHLIBGEN)
else
	SHAREDdepend:=
endif

ifneq ($(strip $(ANALCFILES)), )
	ANALdepend:=$(ANAL)
else
	ANALdepend:=
endif

ifneq ($(strip $(TSTCFILES)), )
	TSTdepend:=$(TST)
else
	TSTdepend:=
endif

STATICLIBGEN_link:=
SHAREDLIBGEN_link:=

ifneq ($(strip $(STATICCFILES)), )
	STATICLIBGEN_link:=-l$(STATICLIBGEN_name)
else
	STATICLIBGEN_link:=
endif

ifneq ($(strip $(SHAREDCFILES)), )
	SHAREDLIBGEN_link:=-l$(SHAREDLIBGEN_name)
else
	SHAREDLIBGEN_link:=
endif

ISSHARED=
ISSTATIC=

ifneq ($(strip $(SHAREDCFILES)), )
	ISSHARED:=$(foreach D,$(SHLIBS),-L$(D))
else
	ISSHARED:=$(ISSHARED)
endif

ifneq ($(strip $(LIBSHARED_files)), )
	ISSHARED:=$(foreach D,$(SHLIBS),-L$(D))
else
	ISSHARED:=$(ISSHARED)
endif

ifneq ($(strip $(STATICCFILES)), )
	ISSTATIC:=$(foreach D,$(STATLIBS),-L$(D))
else
	ISSTATIC:=$(ISSTATIC)
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

all:$(OUTPUT) $(ANALdepend) $(TSTdepend)
	@echo SUCCES

run:$(OUTPUT)
	@./$(OUTPUT)

runanal:$(ANALdepend)
	@./$(ANAL)

runtst:$(TSTdepend)
	@./$(TST)

anal:$(ANALdepend)

libs:$(STATICdepend) $(SHAREDdepend)

libstatic:$(STATICdepend)

libshared:$(SHAREDdepend)

tst:$(TSTdepend)

$(OUTPUT):$(STATICdepend) $(SHAREDdepend) $(OBJECTS)
	$(CPPC) $^ $(ISSTATIC) $(ISSHARED) $(foreach D,$(LIBSTATIC_names),-l$(D)) $(foreach D,$(LIBSHARED_names),-l$(D)) $(STATICLIBGEN_link) $(SHAREDLIBGEN_link) -o $@
	$(INCLUDESHARED)

$(ANAL):$(STATICdepend) $(SHAREDdepend) $(ANALOBJECTS) $(OBJECTS)
	$(CPPC) $(OBJECTS) $(ANALOBJECTS) -Wl,--defsym=main=$(ANALENTRY) $(ISSTATIC) $(ISSHARED) $(foreach D,$(LIBSTATIC_names),-l$(D)) $(foreach D,$(LIBSHARED_names),-l$(D)) $(STATICLIBGEN_link) $(SHAREDLIBGEN_link) -o $@
	$(INCLUDESHARED)

$(TST):$(STATICdepend) $(SHAREDdepend) $(TSTOBJECTS) $(OBJECTS)
	$(CPPC) $(OBJECTS) $(TSTOBJECTS) -Wl,--defsym=main=$(TSTENTRY) $(ISSTATIC) $(ISSHARED) $(foreach D,$(LIBSTATIC_names),-l$(D)) $(foreach D,$(LIBSHARED_names),-l$(D)) $(STATICLIBGEN_link) $(SHAREDLIBGEN_link) -o $@
	$(INCLUDESHARED)

mrproper:
	rm -rf $(OUTPUTS) $(OBJECTS) $(DEPFILES) $(STLIBGEN) $(SHLIBGEN) $(OBJECTSSTATIC) $(OBJECTSSHARED) $(ANALOBJECTS) $(TSTOBJECTS)

$(STLIBGEN):$(OBJECTSSTATIC)
	ar rc $(STLIBGEN) $(OBJECTSSTATIC)
	ranlib $(STLIBGEN)

$(SHLIBGEN):$(OBJECTSSHARED)
	$(CPPC) -shared -o $(SHLIBGEN) $(OBJECTSSHARED)

$(DEPOBJDIR)/%.o:$(SOURCESHARED)/%.cpp
	$(CPPC) $(CFLAGS) $(foreach D,$(INCDIRSHARED),-I$(D)) -fPIC -c $< -o $@

$(DEPOBJDIR)/%.o:$(SOURCESTATIC)/%.cpp
	$(CPPC) $(CFLAGS) $(foreach D,$(INCDIRSTATIC),-I$(D)) -c $< -o $@

$(DEPOBJDIR)/%.o:$(ROOTDIR)/%.cpp
	$(CPPC) $(CFLAGS) $(foreach D,$(INCDIRS),-I$(D)) -c -o $@ $<

$(DEPOBJDIR)/%.o:$(SOURCEDIR)/%.cpp
	$(CPPC) $(CFLAGS) $(foreach D,$(INCDIRS),-I$(D)) -c -o $@ $<

$(DEPOBJDIR)/%.o:$(SOURCEANAL)/%.cpp
	$(CPPC) $(CFLAGS) $(foreach D,$(INCDIRS),-I$(D)) -c -o $@ $<

$(DEPOBJDIR)/%.o:$(SOURCETST)/%.cpp
	$(CPPC) $(CFLAGS) $(foreach D,$(INCDIRS),-I$(D)) -c -o $@ $<

-include $(DEPFILES) 