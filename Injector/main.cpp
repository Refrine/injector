#include <Windows.h>
#include <iostream>
#include <string>
// Функция для загрузки DLL-файла
HMODULE LoadDll(const std::wstring& dllPath) {
    HMODULE hDll = LoadLibraryW(dllPath.c_str());
    if (!hDll) {
        std::cerr << "Ошибка загрузки DLL: " << GetLastError() << std::endl;
        return nullptr;
    }
    return hDll;
}

// Функция для получения функции из DLL-файла
FARPROC GetDllFunction(HMODULE hDll, const std::string& functionName) {
    FARPROC functionProc = GetProcAddress(hDll, functionName.c_str());
    if (!functionProc) {
        std::cerr << "Ошибка получения функции из DLL: " << GetLastError() << std::endl;
        return nullptr;
    }
    return functionProc;
}

// Функция для вызова функции из DLL-файла
void CallDllFunction(FARPROC functionProc, int a, int b) {
    // Приведение типа функции к типу, который она представляет
    int (*pfn)(int, int) = reinterpret_cast<int (*)(int, int)>(functionProc);

    // Вызов функции
    int result = pfn(a, b);

    // Вывод результата
    std::cout << "Результат: " << result << std::endl;
}

int main() {
    // Путь к DLL-файлу
    std::wstring dllPath = L"";
    
    // Загрузка DLL-файла
    HMODULE hDll = LoadDll(dllPath);
    if (!hDll) {
        return 1;
    }
   
    // Получение функции из DLL-файла
    FARPROC functionProc = GetDllFunction(hDll, "MyFunction");
    if (!functionProc) {
        return 1;
    }

    // Вызов функции из DLL-файла
    CallDllFunction(functionProc, 5, 10);

    // Освобождение DLL-файла
    FreeLibrary(hDll);

    return 0;
}
