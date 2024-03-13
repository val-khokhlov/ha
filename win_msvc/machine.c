/***********************************************************************
  This file is part of HA, a general purpose file archiver.
  Copyright (C) 1995 Harri Hirvola

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
************************************************************************
	HA win32 specific routines combined by val khokhlov
***********************************************************************/

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/utime.h>
#include <time.h>
#include "ha.h"
#include "error.h"
#include "archive.h"
#include <string.h>

typedef struct {
    unsigned char attr;
} Mdhd;

static Mdhd mdhd;
struct stat filestat;

	
static void sig_handler(int signo) {

    error(1,ERR_INT,signo);
}

void md_init(void) {

    signal(SIGINT,sig_handler);	
}

char *md_strcase(char *s) {
    
    int i;
    
    for (i=0;s[i];++i) s[i]=tolower(s[i]);
    return s;
}

char *md_arcname(char *name_req) {

    int pos;
    char *newname;

    pos=strlen(name_req);
    if (pos>3 && 
	tolower(name_req[pos-1])=='a' && 
	tolower(name_req[pos-2])=='h' && 
	name_req[pos-3]=='.') return name_req;
    if ((newname=malloc(pos+4))==NULL) error(1,ERR_MEM,"md_arcname()");
    strcpy(newname,name_req);
    strcpy(newname+pos,".ha");
    return newname;
}

void md_gethdr(int len, int mode) {
    
    static int longest=0;
    static unsigned char *buf=NULL;
    
    if (len>longest) {
	if (buf!=NULL) buf=realloc(buf,len);
	else buf=malloc(len);
	if (buf==NULL) error(1,ERR_MEM,"md_gethdr()");
	longest=len;
    }
    read(arcfile,buf,len);
    if (buf[0]==MSDOSMDH) mdhd.attr=buf[1];
    else {
	switch(mode) {
	  case M_DIR:
	    mdhd.attr=FA_DIREC;
	    break;
	  default:
	    mdhd.attr=FA_ARCH;
	    break;
	}
    }
}

void md_puthdr(void) {

    unsigned char buf[2];
    
    buf[0]=MSDOSMDH;
    buf[1]=mdhd.attr;
    write(arcfile,buf,2);
}

static int samefile(char *f1, char *f2) {
	
    S16B rv;
    
    f1=_fullpath(NULL,f1,0);
    f2=_fullpath(NULL,f2,0);
    md_strcase(f1);
    md_strcase(f2);
    if (f1==NULL || f2==NULL) {
	if (f1!=NULL) free(f1);
	if (f2!=NULL) free(f2);
	rv=0;
    }	
    else {
	if (strcmp(f1,f2)==0) rv=1;
	else rv=0;
	free(f1);
	free(f2);
    }
    return rv;
}

#include <windows.h>
int md_filetype(char *path, char *name) {

    char *fullpath;
    DWORD dwAttrs;
    
    if (!strcmp(name,".") || !strcmp(name,"..")) return T_SKIP;
    fullpath=md_pconcat(0,path,name);
    if (stat(fullpath,&filestat)<0) {
	error(0,ERR_STAT,fullpath);
	free(fullpath);
	return T_SKIP;
    }
    mdhd.attr = dwAttrs = GetFileAttributes(fullpath);
    if (samefile(arcname, fullpath)) {
	free(fullpath);
	return T_SKIP;
    }
    if (mdhd.attr&FA_DIREC) return T_DIR;
    if (mdhd.attr&(FA_HIDDEN|FA_SYSTEM|FA_LABEL)) {
	if (!special) return T_SKIP;
	else return T_REGULAR; 
    }
    return T_REGULAR;
}

int md_newfile(void) {
    
    return 2;
}

void md_setft(char *file,U32B time) {
    
    struct utimbuf utb;
    
    utb.actime=time;
    utb.modtime=time;
    utime(file,&utb);
}

void md_setfattrs(char *file) {

    if (useattr) SetFileAttributes(file,mdhd.attr);
}

U32B md_systime(void) {

    return (U32B)time(NULL);
}

void md_listhdr(void) {
    
    printf("\ndhsar  ");
}

static char *attrstring(unsigned attr) {

    static char as[6];
    
    sprintf(as,"%c%c%c%c%c",
	    (attr&FA_DIREC)?'d':'-',
	    (attr&FA_HIDDEN)?'h':'-',
	    (attr&FA_SYSTEM)?'s':'-',
	    (attr&FA_ARCH)?'a':'-',
	    (attr&FA_RDONLY)?'r':'-');
    return as;
}

void md_listdat(void) {
    
    printf("\n %s",attrstring(mdhd.attr));
}

char *md_timestring(unsigned long t) {
    
    static char ts[22];
    struct tm *tim;	
    
    tim=localtime((long *)&t);
    sprintf(ts,"%04d-%02d-%02d  %02d:%02d",tim->tm_year+1900,tim->tm_mon+1,
	    tim->tm_mday,tim->tm_hour,tim->tm_min);
    return ts;	
}

void md_truncfile(int fh, U32B len) {

    chsize(fh,len);	
}

char *md_tohapath(char *mdpath) {

    static char p[_MAX_PATH];
    int i,j;
    
    for (i=0;mdpath[i];++i) if (mdpath[i]!='.' && mdpath[i]!='\\' && mdpath[i]!='/') break;
    while (i>0 && mdpath[i-1]=='.') --i;
    if (i==0) skipemptypath=1;
    else skipemptypath=0;
    for (j=0;mdpath[i];++i) {
	switch(mdpath[i]) {
	  case '\\' :
	  case '/' :
	    p[j++]=0xff;
	    break;
	  default :
	    p[j++]=mdpath[i];
	    break;
	}
    }
    p[j]=0;
    return md_strcase(p);
}

static int md_trunclast(char *s) {
	
    char *ptr,*optr,name[8],ext[3];
    int i,olen,nlen,elen;
    
    if ((ptr=strrchr(s,'\\'))==NULL) ptr=s;
    else ++ptr;
    optr=ptr;
    olen=strlen(ptr);
    if (*ptr=='.') *ptr='_';
    for (i=0;i<8;++i,++ptr) {
	if (!*ptr || *ptr=='.') break;
	name[i]=*ptr;
    }
    nlen=i;
    if (!*ptr || (ptr=strrchr(ptr,'.'))==NULL) {
	if (olen>8) {
	    for (ptr=optr,i=0;i<nlen;++i) *ptr++=name[i];
	    *ptr=0;
	}
	return olen-nlen;
    }
    ++ptr;
    for (i=0;i<3;++i,++ptr) {
	if (!*ptr) break;
	ext[i]=*ptr;
    }
    elen=i;
    for (ptr=optr,i=0;i<nlen;++i) *ptr++=name[i];
    *ptr++='.';
    for (i=0;i<elen;++i) *ptr++=ext[i];
    *ptr=0;
    return olen-nlen-elen-1;	
}

char *md_tomdpath(char *hapath) {

    static char p[_MAX_PATH];
    int i,j;
	
    for (i=j=0;hapath[i];++i) {
	switch((unsigned char)hapath[i]) {
	  case 0xff :
	    p[j]=0;
	    j-=md_trunclast(p);
	    p[j++]='\\';
	    break;
	  default :
	    p[j++]=hapath[i];
	    break;
	}
	}
    p[j]=0;
    j-=md_trunclast(p);
    p[j]=0;
    return p;
}

char *md_strippath(char *mdfullpath) {
    
    int i;
    static char *plainpath=NULL;
    
    if (plainpath!=NULL) free(plainpath),plainpath=NULL;
    if ((plainpath=malloc(strlen(mdfullpath)+1))==NULL) 
      error(1,ERR_MEM,"md_strippath()");
    strcpy(plainpath,mdfullpath);
    for (i=strlen(plainpath)-1;i>=0;i--) {
	if (plainpath[i]=='\\') break; 
    }
    plainpath[i+1]=0;
    return plainpath;
}

char *md_stripname(char *mdfullpath) {
    
    int i;
    static char *plainname=NULL;
    
    if (plainname!=NULL) free(plainname),plainname=NULL;
    if ((plainname=malloc(strlen(mdfullpath)+1))==NULL) 
      error(1,ERR_MEM,"md_stripname()");
    for (i=strlen(mdfullpath)-1;i>0;i--) {
	if (mdfullpath[i]=='\\') {
	    i++;
	    break;
	}
    }
    strcpy(plainname,mdfullpath+i);
    return plainname;

}


char *md_pconcat(int delim, char *head, char *tail) {

    char *newpath;
    int headlen,delim1;

    delim1=0;
    if ((headlen=strlen(head))!=0)  {
	if (head[headlen-1]!='\\' && head[headlen-1]!=':') delim1=1;
    }
    if ((newpath=malloc(headlen+strlen(tail)+delim+delim1+1))==NULL) 
      error(1,ERR_MEM,"md_pconcat()");
    if (headlen!=0) strcpy(newpath,head);
    if (delim1) newpath[headlen]='\\';
    strcpy(newpath+headlen+delim1,tail);
    if (delim) strcpy(newpath+strlen(newpath),"\\");
    return newpath;
}

int md_mkspecial(char *ofname,unsigned sdlen,unsigned char *sdata) {

    error(0,ERR_HOW,ofname);
    return 0;
}

int md_namecmp(char *pat, char *cmp) {

    for (;*pat;++pat) {
	switch(*pat) {
	  case '?' :
	    if (*cmp!='.' && *cmp) ++cmp;
	    break;
	  case '*' :
	    while (*cmp!='.' && *cmp) ++cmp;
	    break;
	  case '.' :
	    if (*cmp=='.') {
		cmp=strrchr(cmp,'.');
		++cmp;
	    }
	    else if (*cmp) return 0;
	    else {
		do ++pat; while (*pat=='?');
		if (*pat==0 || *pat=='*') {
		    while (*pat) ++pat;
		}
		--pat;
	    }
	    break;
	  default :
	    if (*cmp!=*pat) return 0;
	    ++cmp;
	    break;
	}
    }
    if (*cmp==0) return 1;
    else return 0;
}



