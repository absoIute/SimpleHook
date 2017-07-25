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

BOOL Detour::WriteJMP(void * from, void * to, BOOL call, DWORD size) {
	DWORD bkup, oldprotect, offset = (DWORD)to - (DWORD)from - 5;
	if (!VirtualProtect(from, size, PAGE_EXECUTE_READWRITE, &bkup)) return FALSE;
	memset(from, 0xE9 - call, 1);
	memcpy((void *)((DWORD)from + 1), &offset, 4);
	for (int i = 0; i < size - 5; i++)
		memset((void *)((DWORD)from + 6 + i), 0x90, 1);
	if (!VirtualProtect(from, size, bkup, &oldprotect)) return FALSE;
	return TRUE;
}

BOOL Detour::WriteNOP(void * at, DWORD size) {
	DWORD bkup, oldprotect;
	if (!VirtualProtect(at, 5, PAGE_EXECUTE_READWRITE, &bkup)) return FALSE;
	for (int i = 0; i < size; i++)
		memset((void *)((DWORD)at + i), 0x90, 1);
	if (!VirtualProtect(at, 5, bkup, &oldprotect)) return FALSE;
	return TRUE;
}

BOOL Detour::TrampolineSetup(void * placeholder_function, LPCVOID backup, DWORD size, DWORD exit_offset, BOOL call) {
	if (backup) {
		DWORD bkup, oldprotect;
		if (!VirtualProtect(placeholder_function, 0x1000, PAGE_EXECUTE_READWRITE, &bkup)) return FALSE;
		memcpy(placeholder_function, &backup, size);
		if (!VirtualProtect(placeholder_function, 0x1000, bkup, &oldprotect)) return FALSE;
	}
	return WriteJMP((void *)((DWORD)placeholder_function + exit_offset), (void *)((DWORD)from_address + 5), call, 5);
}

BOOL Detour::Create(DWORD size /* amount to write */, LPVOID backup, BOOL call /* set to true if a call should be placed instead of a jmp */) {
	if (backup) ReadProcessMemory(GetCurrentProcess(), from_address, backup, size, NULL);
	hooked = WriteJMP(from_address, to_address, call, size);
	return hooked;
}

BOOL Detour::Remove(DWORD size, LPCVOID restore) {
	if (restore) {
		DWORD backup, oldprotect;
		if (!VirtualProtect(from_address, size, PAGE_EXECUTE_READWRITE, &backup)) return FALSE;
		if (!WriteProcessMemory(GetCurrentProcess(), from_address, restore, size, NULL)) return FALSE;
		if (!VirtualProtect(from_address, size, backup, &oldprotect)) return FALSE;
		return TRUE;
	}
	return WriteNOP(from_address, size);
}
