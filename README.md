# gawk.exe
Утилита gawk последней на 10.02.2026 года версии 5.3.2. Скомпилирована под Windows с помощью ИИ от google. Текст правок ИИ не сохранил. ИИ что-то изменял, чтобы убрать ошибки компиляции.  

Компиляция произведена в оболочке w64devkit от Christopher Wellons, репозиторий https://github.com/skeeto/w64devkit. Команда на компиляцию:
```
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
