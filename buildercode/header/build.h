#include <filework.h>
#include <reg.h>
struct function{
	std::string type, name;
	std::vector<std::string> args;
};
const std::string sourceCodeFolder = "/home/sergantdornan/MasterFolder/UBERMENSCHENAMOGUS228/";
const std::string builderOutfile = "builder";
const std::string mainSourceFileName = sourceCodeFolder + "buildercode/source/build.cpp";
const std::string depFolder = "depsAndObjects";
const std::string contFile = "code";
const std::string TSTfile = "testFile";
const std::string ANSfile = "answerFile";
const std::string TSTlogs = "logs";
const std::vector<std::string> TSTgarbage = {"tstFile", "ansFile", "mainFile", "genTest"};
const std::vector<std::string> ANALgarbage = {"analFile"};
const std::string STATICLIBGEN_name = "static";
const std::string SHAREDLIBGEN_name = "shared";
const std::string defaultMakefile = "C++standart=-std=c++23\nOPT=-O3\nDEPFLAGS=-MP -MD\nGENERALFLAGS=$(C++standart) -g3 -w\nCFLAGS=$(GENERALFLAGS) $(OPT) $(DEPFLAGS)\nDEPFILES=$(patsubst %.o, %.d, $(OBJECTS))\nall:$(OUTPUT)\n	@echo ========= SUCCESS ==========\nlibstatic:$(STATICdepend)\n	@echo ========= SUCCESS ==========\nlibshared:$(SHAREDdepend)\n	@echo ========= SUCCESS ==========\n$(OUTPUT):$(STATICdepend) $(SHAREDdepend) $(OBJECTS)\n	$(CPPC) $(OBJECTS) -Wl,--defsym=main=$(ENTRY) $(foreach D,$(LIBFOLDERS),-L$(D)) $(foreach D,$(LIBNAMES),-l$(D)) -o $@\n	$(SHAREDLIBCOMMAND)\nmrproper:\n	rm -rf $(OBJECTS) $(DEPFILES) $(TSTgarbage) $(ANALgarbage)\npurge:\n	rm -rf $(OBJECTS) $(DEPFILES) $(STLIBGEN) $(SHLIBGEN) $(ContFile) $(TSTfile) $(ANSfile) $(TSTlogs) $(TSTgarbage) $(ANALgarbage)\n$(STLIBGEN):$(OBJECTS)\n	ar rc $(STLIBGEN) $(OBJECTS)\n	ranlib $(STLIBGEN)\n$(SHLIBGEN):$(OBJECTS)\n	$(CPPC) -shared -o $(SHLIBGEN) $(OBJECTS)\n$(DEPOBJDIR)/%.o:./%.$(EXT)\n	$(CPPC) $(CFLAGS) $(foreach D,$(INCDIR),-I$(D)) $(SHAREDFLAG) -c $< -o $@\n$(DEPOBJDIR)/%.o:./lib/%.$(EXT)\n	$(CPPC) $(CFLAGS) $(foreach D,$(INCDIR),-I$(D)) $(SHAREDFLAG) -c $< -o $@\n-include $(DEPFILES)";

void getAllheaders(std::vector<std::string>&,const std::string path = "./");
void getAllsource(std::vector<std::string>&,const std::string path = "./");
void createMakeFile(const std::string&,const std::string&,const std::string&,
	const std::vector<std::string>&,const std::vector<std::string>&,const std::string&);
void createEssentials(const std::string&, const std::string&, const std::string&);
void includeFiles(std::vector<std::string>&,const std::vector<std::string>&, const std::vector<std::string>&,const std::string&);
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
std::string getFolder(const std::string&);
void getAllStaticLibs(std::vector<std::string>&, const std::string path = "./");
void getAllSharedLibs(std::vector<std::string>&, const std::string path = "./");
void getLibsFolders(std::vector<std::string>&, const std::vector<std::string>&);
void getLibNamesStatic(std::vector<std::string>&, const std::vector<std::string>&);
void getLibNamesShared(std::vector<std::string>&, const std::vector<std::string>&);
void MrProperSourceFiles(std::vector<std::string>&, const std::vector<std::string>&);
void sourceFiles(std::vector<std::string>&, const std::vector<std::string>&,
	const std::vector<std::string>&,int);