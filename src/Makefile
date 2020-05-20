SOURCES		:= $(shell ls -tbd *.c *.cpp 2>/dev/null)
ALL		:= $(basename $(SOURCES))
EXECS		:= $(basename $(shell grep -zl 'int\s\+main' $(SOURCES)))
NEWEST		:= $(shell echo $(EXECS) |cut -d ' ' -f1)

CFLAGS		= -Wall -O -pipe -Wno-unused-result -Wno-long-long -pedantic -fdiagnostics-color=always
LDFLAGS		= 
DEBUG		?= 0

ifneq ($(DEBUG),0)
	CFLAGS += -g -DDEBUG
endif

ifdef FLAGS
	CFLAGS += $(FLAGS)
endif

CC		= gcc
CCFLAGS		= $(CFLAGS) -std=c99

CXX		= g++
CXXFLAGS	= $(CFLAGS) -std=c++0x

DEPDIR		= .deps
DEPFLAGS	= -MM
LDDEPFILE	= linkrules.mk

default: buzzquery

%.o: %.c $(DEPDIR)/%.d
	$(CC) -c $(CCFLAGS) $<

%.o: %.cpp $(DEPDIR)/%.d
	$(CXX) -c $(CXXFLAGS) $<

%: %.o
	$(CXX) -o $@ $^ $(LDFLAGS)

spotless: clean clean-deps
clean: clean-aux
	rm -f $(EXECS)
clean-aux:
	rm -f *.o
clean-deps:
	rm -f $(DEPDIR)/*.d

all: $(EXECS)

deps: $(patsubst %,$(DEPDIR)/%.d,$(ALL))
$(DEPDIR)/%.d: %.c
	@mkdir -p $(DEPDIR)
	$(CC) $(CCFLAGS) $(DEPFLAGS) -MF $@ $^
$(DEPDIR)/%.d: %.cpp
	@mkdir -p $(DEPDIR)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -MF $@ $^

include $(DEPDIR)/$(LDDEPFILE)
ifeq (,$(filter spotless clean%,$(MAKECMDGOALS)))
	-include $(ALL:%=$(DEPDIR)/%.d)
endif

.PRECIOUS: %.o $(DEPDIR)/%.d
.SUFFIXES:
