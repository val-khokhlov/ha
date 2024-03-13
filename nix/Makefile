############################################################################
#  This file is part of HA, a general purpose file archiver.
#  Copyright (C) 1995 Harri Hirvola
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
############################################################################
#	Makefile for *nix specific part of HA
############################################################################

OBJS =  machine.o info.o

.c.o:  
	$(CC) $(CFLAGS) -c $<

all: $(OBJS)

info.c: info.txt
	if [ -x ../ha ] ; then ../ha MAKEINFO info.txt info.c ; fi

depend dep:
	$(CPP) $(CFLAGS) -M *.c > .depend

clean: 
	rm -f .depend *.o *~

#
# include a dependency file if one exists
#
ifeq (.depend,$(wildcard .depend))
include .depend
endif

