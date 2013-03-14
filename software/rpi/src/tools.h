#ifndef TOOLS_H_
#define TOOLS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <linux/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <libgen.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <sys/stat.h>
#include <unistd.h>

//#include "defs.h"

#define __MSG(...) msg(0, __LINE__, __FILE__, stdout, __VA_ARGS__, NULL)
#define __WNG(...) msg(0, __LINE__, __FILE__, stderr, __VA_ARGS__, NULL)
#define __DIE(...) msg(1, __LINE__, __FILE__, stderr, __VA_ARGS__, NULL)

int file_exists(const char *f);
void msg(int die, int line, const char *srcfile, FILE *fp,
		const char *fmt, ...);

#endif

