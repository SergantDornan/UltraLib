#include <filework.h>
#include <reg.h>
const std::string builderOutfile = "builder";
const std::string mainSourceFileName = "./buildercode/source/build.cpp";
const std::string depFolder = "depsAndObjects";
const std::string staticLibsFolder = "staticLibs";
const std::string sharedLibsFolder = "sharedLibs";
const std::string contFile = "code";
const std::string TSTfile = "testFile";
const std::string ANSfile = "answerFile";
const std::string TSTlogs = "logs";
const std::vector<std::string> TSTgarbage = {"tstFile", "ansFile", "mainFile", "genTest"};
const std::vector<std::string> ANALgarbage = {"analFile"};
const std::string STATICLIBGEN_name = "static";
const std::string SHAREDLIBGEN_name = "shared";
const std::string defaultMakefile = "C++standart=-std=c++23\nOPT=-O3\nDEPFLAGS=-MP -MD\nGENERALFLAGS=$(C++standart) -g3 -w\nSTLIBGEN=$(STATLIBS)/lib$(STATICLIBGEN_name).a\nSHLIBGEN=$(SHLIBS)/lib$(SHAREDLIBGEN_name).so\nCFLAGS=$(GENERALFLAGS) $(OPT) $(DEPFLAGS)\nDEPFILES=$(patsubst %.o, %.d, $(OBJECTS))\nLIBSTATIC_files=$(foreach D, $(STATLIBS), $(wildcard $(D)/lib*.a))\nLIBSHARED_files=$(foreach D, $(SHLIBS), $(wildcard $(D)/lib*.so))\nLIBSTATIC_names=\nLIBSHARED_names=\nifneq ($(LIBSHARED_files), )\n	LIBSHARED_names:=$(patsubst $(SHLIBS)/lib%.so, %, $(LIBSHARED_files))\nelse\n	LIBSHARED_names:=\nendif\nifneq ($(LIBSTATIC_files), )\n	LIBSTATIC_names:=$(patsubst $(STATLIBS)/lib%.a, %, $(LIBSTATIC_files))\nelse\n	LIBSTATIC_names:=\nendif\nISSHARED=\nISSTATIC=\nifneq ($(strip $(LIBSHARED_files)), )\n	ISSHARED:=$(foreach D,$(SHLIBS),-L$(D))\nelse\n	ISSHARED:=$(ISSHARED)\nendif\nifneq ($(strip $(LIBSTATIC_files)), )\n	ISSTATIC:=$(foreach D,$(STATLIBS),-L$(D))\nelse\n	ISSTATIC:=$(ISSTATIC)\nendif\nINCLUDESHARED:=\nifeq ($(ISSHARED),$(foreach D,$(SHLIBS),-L$(D)))\n	INCLUDESHARED:=export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(SHLIBS)\nelse\n	INCLUDESHARED:=\nendif\nall:$(OUTPUT)\n	@echo ========= SUCCESS ==========\nlibstatic:$(STATICdepend)\n	@echo ========= SUCCESS ==========\nlibshared:$(SHAREDdepend)\n	@echo ========= SUCCESS ==========\n$(OUTPUT):$(STATICdepend) $(SHAREDdepend) $(OBJECTS)\n	$(CPPC) $(OBJECTS) -Wl,--defsym=main=$(ENTRY) $(ISSTATIC) $(ISSHARED) $(foreach D,$(LIBSTATIC_names),-l$(D)) $(foreach D,$(LIBSHARED_names),-l$(D)) -o $@\n	$(INCLUDESHARED)\nmrproper:\n	rm -rf $(OBJECTS) $(DEPFILES) $(TSTgarbage) $(ANALgarbage)\npurge:\n	rm -rf $(OBJECTS) $(DEPFILES) $(STLIBGEN) $(SHLIBGEN) $(ContFile) $(TSTfile) $(ANSfile) $(TSTlogs) $(TSTgarbage) $(ANALgarbage)\n$(STLIBGEN):$(OBJECTS)\n	ar rc $(STLIBGEN) $(OBJECTS)\n	ranlib $(STLIBGEN)\n$(SHLIBGEN):$(OBJECTS)\n	$(CPPC) -shared -o $(SHLIBGEN) $(OBJECTS)";

void getAllheaders(std::vector<std::string>&,const std::string path = "./");
void getAllsource(std::vector<std::string>&,const std::string path = "./");
void createMakeFile(const std::string&,const std::string&,const std::string&,
	const std::vector<std::string>&,const std::vector<std::string>&,const std::string&);
void createEssentials(const std::string&, const std::string&, const std::string&);
void includeFiles(std::vector<std::string>&,const std::vector<std::string>&,const std::string&);
void sourceFiles(std::vector<std::string>&,const std::vector<std::string>&,
	const std::vector<std::string>&);
std::string defineEntryPoint(const std::string&);
std::string rulesGen(const std::vector<std::string>&);
std::string objectsGen(const std::vector<std::string>&);
void stripExt(std::vector<std::string>&, const std::string&);
void refreshObjects(const std::string&);
void createOnefile(const std::string&,const std::vector<std::string>&,const std::vector<std::string>&,
	const std::string&,const std::string&);
void push_line(std::vector<std::string>&,const std::string&);
void writeHeaderFiles(std::vector<std::string>&,const std::vector<std::string>&);
void writeIncludes(std::vector<std::string>&,const std::vector<std::string>&);
void writeSourceFiles(std::vector<std::string>&,const std::vector<std::string>&);
void writeMainFile(std::vector<std::string>&,const std::vector<std::string>&,const std::string&);