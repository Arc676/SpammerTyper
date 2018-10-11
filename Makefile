# Makefile for SpammerTyper
# On Linux or Mac, use this Makefile to compile SpammerTyper
# On Windows, use the Visual Studio project
# You need to have a compiled version of Orx for your platform in the lib/ folder
# You may need to change the compiler if you don't have g++ in your PATH
SDIR=src
ODIR=obj
OUTDIR=Build
OUTPUT=$(OUTDIR)/SpammerTyper

CC=g++
FLAGS=-std=c++11 -c -o $(ODIR)/$(@F)
LD=-I inc/ -L lib/
LIB=-l orx

OBJS=Main.o StandAlone.o Character.o
_OBJS=$(patsubst %, $(ODIR)/%, $(OBJS))

ifdef DEBUG
	FLAGS += -g -O0
endif

CP=cp -u
ifdef MAC
	CP=cp
endif

spammertyper: copyassets $(_OBJS)
	$(CC) $(LD) $(_OBJS) $(LIB) -o $(OUTPUT)

copyassets:
	mkdir -p $(OUTDIR) $(ODIR)
	$(CP) bin/* $(OUTDIR)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(FLAGS) $(LD) $^

clean:
	rm -f $(ODIR)/*.o $(OUTPUT)

squeakyclean:
	rm -rf $(OUTDIR) $(ODIR)
