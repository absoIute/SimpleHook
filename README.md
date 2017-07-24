# SimpleHook
A C++ library for hooking/detouring functions
## Basic Usage
You'll need a function to detour and a function to detour to, either can just be address to use.
Creation:
```cpp
#include "SimpleHook.hpp"

void MyFunction(); // function to detour
void MyHook(); // function to detour to

int main() {
    Detour MyDetour(MyFunction, MyHook);
    MyDetour.Create();
}
```
Note: alternatively you could use `Detour::SetFrom(void * value)` & `Detour::SetTo(void * value)` to set the values.

If needed, `Detour::Create()` will place NOPs after the detour if only part of an opcode is overwritten, this is done by setting the first argument of the function to the chosen size (size = 5 + number of NOPs to be placed, anything 5 or less will result in none being placed down) `Detour::Create(size)`.
You can also choose to add place a call instead of a jmp with the third argument of the function, `Detour::Create(size, NULL, TRUE)`.
To check the success of a detour creation call `Detour::Hooked()` or check the return value of `Detour::Create()`.
To remove a detour simply add `MyDetour.Remove()` to your program, this will just NOP the detour (unless a backup is used).
## Backups & Restoration
Another feature of the SimpleHook library is that you can restore overwritten opcode.
A backup is performed like this:
```cpp
#include "SimpleHook.hpp"

void MyFunction(); // function to detour
void MyHook(); // function to detour to

int main() {
    int BackupSize = 5; // amount of bytes to backup
    char MyBackup[BackupSize]; // backup will be stored here
    
    Detour MyDetour(MyFunction, MyHook);
    MyDetour.Create(BackupSize, &MyBackup); // creating detour & backing up opcode
    Sleep(5000); // wait 5 seconds
    MyDetour.Remove(BackupSize, &MyBackup); // removing detour & restoring backup
}
```
## Future (to add)
- Trampolines
- ~~Backups and restoration after detour removal~~
