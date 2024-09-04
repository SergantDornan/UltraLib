OUTPUT=prog
ROOTDIR=.
SOURCEDIR=./lib
CODEDIRS=$(ROOTDIR) $(SOURCEDIR)
INCDIRS=. ./include/

DEPDIR =./deps
STATLIBS=./staticLibs
SHLIBS=./sharedLibs

Static_lib_folder_code=./staticLibsSource
Shared_lib_folder_code=./sharedLibsSource


SOURCESTATIC=$(Static_lib_folder_code)/source
SOURCESHARED=$(Shared_lib_folder_code)/source
INCDIRSTATIC=$(Static_lib_folder_code)/header
INCDIRSHARED=$(Shared_lib_folder_code)/header

STATICLIBGEN_name=static
SHAREDLIBGEN_name=shared


STLIBGEN=$(STATLIBS)/lib$(STATICLIBGEN_name).a
SHLIBGEN=$(SHLIBS)/lib$(SHAREDLIBGEN_name).so



CPPC=g++
C++standart=-std=c++20
OPT=-O2
DEPFLAGS=-MP -MD
GENERALFLAGS=-Wall -Werror -Wextra $(C++standart)
CFLAGS=$(GENERALFLAGS) $(foreach D,$(INCDIRS),-I$(D)) $(OPT) $(DEPFLAGS)
CFLAGS_static=$(GENERALFLAGS) $(foreach D,$(INCDIRSTATIC),-I$(D)) $(OPT) $(DEPFLAGS)
CFLAGS_shared=$(GENERALFLAGS) $(foreach D,$(INCDIRSHARED),-I$(D)) $(OPT) $(DEPFLAGS)

CFILESROOT=$(foreach D, $(ROOTDIR), $(wildcard $(D)/*.cpp))
CFILESSOURCE=$(foreach D, $(SOURCEDIR), $(wildcard $(D)/*.cpp))
CFILES=$(CFILESROOT) $(CFILESSOURCE)
 
OBJECTS=$(patsubst %.cpp, %.o, $(CFILES))
DEPFILES=$(patsubst %.cpp, %.d, $(CFILES))


STATICCFILES=$(foreach D, $(SOURCESTATIC), $(wildcard $(D)/*.cpp))
SHAREDCFILES=$(foreach D, $(SOURCESHARED), $(wildcard $(D)/*.cpp))
OBJECTSSTATIC=$(patsubst %.cpp, %.o, $(STATICCFILES))
OBJECTSSHARED=$(patsubst %.cpp, %.o, $(SHAREDCFILES))
DEPFILES_libs=$(patsubst %.cpp, %.d, $(STATICCFILES)) $(patsubst %.cpp, %.d, $(SHAREDCFILES))


DEPFILES_final=$(patsubst .%.cpp, $(DEPDIR)%.d, $(CFILESROOT)) $(patsubst ./lib%.cpp, $(DEPDIR)%.d, $(CFILESSOURCE)) $(patsubst $(SOURCESTATIC)/%.cpp, $(DEPDIR)/%.d, $(STATICCFILES)) $(patsubst $(SOURCESHARED)/%.cpp, $(DEPDIR)/%.d, $(SHAREDCFILES))


LIBSTATIC_files=$(foreach D, $(STATLIBS), $(wildcard $(D)/lib*.a))
LIBSHARED_files=$(foreach D, $(SHLIBS), $(wildcard $(D)/lib*.so))
LIBSTATIC_names=$(patsubst $(STATLIBS)/lib%.a, %, $(LIBSTATIC_files))
LIBSHARED_names=$(patsubst $(SHLIBS)/lib%.so, %, $(LIBSHARED_files))


all: $(OUTPUT)
	rm -rf $(OBJECTS)
	

$(OUTPUT): $(OBJECTS)
	mv $(DEPFILES) $(DEPDIR)
	$(MAKE) libs
	$(CPPC) $^ $(foreach D,$(STATLIBS),-L$(D)) $(foreach D,$(SHLIBS),-L$(D)) $(foreach D,$(LIBSTATIC_names),-l$(D)) $(foreach D,$(LIBSHARED_names),-l$(D)) -l$(STATICLIBGEN_name) -l$(SHAREDLIBGEN_name) -o $@
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(SHLIBS)

%.o:%.cpp
	$(CPPC) $(CFLAGS) -c -o $@ $<

mrproper:
	rm -rf $(OUTPUT) $(OBJECTS) $(DEPFILES_final) $(STLIBGEN) $(SHLIBGEN)

libs: $(OBJECTSSTATIC) $(OBJECTSSHARED)
	mv $(DEPFILES_libs) $(DEPDIR)
	ar rc $(STLIBGEN) $(OBJECTSSTATIC)
	ranlib $(STLIBGEN)
	$(CPPC) -shared -o $(SHLIBGEN) $(OBJECTSSHARED)
	rm -rf $(OBJECTSSTATIC) $(OBJECTSSHARED)
	

sh%.o:sh%.cpp
	$(CPPC) $(CFLAGS_shared) -fPIC -c $< -o $@ 

st%.o:st%.cpp
	$(CPPC) $(CFLAGS_static) -c $< -o $@

-include $(DEPFILES_final)
