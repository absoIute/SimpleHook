#pragma once

#include <Windows.h>

class Detour {
private:
	void * from_address;
	void * to_address;
	BOOL hooked;
	
	BOOL WriteJMP(void * from, void * to, BOOL call, DWORD size);
	BOOL WriteNOP(void * at, DWORD size);
public:
	Detour();
	Detour(void * from, void * to);
	~Detour() { /* do nothing */ }

	void SetFrom(void * value);
	void SetTo(void * value);
	void * GetFrom();
	void * GetTo();
	BOOL Hooked();
	
	BOOL TrampolineSetup(void * placeholder_function, LPCVOID backup, DWORD size, DWORD exit_offset, BOOL call = FALSE);

	BOOL Create(DWORD size = 5, LPVOID backup = NULL, BOOL call = FALSE);
	BOOL Remove(DWORD size = 5, LPCVOID restore = NULL);
};
