#ifndef _RETRO_GLUE_H_
#define _RETRO_GLUE_H_
#include "../libretro/libretro-mapper.h"

void InitOSGLU(void);
void UnInitOSGLU(void);

void enter_options(void);
void show_gui_message(char* msg);
void uae_resume (void);
void uae_pause (void);
char *filebrowser(const char *path_and_name);
void retro_key_up(int key);
void retro_key_down(int key);
void retro_mouse_but0(int down);
void retro_joy0(unsigned char joy0);
void retro_mouse_but1(int down);
void retro_mouse(int dx, int dy);
#endif
