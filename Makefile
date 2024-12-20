OUTPUT=main
EXT=cpp
CPPC=g++
INCDIR=./include 
OBJECTS=./depsAndObjects/main.o 
STATICdepend=
SHAREDdepend=
SHAREDFLAG=
ENTRY=main
DEPOBJDIR=./depsAndObjects
ContFile=./code.cpp
TSTfile=./testFile
ANSfile=./answerFile
TSTlogs=./logs
TSTgarbage=./tstFile ./ansFile ./mainFile ./genTest 
ANALgarbage=./analFile 
STLIBGEN=./libstatic.a
SHLIBGEN=./libshared.so
SHAREDLIBCOMMAND=
LIBNAMES=static 
LIBFOLDERS=./include/ 
C++standart=-std=c++23
OPT=-O3
DEPFLAGS=-MP -MD
GENERALFLAGS=$(C++standart) -g3 -w
CFLAGS=$(GENERALFLAGS) $(OPT) $(DEPFLAGS)
DEPFILES=$(patsubst %.o, %.d, $(OBJECTS))
all:$(OUTPUT)
	@echo ========= SUCCESS ==========
libstatic:$(STATICdepend)
	@echo ========= SUCCESS ==========
libshared:$(SHAREDdepend)
	@echo ========= SUCCESS ==========
$(OUTPUT):$(STATICdepend) $(SHAREDdepend) $(OBJECTS)
	$(CPPC) $(OBJECTS) -Wl,--defsym=main=$(ENTRY) $(foreach D,$(LIBFOLDERS),-L$(D)) $(foreach D,$(LIBNAMES),-l$(D)) -o $@
	$(SHAREDLIBCOMMAND)
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
$(DEPOBJDIR)/%.o:./%.$(EXT)
	$(CPPC) $(CFLAGS) $(foreach D,$(INCDIR),-I$(D)) $(SHAREDFLAG) -c $< -o $@
$(DEPOBJDIR)/%.o:./lib/%.$(EXT)
	$(CPPC) $(CFLAGS) $(foreach D,$(INCDIR),-I$(D)) $(SHAREDFLAG) -c $< -o $@

-include $(DEPFILES)
