#include <stdio.h>
#include <time.h>
#include <stdarg.h>

/* Время */
size_t rpl_strftime(char *s, size_t m, const char *f, const struct tm *t) { return 0; }
long timegm(struct tm *tm) { return 0; }

/* Системные заглушки */
int getuid(void) { return 0; }
int geteuid(void) { return 0; }
int getgid(void) { return 0; }
int getegid(void) { return 0; }
int getppid(void) { return 1; }
int getpgrp(void) { return 1; }

/* Функции, которые gawk не нашел в ядре */
void adjust_uint(void) {}
void out_of_range(void) {}
void format_nan_inf(void) {}
void format_args(void) {}
void do_printf(void *p) {}
void do_sprintf(void *p) {}
const char *deflibpath = "";
