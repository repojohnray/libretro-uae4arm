 /* 
  * UAE - The Un*x Amiga Emulator
  * 
  * Support for the Mute sound system.
  * 
  * Copyright 1997 Bernd Schmidt
  */

#ifndef OSDEP_SOUND_H
#define OSDEP_SOUND_H
#define SOUNDSTUFF 1
//#include "driveclick.h"
extern int retro_renderSound(short* samples, int sampleCount);

#define sndbuffer paula_sndbuffer
#define sndbufpt paula_sndbufpt
#define sndbufsize paula_sndbufsize

extern uae_u16 paula_sndbuffer[];
extern uae_u16 *paula_sndbufpt;
extern int paula_sndbufsize;


extern int soundcheck;

static __inline__ void check_sound_buffers (void)
{
    unsigned int size = (char *)sndbufpt - (char *)sndbuffer;

    if (size >= sndbufsize) {
	//LOG_MSG2("render sound %i   ",soundcheck++ );
#ifdef DRIVESOUND
	driveclick_mix ((uae_s16*)sndbuffer, sndbufsize >> 1,currprefs.dfxclickchannelmask);
#endif	
	retro_renderSound((short*) sndbuffer, sndbufsize >> 1);	
	sndbufpt = sndbuffer;
    }
}
STATIC_INLINE void set_sound_buffers (void)
{
}

STATIC_INLINE void clear_sound_buffers (void)
{
	memset (sndbuffer, 0, sndbufsize);
	sndbufpt = sndbuffer;
}

#undef AUDIO_NAME
#define AUDIO_NAME "retroaudio"


#define PUT_SOUND_BYTE(b) do { *(uae_u8 *)sndbufpt = b; sndbufpt = (uae_u16 *)(((uae_u8 *)sndbufpt) + 1); } while (0)
#define PUT_SOUND_WORD(b) do { *(uae_u16 *)sndbufpt = b; sndbufpt = (uae_u16 *)(((uae_u8 *)sndbufpt) + 2); } while (0)
//#define PUT_SOUND_WORD(b) PUT_SOUND_BYTE(b << 8); PUT_SOUND_BYTE(b >> 8)

#define PUT_SOUND_WORD_LEFT(b) PUT_SOUND_WORD(b)
#define PUT_SOUND_WORD_RIGHT(b) PUT_SOUND_WORD(b)
#define PUT_SOUND_WORD_MONO(b) PUT_SOUND_WORD_LEFT(b)

#define PUT_SOUND_WORD_LEFT2(b) PUT_SOUND_WORD(b)
#define PUT_SOUND_WORD_RIGHT2(b) PUT_SOUND_WORD(b)

#define SOUND16_BASE_VAL 0
#define SOUND8_BASE_VAL 128

#define DMULTIPLICATION_PROFITABLE
#define DEFAULT_SOUND_MAXB 8192
#define DEFAULT_SOUND_MINB 8192
#define DEFAULT_SOUND_BITS 16
#define DEFAULT_SOUND_FREQ 22050

#define HAVE_STEREO_SUPPORT

#define DEFAULT_SOUND_LATENCY 50


#endif
