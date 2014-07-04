###############################################################################
#                                                 Adagio Makefile [Linux x86] #
###############################################################################

ifndef TOPDIR
export TOPDIR		:= $(shell cd ../../ && pwd)
export TOPSRC		= $(TOPDIR)/Source
export TARGETDIR	= $(TOPDIR)/Bin/$(PLATFORM)/$(ARCH)/$(BITSIZE)
export OBJSDIR		= $(TOPDIR)/Obj/$(PLATFORM)/$(ARCH)/$(BITSIZE)/GCC/$(GCCVER)/$(BUILD)
endif

SOURCEDIR	= Source ../Common/Source

PROJECT	:= Adagio
TARGET	:= $(PROJECT)
OUTFILE	= $(TARGETDIR)/$(TARGET)_$(GCCVER)

PLATFORM		:= Linux
BUILD_PLATFORM	:= LINUX
ARCH			:= x86
BUILD_ARCH		:= X86
BITSIZE			:= 32

GCCVER	= $(shell $(CPP) -dumpversion)

BUILD_TYPE	:= debug

32BIT	?= False
64BIT	?= False

UNAME		= $(shell uname)
UNAME_MACH	= $(shell uname -m)

VERSIONINFO = $(TOPSRC)/$(PLATFORM)/Headers/GitVersion.hpp

ifeq ($(UNAME), Linux)
	CPPFLAGS_EXT	= -ffriend-injection -std=c++11
	SYSIPATH		= -I/usr/include/xorg
	PLATFORM		= Linux
	BUILD_PLATFORM	= LINUX
	LINKFLAGS		=
ifneq ($(64BIT), False)
	BUILD_ARCH	= X86
	ARCH		= x86
	BITSIZE		= 64
else
ifneq ($(32BIT), False)
	BUILD_ARCH	= X86
	ARCH		= x86
	BITSIZE		= 32
else
ifeq ($(UNAME_MACH), x86_64)
	BUILD_MACH	= X86
	ARCH		= x86
	BITSIZE		= 64
endif
ifeq ($(UNAME_MACH), i686)
	BUILD_ARCH	= X86
	ARCH		= x86
	BITSIZE		= 32
endif
endif
endif
endif

CPP	= g++

CPPFLAGS =	-c -m$(BITSIZE) -DBUILD_$(BUILD_DEF) \
			-DPLATFORM_$(BUILD_PLATFORM) \
			-DPLATFORM_$(BUILD_PLATFORM)_$(BUILD_ARCH) \
			-DPLATFORM_$(BUILD_PLATFORM)_$(BUILD_ARCH)_$(BITSIZE) \
			-DBITSIZE_$(BITSIZE) -DARCH_$(BUILD_ARCH) \
			-I$(TOPSRC)/$(PLATFORM)/Headers -I$(TOPSRC)/Common/Headers

SYSIPATH	=
INCPATH		=
SYSLPATH	=
LIBPATH		=
SYSLIBS		= -lX11 -lGL -lXrandr -lrt -pthread -lXi
LINKFLAGS	=

##### Debug Build #####
debug: BUILD		= Debug
debug: BUILD_TYPE	= debug
debug: BUILD_DEF	= DEBUG
debug: TARGET		:= $(TARGET)D
debug: CPPFLAGS		+= -g -ggdb -Wall -D_DEBUG $(CPPFLAGS_EXT)
debug: $(TARGET)

##### Release Build #####

release: BUILD		= Release
release: BUILD_TYPE	= release
release: BUILD_DEF	= RELEASE
release: TARGET		:= $(TARGET)
release: CPPFLAGS	+= -O3 -s -fomit-frame-pointer $(CPPFLAGS_EXT)
release: $(TARGET)

##### Profile Build #####
profile: BUILD		= Profile
profile: BUILD_TYPE = profile
profile: BUILD_DEF	= PROFILE
profile: TARGET		:= $(TARGET)P
profile: CPPFLAGS	+= -g -O3 $(CPPFLAGS_EXT)
profile: $(TARGET)

ifneq ($(OBJSDIR), $(CURDIR))
TARGETDIR:
	@mkdir -p $(TARGETDIR)

OBJSDIR:
	@mkdir -p $(OBJSDIR)

$(VERSIONINFO):
	@echo "------------------------ Generating Version Information -----------------------"
	@mkdir -p $(TOPSRC)/$(PLATFORM)/Headers
	@sh $(TOPSRC)/$(PLATFORM)/GitVersion.sh $(TOPSRC)/$(PLATFORM)/Headers/GitVersion.hpp $(PROJECT)
	@echo "-------------------------------------------------------------------------------"

CPPFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.cpp)))
export VPATH	:= $(foreach dir,$(SOURCEDIR),$(CURDIR)/$(dir))
export OBJS		:= $(CPPFILES:.cpp=.o)

$(TARGET): OBJSDIR TARGETDIR $(VERSIONINFO)
	@/usr/bin/time -f "%E" -o $(OBJSDIR)/compiletime \
	$(MAKE) --no-print-directory -C $(OBJSDIR) \
	-f $(TOPSRC)/$(PLATFORM)/Makefile $(BUILD_TYPE)
	@printf "\n%s\n" "-------------------------------------------------------------------------------"
	@printf "Compile time: "
	@cat $(OBJSDIR)/compiletime
	@echo "-------------------------------------------------------------------------------"

else

$(TARGET): $(OBJS)
	@if [ -s *.cmsgs ]; then\
		echo "-------------------------- MESSAGES FROM THE COMPILER -------------------------";\
		cat *.cmsgs;\
		echo "-------------------------------------------------------------------------------";\
	fi
	@echo ""	
	@printf "Creating: $(OUTFILE) ... "
	@$(CPP) -o $(OUTFILE) $(LINKFLAGS) -m$(BITSIZE) $(OBJS) $(SYSLPATH) \
	$(LIBPATH) $(LIBS) $(SYSLIBS) 2> lmsgs;\
	RETVAL=$$?;\
	if env | grep -q ^TERM=; then\
		COLOURSUPPORT=`tput colors`;\
		if [ $$COLOURSUPPORT -gt -1 ]; then\
			cat lmsgs | sed ''/error/s//`printf "\033[31merror\033[0m"`/'' > lmsgs;\
			cat lmsgs | sed ''/warning/s//`printf "\033[35mwarning\033[0m"`/'' > lmsgs;\
		fi;\
	fi;\
	if [ $$RETVAL -eq 0 ]; then\
		printf "[OK]\n";\
	else\
		printf "\n\n%s\n" "------------------------------------ ERROR ------------------------------------";\
		cat lmsgs;\
		echo "-------------------------------------------------------------------------------";\
		exit 1;\
	fi

%.o: %.cpp
	@printf "Compiling $< ... "
	@$(CPP) -MMD -MP -MF $*.d $(CPPFLAGS) $(SYSIPATH) $(INCPATH) $< -o $@ 2> $*.cmsgs;\
	RETVAL=$$?;\
	if env | grep -q ^TERM=; then\
		COLOURSUPPORT=`tput colors`;\
		if [ $$COLOURSUPPORT -gt -1 ]; then\
			cat $*.cmsgs | sed ''/error/s//`printf "\033[31merror\033[0m"`/'' > $*.cmsgs;\
			cat $*.cmsgs | sed ''/warning/s//`printf "\033[35mwarning\033[0m"`/'' > $*.cmsgs;\
		fi;\
	fi;\
	if [ $$RETVAL -eq 0 ]; then\
		printf "[OK]\n";\
	else\
		printf "\n\n%s\n" "------------------------------------ ERROR ------------------------------------";\
		cat $*.cmsgs;\
		echo "-------------------------------------------------------------------------------";\
		exit 1;\
	fi

-include $(OBJSDIR)/*.d
endif

.PHONY: clean completeclean

clean:
	rm -rf $(TARGETDIR)
	rm -rf $(OBJSDIR)

cleangit:
	rm -rf $(VERSIONINFO)

