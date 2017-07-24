# SimpleHook
A C++ library for hooking/detouring functions
## Basic Usage
You'll need a function to detour and a function to detour to, either can just be address to use.

A basic detour looks like:
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
This code will backup 5 bytes in the `MyBackup` variable, create the detour, wait 5 seconds then remove the detour and restore the backup.
A value of FALSE will be returned if either the creation of removal fails.

Since the backups are restored exactly as the were originally, you may need to make modifications to jumps, calls, etc..
## Future (to add)
- ~~Trampolines~~
- ~~Backups and restoration after detour removal~~
- Update README
- Examples
## License
MIT License

Copyright (c) 2017 Absolute (Ben .S)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
