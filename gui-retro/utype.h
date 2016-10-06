/*
	modded for libretro-uae
*/

#ifndef HATARI_UTYPE_H
#define HATARI_UTYPE_H

#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef __LIBRETRO__
#include <ctype.h>

#ifdef PS3PORT
#include <sdk_version.h>
#include <cell.h>
#include <stdio.h>
#include <string.h>
#define	getcwd(a,b)	"/"
#include <unistd.h> //stat() is defined here
#define S_ISDIR(x) (x & CELL_FS_S_IFDIR)
#define F_OK 0
#define ftello ftell
#define chdir(a) 0
#define getenv(a)	"/dev_hdd0/HOMEBREW/ST/"
#define tmpfile() NULL
#endif
//#define PROG_NAME "Hatari devel (" __DATE__ ")"
#endif

#ifdef WIN32
#define PATHSEP '\\'
#else
#define PATHSEP '/'
#endif

#endif

