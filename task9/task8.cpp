#include <windows.h>
#include <iostream>

int main() {
    system("reg export \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\" C:\\Users\\Anna\\Desktop\\Backup.reg /y");
    return 0;
}