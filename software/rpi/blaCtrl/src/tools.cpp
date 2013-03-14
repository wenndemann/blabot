#include "tools.h"

static char *
timestamp(int line, char *srcfile)
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	char *ts = (char*) malloc(64 * sizeof(char));
	int n = sprintf(ts, "(%.2d:%.2d:%.2d %s:%i)", timeinfo->tm_hour,
					timeinfo->tm_min, timeinfo->tm_sec, srcfile, line);
	if (n > 64)
	{
		ts = (char*) realloc(ts, n);
		n = sprintf(ts, "(%.2d:%.2d:%.2d %s:%i)", timeinfo->tm_hour,
					timeinfo->tm_min, timeinfo->tm_sec, srcfile, line);
	}
	if (n == -1)
	{
		fprintf(stderr, "*** tools.c: %d: Fatal error ***\n", __LINE__);
		exit(EXIT_FAILURE);
	}

	return ts;
}

int
file_exists(const char *f)
{
	struct stat st;
	if (!stat(f, &st))
		return S_ISREG(st.st_mode);
	return -1;
}

void
msg(int die, int line, const char *srcfile, FILE *fp, const char *fmt, ...)
{
	char *bn = strdup(srcfile);
	bn = basename(bn);
	char *ts = timestamp(line, bn);
	fprintf(fp, "%s ", ts);
	free(ts);

	va_list ap;
	va_start(ap, fmt);
	vfprintf(fp, fmt, ap);
	va_end(ap);

	if (die)
		exit(EXIT_FAILURE);
}

