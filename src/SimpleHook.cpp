#include "SimpleHook.hpp"

Detour::Detour() {
	hooked = FALSE;
}

Detour::Detour(void * from, void * to) {
	from_address = from;
	to_address = to;
	hooked = FALSE;
}

void Detour::SetFrom(void * value) {
	from_address = value;
}

void Detour::SetTo(void * value) {
	to_address = value;
}

void * Detour::GetFrom() {
	return from_address;
}

void * Detour::GetTo() {
	return to_address;
}

BOOL Detour::Hooked() {
	return hooked;
}

BOOL Detour::Create(DWORD size /* amount to write */, BOOL call /* set to true if a call should be placed instead of a jmp */) {
	DWORD backup, oldprotect, offset = (DWORD)to_address - (DWORD)from_address - 5;
	if (!VirtualProtect(from_address, size, PAGE_EXECUTE_READWRITE, &backup)) return FALSE;
	memset(from_address, 0xE9 - call, 1);
	memcpy((void *)((DWORD)from_address + 1), &offset, 4);
	for (int i = 0; i < size - 5; i++)
		memset((void *)((DWORD)from_address + 6 + i), 0x90, 1);
	if (!VirtualProtect(from_address, size, backup, &oldprotect)) return FALSE;
	return TRUE;
}

BOOL Detour::Remove() {
	DWORD backup, oldprotect;
	if (!VirtualProtect(from_address, 5, PAGE_EXECUTE_READWRITE, &backup)) return FALSE;
	if (!WriteProcessMemory(GetCurrentProcess(), (PVOID)from_address, "\x90\x90\x90\x90\x90", 5, NULL))
		if (!VirtualProtect(from_address, 5, backup, &oldprotect)) return FALSE;
	return TRUE;
}
