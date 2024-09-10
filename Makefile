OUTPUT=prog
ANAL=algs
ANALstatic=algsST
ANALshared=algsSH
ANALstaticOTHER=algsSTother
ANALsharedOTHER=algsSHother
ANALstaticMY=algsSTmy
ANALsharedMY=algsSHmy
ANALsimp=algsSMP

OUTPUTstatic=progST
OUTPUTshared=progSH
OUTPUTstaticOTHER=progSTother
OUTPUTsharedOTHER=progSHother
OUTPUTstaticMY=progSTmy
OUTPUTsharedMY=progSHmy
OUTPUTsimp=progSMP


OUTPUTS=$(OUTPUT) $(ANAL) $(ANALstatic) $(ANALshared) $(ANALstaticOTHER) $(ANALsharedOTHER) $(ANALstaticMY) $(ANALsharedMY) $(ANALsimp) $(OUTPUTstatic) $(OUTPUTshared) $(OUTPUTstaticOTHER) $(OUTPUTsharedOTHER) $(OUTPUTstaticMY) $(OUTPUTsharedMY) $(OUTPUTsimp)

ROOTDIR=.
SOURCEDIR=./lib
DEPOBJDIR =./depsAndObjects
STATLIBS=./staticLibs
SHLIBS=./sharedLibs
Static_lib_folder_code=./staticLibsSource
Shared_lib_folder_code=./sharedLibsSource
lib_code_source=/source
lib_code_headers=/header
SOURCESTATIC=$(Static_lib_folder_code)$(lib_code_source)
SOURCESHARED=$(Shared_lib_folder_code)$(lib_code_source)
INCDIRSTATIC=$(Static_lib_folder_code)$(lib_code_headers)
INCDIRSHARED=$(Shared_lib_folder_code)$(lib_code_headers)
INCDIRS=. ./include/ $(INCDIRSTATIC) $(INCDIRSHARED)
STATICLIBGEN_name=static
SHAREDLIBGEN_name=shared
STLIBGEN=$(STATLIBS)/lib$(STATICLIBGEN_name).a
SHLIBGEN=$(SHLIBS)/lib$(SHAREDLIBGEN_name).so
CPPC=g++
C++standart=-std=c++20
OPT=-O2
DEPFLAGS=-MP -MD
GENERALFLAGS=$(C++standart) -g3
CFLAGS=$(GENERALFLAGS) $(foreach D,$(INCDIRS),-I$(D)) $(OPT) $(DEPFLAGS)
CFLAGS_static=$(GENERALFLAGS) $(foreach D,$(INCDIRSTATIC),-I$(D)) $(OPT) $(DEPFLAGS)
CFLAGS_shared=$(GENERALFLAGS) $(foreach D,$(INCDIRSHARED),-I$(D)) $(OPT) $(DEPFLAGS)
CFILESROOT=$(foreach D, $(ROOTDIR), $(wildcard $(D)/*.cpp))
CFILESSOURCE=$(foreach D, $(SOURCEDIR), $(wildcard $(D)/*.cpp))

STATICCFILES=$(foreach D, $(SOURCESTATIC), $(wildcard $(D)/*.cpp))
SHAREDCFILES=$(foreach D, $(SOURCESHARED), $(wildcard $(D)/*.cpp))

OBJECTSSTATIC=$(patsubst $(Static_lib_folder_code)$(lib_code_source)%.cpp, $(DEPOBJDIR)%.o, $(STATICCFILES))
OBJECTSSHARED=$(patsubst $(Shared_lib_folder_code)$(lib_code_source)%.cpp, $(DEPOBJDIR)%.o, $(SHAREDCFILES))

OBJECTS=$(patsubst $(ROOTDIR)%.cpp, $(DEPOBJDIR)%.o, $(CFILESROOT)) $(patsubst $(SOURCEDIR)%.cpp, $(DEPOBJDIR)%.o, $(CFILESSOURCE))
DEPFILES=$(patsubst $(ROOTDIR)%.cpp, $(DEPOBJDIR)%.d, $(CFILESROOT)) $(patsubst $(SOURCEDIR)%.cpp, $(DEPOBJDIR)%.d, $(CFILESSOURCE)) $(patsubst $(SOURCESTATIC)/%.cpp, $(DEPOBJDIR)/%.d, $(STATICCFILES)) $(patsubst $(SOURCESHARED)/%.cpp, $(DEPOBJDIR)/%.d, $(SHAREDCFILES))
LIBSTATIC_files=$(foreach D, $(STATLIBS), $(wildcard $(D)/lib*.a))
LIBSHARED_files=$(foreach D, $(SHLIBS), $(wildcard $(D)/lib*.so))
LIBSTATIC_names=$(patsubst $(STATLIBS)/lib%.a, %, $(LIBSTATIC_files))
LIBSHARED_names=$(patsubst $(SHLIBS)/lib%.so, %, $(LIBSHARED_files))



all:$(OUTPUT)
	@echo
	@echo
	@echo
	@echo RUN THIS COMMAND:
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(SHLIBS)


simple:$(OUTPUTsimp)


$(OUTPUTsimp):$(OBJECTS)
		$(CPPC) $^ -o $@

$(OUTPUT): $(OBJECTS) $(STLIBGEN) $(SHLIBGEN)
	$(CPPC) $^ $(foreach D,$(STATLIBS),-L$(D)) $(foreach D,$(SHLIBS),-L$(D)) $(foreach D,$(LIBSTATIC_names),-l$(D)) $(foreach D,$(LIBSHARED_names),-l$(D)) -l$(STATICLIBGEN_name) -l$(SHAREDLIBGEN_name) -o $@

$(DEPOBJDIR)/%.o:$(ROOTDIR)/%.cpp
	$(CPPC) $(CFLAGS) -c -o $@ $<

$(DEPOBJDIR)/%.o:$(SOURCEDIR)/%.cpp
	$(CPPC) $(CFLAGS) -c -o $@ $<

mrproper:
	rm -rf $(OUTPUTS) $(OBJECTS) $(DEPFILES) $(STLIBGEN) $(SHLIBGEN) $(OBJECTSSTATIC) $(OBJECTSSHARED)


static:$(OUTPUTstatic)

$(OUTPUTstatic):$(OBJECTS) $(STLIBGEN)
	$(CPPC) $^ $(foreach D,$(STATLIBS),-L$(D)) $(foreach D,$(LIBSTATIC_names),-l$(D)) -l$(STATICLIBGEN_name) -o $@

shared:$(OBJECTS) $(SHLIBGEN)
	$(CPPC) $^ $(foreach D,$(SHLIBS),-L$(D)) $(foreach D,$(LIBSHARED_names),-l$(D)) -l$(SHAREDLIBGEN_name) -o $@
	@echo
	@echo
	@echo
	@echo RUN THIS COMMAND:
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(SHLIBS)

MYstatic:$(OBJECTS) $(STLIBGEN)
	$(CPPC) $^ $(foreach D,$(STATLIBS),-L$(D)) -l$(STATICLIBGEN_name) -o $@

MYshared:$(OBJECTS) $(SHLIBGEN)
	$(CPPC) $^ $(foreach D,$(SHLIBS),-L$(D)) -l$(SHAREDLIBGEN_name) -o $@
	@echo
	@echo
	@echo
	@echo RUN THIS COMMAND:
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(SHLIBS)

OTHERstatic:$(OBJECTS)
	$(CPPC) $^ $(foreach D,$(STATLIBS),-L$(D)) $(foreach D,$(LIBSTATIC_names),-l$(D)) -o $@

OTHERshared:$(OBJECTS)
	$(CPPC) $^ $(foreach D,$(SHLIBS),-L$(D)) -o $@
	@echo
	@echo
	@echo
	@echo RUN THIS COMMAND:
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(SHLIBS)

libshared:$(SHLIBHEN)

libstatic:$(STLIBGEN)

libs:$(STLIBGEN) $(SHLIBGEN)

$(STLIBGEN):$(OBJECTSSTATIC)
	ar rc $(STLIBGEN) $(OBJECTSSTATIC)
	ranlib $(STLIBGEN)

$(SHLIBGEN):$(OBJECTSSHARED)
	$(CPPC) -shared -o $(SHLIBGEN) $(OBJECTSSHARED)

$(DEPOBJDIR)/%.o:$(SOURCESHARED)/%.cpp
	$(CPPC) $(CFLAGS_shared) -fPIC -c $< -o $@

$(DEPOBJDIR)/%.o:$(SOURCESTATIC)/%.cpp
	$(CPPC) $(CFLAGS_static) -c $< -o $@

-include $(DEPFILES) 