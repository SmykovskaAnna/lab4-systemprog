#include <windows.h>
#include <iostream>
#include <fcntl.h>
#include <io.h>

void PrintStartupPrograms(HKEY rootKey, const std::wstring& subKey) {
    HKEY hKey;
    if (RegOpenKeyExW(rootKey, subKey.c_str(), 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        WCHAR valueName[256], valueData[1024];
        DWORD valueNameSize, valueDataSize, valueType;
        DWORD index = 0;

        while (true) {
            valueNameSize = 256;
            valueDataSize = sizeof(valueData);

            LONG result = RegEnumValueW(hKey, index++, valueName, &valueNameSize, NULL,
                &valueType, (LPBYTE)valueData, &valueDataSize);
            if (result == ERROR_NO_MORE_ITEMS) break;

            if (valueType == REG_SZ) {
                std::wcout << L"��'�: " << valueName << L" \n����: " << valueData << std::endl;
            }
        }
        RegCloseKey(hKey);
    }
}

int main() {
    if (_setmode(_fileno(stdout), _O_U16TEXT) == -1) {
        return 1;
    }

    std::wcout << L"������ ��� ������� �� ����� �� �������������� ����������� ��� ��� ������������ (HKLM):\n";
    PrintStartupPrograms(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run");

    std::wcout << L"\n������ ��� ������� �� ����� �� �������������� ����������� ��� ��������� ����������� (HKCU):\n";
    PrintStartupPrograms(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run");

    return 0;
}