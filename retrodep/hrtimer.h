/*
 * E-UAE - The portable Amiga Emulator
 *
 * Generic high-resolution timer support.
 *
 * (c) 2005 Richard Drummond
 */

#ifndef EUAE_OSDEP_HRTIMER_H
#define EUAE_OSDEP_HRTIMER_H

#ifdef __CELLOS_LV2__
#include "sys/sys_time.h"
#include "sys/timer.h"
#define usleep  sys_timer_usleep

static INLINE void gettimeofday (struct timeval *tv, void *blah)
{
    int64_t time = sys_time_get_system_time();

    tv->tv_sec  = time / 1000000;
    tv->tv_usec = time - (tv->tv_sec * 1000000);  // implicit rounding will take care of this for us
}

#else
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#endif

#ifndef LIBRETRO_UAE4ARM
#include "machdep/rpt.h"
#endif


STATIC_INLINE frame_time_t osdep_gethrtime (void)
{
#ifndef _ANDROID_

   struct timeval tv;
   gettimeofday (&tv, NULL);
   return tv.tv_sec*1000000 + tv.tv_usec;

#else
#define osd_ticks_t uae_s64
   struct timeval    tp;
   static osd_ticks_t start_sec1 = 0;

   gettimeofday(&tp, NULL);
   if (start_sec1==0)
      start_sec1 = tp.tv_sec;
   return (tp.tv_sec - start_sec1) * (osd_ticks_t) 1000000 + tp.tv_usec;
#endif
}

STATIC_INLINE frame_time_t osdep_gethrtimebase (void)
{
    return 1000000;
}

STATIC_INLINE void osdep_inithrtimer (void)
{
}
#endif
