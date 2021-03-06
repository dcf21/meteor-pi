# MAKEFILE
# $Id: $

CWD=$(shell pwd)

VERSION = 0.0.1
DATE    = 05/01/2015

OPENMAX_COMPILE = -I /opt/vc/include -I /opt/vc/include/interface/vcos/pthreads -I /opt/vc/include/interface/vmcs_host/linux/
OPENMAX_LINK    = -L/opt/vc/lib -lopenmaxil -lvcos -lbcm_host -lpthread

COMPILE = $(CC) -Wall -g -fopenmp `gsl-config --cflags` $(shell pkg-config --cflags libv4l2) -c -I $(CWD)/src ${OPENMAX_COMPILE}
LINK    = $(CC) -Wall -g -fopenmp
LIBS    = `gsl-config --libs` $(shell pkg-config --libs libv4l2) -lpng -ljpeg -lm

OPTIMISATION = -O1

DEBUG   = -D DEBUG=1
NODEBUG = -D DEBUG=0

LOCAL_SRCDIR = src
LOCAL_OBJDIR = obj
LOCAL_DOCDIR = doc
LOCAL_BINDIR = bin

COMMON_FILES = asciidouble.c color.c error.c jpeg_in.c jpeg_out.c tools.c v4l2uvc.c JulianDate.c

VIDREC_FILES = $(COMMON_FILES) vidRec.c
OBSERV_FILES = $(COMMON_FILES) observe.c
SNAPSH_FILES = $(COMMON_FILES) snapshot.c
RAWJPG_FILES = $(COMMON_FILES) raw2jpeg.c
RAWRGB_FILES = $(COMMON_FILES) raw2rgbpng.c
RAWFRM_FILES = $(COMMON_FILES) raw2frames.c
RAWOPM_FILES = $(COMMON_FILES) raw2openmax.c
MEDIAN_FILES = $(COMMON_FILES) makeMedianMap.c

HEADERS = asciidouble.h color.h error.h jpeg.h settings.h str_constants.h tools.h uvc_compat.h uvcvideo.h v4l2uvc.h JulianDate.h

VIDREC_SOURCES         = $(VIDREC_FILES:%.c=$(LOCAL_SRCDIR)/%.c)
VIDREC_OBJECTS         = $(VIDREC_FILES:%.c=$(LOCAL_OBJDIR)/%.o)
VIDREC_OBJECTS_DEBUG   = $(VIDREC_OBJECTS:%.o=%.debug.o)

OBSERV_SOURCES         = $(OBSERV_FILES:%.c=$(LOCAL_SRCDIR)/%.c)
OBSERV_OBJECTS         = $(OBSERV_FILES:%.c=$(LOCAL_OBJDIR)/%.o)
OBSERV_OBJECTS_DEBUG   = $(OBSERV_OBJECTS:%.o=%.debug.o)

SNAPSH_SOURCES         = $(SNAPSH_FILES:%.c=$(LOCAL_SRCDIR)/%.c)
SNAPSH_OBJECTS         = $(SNAPSH_FILES:%.c=$(LOCAL_OBJDIR)/%.o)
SNAPSH_OBJECTS_DEBUG   = $(SNAPSH_OBJECTS:%.o=%.debug.o)

RAWJPG_SOURCES         = $(RAWJPG_FILES:%.c=$(LOCAL_SRCDIR)/%.c)
RAWJPG_OBJECTS         = $(RAWJPG_FILES:%.c=$(LOCAL_OBJDIR)/%.o)
RAWJPG_OBJECTS_DEBUG   = $(RAWJPG_OBJECTS:%.o=%.debug.o)

RAWRGB_SOURCES         = $(RAWRGB_FILES:%.c=$(LOCAL_SRCDIR)/%.c)
RAWRGB_OBJECTS         = $(RAWRGB_FILES:%.c=$(LOCAL_OBJDIR)/%.o)
RAWRGB_OBJECTS_DEBUG   = $(RAWRGB_OBJECTS:%.o=%.debug.o)

RAWFRM_SOURCES         = $(RAWFRM_FILES:%.c=$(LOCAL_SRCDIR)/%.c)
RAWFRM_OBJECTS         = $(RAWFRM_FILES:%.c=$(LOCAL_OBJDIR)/%.o)
RAWFRM_OBJECTS_DEBUG   = $(RAWFRM_OBJECTS:%.o=%.debug.o)

RAWOPM_SOURCES         = $(RAWOPM_FILES:%.c=$(LOCAL_SRCDIR)/%.c)
RAWOPM_OBJECTS         = $(RAWOPM_FILES:%.c=$(LOCAL_OBJDIR)/%.o)
RAWOPM_OBJECTS_DEBUG   = $(RAWOPM_OBJECTS:%.o=%.debug.o)

MEDIAN_SOURCES         = $(MEDIAN_FILES:%.c=$(LOCAL_SRCDIR)/%.c)
MEDIAN_OBJECTS         = $(MEDIAN_FILES:%.c=$(LOCAL_OBJDIR)/%.o)
MEDIAN_OBJECTS_DEBUG   = $(MEDIAN_OBJECTS:%.o=%.debug.o)

ALL_HFILES             = $(HEADERS:%.h=$(LOCAL_SRCDIR)/%.h) Makefile

COMMON_SWITCHES = -D VERSION=\"$(VERSION)\"  -D DATE=\"$(DATE)\"  -D SRCDIR=\"$(CWD)/$(LOCAL_SRCDIR)/\"

all: $(LOCAL_BINDIR)/vidRec $(LOCAL_BINDIR)/debug/vidRec $(LOCAL_BINDIR)/snapshot $(LOCAL_BINDIR)/debug/snapshot $(LOCAL_BINDIR)/raw2jpeg $(LOCAL_BINDIR)/debug/raw2jpeg $(LOCAL_BINDIR)/raw2rgbpng $(LOCAL_BINDIR)/debug/raw2rgbpng $(LOCAL_BINDIR)/raw2frm $(LOCAL_BINDIR)/debug/raw2frm $(LOCAL_BINDIR)/makeMedianMap $(LOCAL_BINDIR)/debug/makeMedianMap $(LOCAL_BINDIR)/observe $(LOCAL_BINDIR)/debug/observe

#
# General macros for the compile steps
#

$(LOCAL_OBJDIR)/%.o:         $(LOCAL_SRCDIR)/%.c $(ALL_HFILES)
	mkdir -p $(LOCAL_OBJDIR) 
	$(COMPILE) $(OPTIMISATION) $(NODEBUG) $(COMMON_SWITCHES) $< -o $@

$(LOCAL_OBJDIR)/%.debug.o:   $(LOCAL_SRCDIR)/%.c $(ALL_HFILES)
	mkdir -p $(LOCAL_OBJDIR)
	$(COMPILE) $(OPTIMISATION) $(DEBUG)   $(COMMON_SWITCHES)     $< -o $@

#
# Make the binaries
#

$(LOCAL_BINDIR)/vidRec:         $(VIDREC_OBJECTS)
	mkdir -p $(LOCAL_BINDIR)
	$(LINK) $(OPTIMISATION) $(VIDREC_OBJECTS) $(LIBS)       -o $(LOCAL_BINDIR)/vidRec

$(LOCAL_BINDIR)/debug/vidRec:   $(VIDREC_OBJECTS_DEBUG)
	mkdir -p $(LOCAL_BINDIR)/debug
	$(LINK) $(OPTIMISATION) $(VIDREC_OBJECTS_DEBUG) $(LIBS) -o $(LOCAL_BINDIR)/debug/vidRec

$(LOCAL_BINDIR)/observe:        $(OBSERV_OBJECTS)
	mkdir -p $(LOCAL_BINDIR)
	$(LINK) $(OPTIMISATION) $(OBSERV_OBJECTS) $(LIBS)       -o $(LOCAL_BINDIR)/observe

$(LOCAL_BINDIR)/debug/observe:  $(OBSERV_OBJECTS_DEBUG)
	mkdir -p $(LOCAL_BINDIR)/debug
	$(LINK) $(OPTIMISATION) $(OBSERV_OBJECTS_DEBUG) $(LIBS) -o $(LOCAL_BINDIR)/debug/observe

$(LOCAL_BINDIR)/snapshot:       $(SNAPSH_OBJECTS)
	mkdir -p $(LOCAL_BINDIR)
	$(LINK) $(OPTIMISATION) $(SNAPSH_OBJECTS) $(LIBS)       -o $(LOCAL_BINDIR)/snapshot

$(LOCAL_BINDIR)/debug/snapshot: $(SNAPSH_OBJECTS_DEBUG)
	mkdir -p $(LOCAL_BINDIR)/debug
	$(LINK) $(OPTIMISATION) $(SNAPSH_OBJECTS_DEBUG) $(LIBS) -o $(LOCAL_BINDIR)/debug/snapshot

$(LOCAL_BINDIR)/raw2jpeg:       $(RAWJPG_OBJECTS)
	mkdir -p $(LOCAL_BINDIR)
	$(LINK) $(OPTIMISATION) $(RAWJPG_OBJECTS) $(LIBS)       -o $(LOCAL_BINDIR)/raw2jpeg

$(LOCAL_BINDIR)/debug/raw2jpeg: $(RAWJPG_OBJECTS_DEBUG)
	mkdir -p $(LOCAL_BINDIR)/debug
	$(LINK) $(OPTIMISATION) $(RAWJPG_OBJECTS_DEBUG) $(LIBS) -o $(LOCAL_BINDIR)/debug/raw2jpeg

$(LOCAL_BINDIR)/raw2rgbpng:    $(RAWRGB_OBJECTS)
	mkdir -p $(LOCAL_BINDIR)
	$(LINK) $(OPTIMISATION) $(RAWRGB_OBJECTS) $(LIBS)       -o $(LOCAL_BINDIR)/raw2rgbpng

$(LOCAL_BINDIR)/debug/raw2rgbpng: $(RAWRGB_OBJECTS_DEBUG)
	mkdir -p $(LOCAL_BINDIR)/debug
	$(LINK) $(OPTIMISATION) $(RAWRGB_OBJECTS_DEBUG) $(LIBS) -o $(LOCAL_BINDIR)/debug/raw2rgbpng

$(LOCAL_BINDIR)/raw2frm:        $(RAWFRM_OBJECTS)
	mkdir -p $(LOCAL_BINDIR)
	$(LINK) $(OPTIMISATION) $(RAWFRM_OBJECTS) $(LIBS)       -o $(LOCAL_BINDIR)/raw2frm

$(LOCAL_BINDIR)/debug/raw2frm:  $(RAWFRM_OBJECTS_DEBUG)
	mkdir -p $(LOCAL_BINDIR)/debug
	$(LINK) $(OPTIMISATION) $(RAWFRM_OBJECTS_DEBUG) $(LIBS) -o $(LOCAL_BINDIR)/debug/raw2frm

$(LOCAL_BINDIR)/raw2opm:        $(RAWOPM_OBJECTS)
	mkdir -p $(LOCAL_BINDIR)
	$(LINK) $(OPTIMISATION) $(RAWOPM_OBJECTS) $(OPENMAX_LINK) $(LIBS)       -o $(LOCAL_BINDIR)/raw2opm

$(LOCAL_BINDIR)/debug/raw2opm:  $(RAWOPM_OBJECTS_DEBUG)
	mkdir -p $(LOCAL_BINDIR)/debug
	$(LINK) $(OPTIMISATION) $(RAWOPM_OBJECTS_DEBUG) $(LIBS) -o $(LOCAL_BINDIR)/debug/raw2opm

$(LOCAL_BINDIR)/makeMedianMap:  $(MEDIAN_OBJECTS)
	mkdir -p $(LOCAL_BINDIR)
	$(LINK) $(OPTIMISATION) $(MEDIAN_OBJECTS) $(LIBS)       -o $(LOCAL_BINDIR)/makeMedianMap

$(LOCAL_BINDIR)/debug/makeMedianMap:$(MEDIAN_OBJECTS_DEBUG)
	mkdir -p $(LOCAL_BINDIR)/debug
	$(LINK) $(OPTIMISATION) $(MEDIAN_OBJECTS_DEBUG) $(LIBS) -o $(LOCAL_BINDIR)/debug/makeMedianMap

#
# Clean macros
#

clean:
	rm -vfR $(LOCAL_OBJDIR) $(LOCAL_BINDIR) gnom.log*

afresh: clean all

