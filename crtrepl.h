#pragma once

// 
// 
// // Allocation replacement functions
// extern HANDLE ProcessHeap;
// 
// __declspec(restrict) __declspec(noalias) __forceinline void* __cdecl malloc(size_t n)
// {
//     return HeapAlloc(ProcessHeap, 0, n);
// }
// 
// __declspec(restrict) __declspec(noalias) __forceinline void* __cdecl realloc(void* p, size_t n)
// {
//     if (p == NULL)
// 		return malloc(n);
//     return HeapReAlloc(ProcessHeap, 0, p, n);
// }
// 
// __declspec(noalias) __forceinline void __cdecl free(void* p)
// {
//     if (p == NULL)
// 		return;
//     HeapFree(ProcessHeap, 0, p);
// }
// 
// __forceinline void* __cdecl operator new(size_t n)
// {
//     return HeapAlloc(ProcessHeap, 0, n);
// }
// 
// __forceinline void* __cdecl operator new[](size_t n)
// {
//     return HeapAlloc(ProcessHeap, 0, n);
// }
// 
// __forceinline void __cdecl operator delete(void* p)
// {
//     if (p == NULL)
// 		return;
//     HeapFree(ProcessHeap, 0, p);
// }
// 
// __forceinline void __cdecl operator delete[](void* p)
// {
//     if (p == NULL)
// 		return;
//     HeapFree(ProcessHeap, 0, p);
// }

// Copy a string and return its length
size_t wcscpylen_s(wchar_t *strDestination, size_t numberOfElements, const wchar_t *strSource);

// Scan a string for the last occurrence of a character.
// Return index of the next position or 0 if no such character.
size_t wcsrchr_pos(const wchar_t* str, size_t start_pos, wchar_t c);

/*
// [lib] Searches for the first occurrence of any of 'control' characters in a string
size_t wcscspn(const wchar_t* string, const wchar_t* control);

// [lib] Copies bytes between buffers
//errno_t memcpy_s(void* dest, size_t numberOfBytes, const void* src, size_t count);

// [lib] Compare the specified number of characters of two strings
int wcsncmp(const wchar_t* string1, const wchar_t* string2, size_t count);

// [lib] Compare the specified number of characters of two strings, case ignored
int _wcsnicmp(const wchar_t* string1, const wchar_t* string2, size_t count);

// Concatenates the two strings and one argument (limited swprintf replacement)
template <class T>
int swprintf_s(wchar_t* buffer, size_t sizeOfBuffer, const wchar_t* str1, T arg1, const wchar_t* str2);

// Special version for swprintf_s<ULONG> with hex format instead of decimal
int swprintf_s_hex(wchar_t* buffer, size_t sizeOfBuffer, const wchar_t* str1, ULONG arg1, const wchar_t* str2);
*/
