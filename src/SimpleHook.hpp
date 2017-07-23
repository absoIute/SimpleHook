#pragma once

#include <Windows.h>

class Detour {
private:
	void * from_address;
	void * to_address;
	BOOL hooked;
public:
	Detour();
	Detour(void * from, void * to);
	~Detour() { /* do nothing */ }

	void SetFrom(void * value);
	void SetTo(void * value);
	void * GetFrom();
	void * GetTo();
	BOOL Hooked();

	BOOL Create(DWORD size = 5, BOOL call = FALSE);
	BOOL Remove();
};
