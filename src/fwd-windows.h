#ifndef FWD_WINDOWS_H
#define FWD_WINDOWS_H
using dword = std::conditional_t<sizeof(long) == 4, unsigned long, unsigned>;
extern "C" __declspec(dllimport) int __stdcall WriteConsoleW(
    void *, const void *, dword, dword *, void *);

#endif // FWD_WINDOWS_H
