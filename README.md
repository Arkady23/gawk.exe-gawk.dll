# gawk.exe and gawk.dll
## Пример использования gawk.dll на C#
Еще не разобрался, что тут ИИ понаписал:
```
public class GawkRunner {
    [DllImport("kernel32.dll", SetLastError = true)]
    private static extern IntPtr LoadLibrary(string dllToLoad);

    [DllImport("kernel32.dll")]
    private static extern bool FreeLibrary(IntPtr hModule);

    [DllImport("kernel32.dll")]
    private static extern IntPtr GetProcAddress(IntPtr hModule, string procedureName);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    private delegate int GawkMain(int argc, string[] argv);

    public void ExecuteGawk(string[] args) {
        IntPtr pDll = LoadLibrary("gawk.dll");
        if (pDll == IntPtr.Zero) return;

        IntPtr pAddressOfFunctionToCall = GetProcAddress(pDll, "gawk_main");
        GawkMain gawkMain = (GawkMain)Marshal.GetDelegateForFunctionPointer(
            pAddressOfFunctionToCall, typeof(GawkMain));


// [DllImport("gawk.dll", EntryPoint = "do_gawk", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
// public static extern int do_gawk(string commandLine);

// Использование в C#:
int result = do_gawk("gawk -f script.awk input.txt");



        // ВЫГРУЖАЕМ DLL, чтобы очистить память и сбросить статические переменные
        FreeLibrary(pDll);
    }
}
```
## Пример использования gawk32.dll/gawk.dll в VFP9/VFPA
```
* 1. Подготовка данных в Unicode (UTF-8)
lcInput = "текст для обработки"
STRTOFILE(STRCONV(lcInput, 9), "in.txt") && 9 = ANSI to UTF-8

* 2. Объявление функции (обратите внимание на имя с подчеркиванием)
* DECLARE INTEGER do_gawk IN gawk.dll STRING cCmd   && Вариант 64 бит
DECLARE INTEGER _do_gawk IN gawk32.dll STRING cCmd

* 3. Запуск (все параметры в одной строке)
* Используем -v BINMODE=3 для корректной работы с UTF-8 в файлах
* -v BINMODE=3: Это критически важно для Windows. Это заставляет Gawk читать
* и писать файлы "как есть", не ломая символы переноса строк и не пытаясь
* конвертировать их в системную кодировку. Сам .awk файл в кодировке UTF-8.
lcCmd = [gawk -v BINMODE=3 -f script.awk in.txt]
* lnRes = do_gawk(lcCmd)   && Вариант 64 бит
lnRes = _do_gawk(lcCmd)

IF lnRes = 0
    * 4. Читаем результат (если скрипт писал в файл или через перенаправление)
    lcOut = STRCONV(FILETOSTR("out.txt"), 11)   && 11 = UTF-8 to ANSI
    ? lcOut
ENDIF

* Сброс DLL для очистки памяти
CLEAR DLLS "gawk32.dll"
```
