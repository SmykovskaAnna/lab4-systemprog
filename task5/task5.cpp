#include <windows.h>
#include <iostream>
#include <fcntl.h>
#include <io.h>

void AddToStartup(const std::wstring& name, const std::wstring& path) {
    HKEY hKey;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        RegSetValueExW(hKey, name.c_str(), 0, REG_SZ, (const BYTE*)path.c_str(), (path.size() + 1) * sizeof(wchar_t));
        RegCloseKey(hKey);
        std::wcout << L"Додано " << name << L" до автозавантаження програм.\n";
    }
}

int main() {
    if (_setmode(_fileno(stdout), _O_U16TEXT) == -1) {
        return 1;
    }

    std::wstring appName = L"WinWord";
    std::wstring appPath = L"\"C:\\Program Files\\Microsoft Office\\root\\Office16\\WINWORD.EXE\"";

    AddToStartup(appName, appPath);

    return 0;
}