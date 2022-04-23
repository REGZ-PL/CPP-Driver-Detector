#pragma once
 
/*
	Bliblioteka driver detector
	Autor: Regz.pl
 
	Przykład:
		while (true)
		{
			if (driver_detector::check())
				MessageBox(NULL, "Znaleziono sterownik","Błąd", MB_OK);
 
			Sleep(15);
		}
 
	Test:
		Uruchom Cheat Engine w trybie kernel mode a funkcja check zwróci prawdę.
*/
 
#include <windows.h>
#include <psapi.h>
#include <tchar.h>
#include <stdio.h>
#include <vector>
 
namespace driver_detector {
	std::vector<const char*> blacklist_vector = { "dbk32.sys", "dbk64.sys" };
 
	LPVOID drivers_list[1024];
	TCHAR driver_name[1024];
	DWORD lpImageBaseBytes;
 
	int check()
	{
		if (EnumDeviceDrivers(drivers_list, sizeof(drivers_list), &lpImageBaseBytes) && lpImageBaseBytes < sizeof(drivers_list))
		{
			int drivers_count = lpImageBaseBytes / sizeof(drivers_list[0]);
 
			for (int i = 0; i < drivers_count; i++)
			{
				if (GetDeviceDriverBaseName(drivers_list[i], driver_name, sizeof(driver_name) / sizeof(driver_name[0])))
				{
					for (auto blacklist_name : blacklist_vector)
					{
						if (_tcscmp(driver_name, blacklist_name) == 0)
						{
							return 1;
						}
					}
 
				}
			}
		}
 
		return 0;
	}
}
