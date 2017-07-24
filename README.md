# SimpleHook
A C++ library for hooking/detouring functions
## Usage
You'll need a function to detour and a function to detour to, either can just be address to use.
Creation:
Note: alternatively you could use `Detour::SetFrom(void * value)` & `Detour::SetTo(void * value)` to set the values.
```
Detour MyDetour(MyFunction, MyHook);
MyDetour.Create();
```
If needed, `Detour::Create()` will place NOPs after the detour if only part of an opcode is overwritten, this is done by setting the first argument of the function to the chosen size (size = 5 + number of NOPs to be placed, anything 5 or less will result in none being placed down) `Detour::Create(size)`.
You can also choose to add place a call instead of a jmp with the second argument of the function, `Detour::Create(size, TRUE)`.
To check the success of a detour creation call `Detour::Hooked()` or check the return value of `Detour::Create()`.
To remove a detour simply add `MyDetour.Remove()` to your program, this will just NOP the detour.
## Future (to add)
- Trampolines
- Backups and restoration after detour removal
