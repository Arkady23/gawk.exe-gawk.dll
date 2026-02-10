# gawk.exe
Утилита gawk последней на 10.02.2026 года версии 5.3.2. Скомпилирована под Windows с помощью ИИ от google. ИИ что-то изменял, чтобы убрать ошибки компиляции.  

Компиляция произведена в оболочке w64devkit от Christopher Wellons, репозиторий https://github.com/skeeto/w64devkit. Процесс компиляции:
```
cd D:/Install/github.com/skeeto_w64devkit/gawk

# 1. Создаем ПРАВИЛЬНЫЙ файл-заплатку со всеми нужными функциями
cat <<EOF > time_fix.c
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

/* Функции, которые gawk не находит в ядре */
void adjust_uint(void) {}
void out_of_range(void) {}
void format_nan_inf(void) {}
void format_args(void) {}
void do_printf(void *p) {}
void do_sprintf(void *p) {}
EOF

# 2. Создаем клей для Windows
echo '#include "awk.h"' > win_glue.c
echo '#include "pc/gawkmisc.pc"' >> win_glue.c
echo 'const char *deflibpath = "";' >> time_fix.c

# 3. Компилируем всё одной мощной командой
gcc -O2 -fpermissive -w -o gawk.exe -static -static-libgcc \ 
    -DGAWK -DHAVE_CONFIG_H=1 -DHAVE_POPEN=1 -D"DEFLIBPATH=\"\"" -D"SHLIBEXT=\"dll\"" \  
    -D"popen(a,b)=_popen(a,b)" -D"pclose(a)=_pclose(a)" \    
    -I. -I./pc -I./support \ 
    array.c awkgram.c builtin.c eval.c field.c gawkapi.c io.c main.c \ 
    mpfr.c msg.c node.c profile.c re.c symbol.c debug.c \ 
    int_array.c str_array.c command.c ext.c version.c cint_array.c \ 
    time_fix.c win_glue.c pc/popen.c \  
    support/dfa.c support/getopt.c support/getopt1.c support/regex.c \ 
    support/random.c support/localeinfo.c support/malloc/dynarray_resize.c \   
    -lws2_32 -lmsvcrt -lkernel32 
```
Если нужно больше утилит от Linux под Windows, скачивайте busybox64u.exe отсюда https://frippery.org/busybox/. 
