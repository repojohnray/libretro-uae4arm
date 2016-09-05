#include "uae_log.h"
#include <stdio.h>
#include <stdarg.h>

void UAECALL uae_log(const char *format, ...)
{
#ifdef DEBUG
  va_list ap;

  /* Determine required size */

  va_start(ap, format);
  vfprintf(stderr, format, ap);
  va_end(ap);
#else
	/* Redirect UAE_LOG_VA_ARGS_FULL to use write_log instead */
#define uae_log write_log
	UAE_LOG_VA_ARGS_FULL(format);
#undef uae_log
#endif
}
