#include <stdlib.h>
#include <string.h>

// Объявляем основную функцию gawk (из main.o)
extern int gawk_main(int argc, char **argv);

// Эта функция будет видна в FoxPro
__declspec(dllexport) int do_gawk(const char* command_line) {
    char* argv[64]; // Максимум 64 аргумента
    char* buf = strdup(command_line);
    int argc = 0;

    // Разбиваем строку по пробелам (простейший парсер)
    char* token = strtok(buf, " ");
    while (token != NULL && argc < 63) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }
    argv[argc] = NULL;

    // Вызываем оригинальный gawk
    int result = gawk_main(argc, argv);

    free(buf);
    return result;
}

// Заглушка, чтобы gawk не закрывал FoxPro при ошибках
void gawk_dll_exit(int code) {
    // Просто ничего не делаем, gawk сам вернется в do_gawk
}
