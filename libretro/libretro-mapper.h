#ifndef _RETRO_HMAPPER_H_
#define _RETRO_HMAPPER_H_
#include "../retrodep/retroglue.h"

#define EMULATOR_DEF_WIDTH 640
#define EMULATOR_DEF_HEIGHT 400
#define EMULATOR_MAX_WIDTH 1024
#define EMULATOR_MAX_HEIGHT 1024

#if EMULATOR_DEF_WIDTH < 0 || EMULATOR_DEF_WIDTH > EMULATOR_MAX_WIDTH || EMULATOR_DEF_HEIGHT < 0 || EMULATOR_DEF_HEIGHT > EMULATOR_MAX_HEIGHT
#error EMULATOR_DEF_WIDTH || EMULATOR_DEF_HEIGHT
#endif

void Screen_SetFullUpdate(void);
void gui_poll_events(void);
void retro_audio_cb( short l, short r);
void pause_select(void);
int fsel_file_exists(char * path);
void loadthumb(char *name,int x,int y);
void dothumb(char *name,int sw,int sh,int tw,int th);
int fsel_file_create(char * path);
void clean_led_area(void);
int update_input_gui(void);
void retro_shutdown_uae(void);
#endif
