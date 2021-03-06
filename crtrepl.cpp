#include "crtrepl.h"

// Copy a string and return its length
size_t wcscpylen_s(wchar_t *strDestination, size_t numberOfElements, const wchar_t *strSource)
{
	size_t count = 0;
	while (((*strDestination++ = *strSource++) != 0) && (--numberOfElements > 0))
		++count;
	return count;
}

// Scan a string for the last occurrence of a character.
// Return index of the next position or 0 if no such character.
size_t wcsrchr_pos(const wchar_t* str, size_t start_pos, wchar_t c)
{
	size_t idx = start_pos;
	while (idx > 0)
	{
		if (str[--idx] == c)
			return idx + 1;
	}
	return 0;
}

/*
// [lib] Searches for the first occurrence of any of 'control' characters in a string
size_t wcscspn(const wchar_t* string, const wchar_t* control)
{
	const wchar_t* str = string;
	const wchar_t* wcset;

	// 1st char in control string stops search
	while (*str)
	{
		for (wcset = control; *wcset; ++wcset)
		{
			if (*wcset == *str)
			{
				return (size_t)(str - string);
			}
		}
		++str;
	}
	return (size_t)(str - string);
}

// [lib] Copies bytes between buffers
// errno_t memcpy_s(void* dest, size_t numberOfBytes, const void* src, size_t count)
// {
// 	if (count > numberOfBytes)
// 		count = numberOfBytes;
// 	while (count--)
// 	{
// 		*(unsigned char*)dest = *(unsigned char*)src;
// 		dest = (unsigned char*)dest + 1;
// 		src = (unsigned char*)src + 1;
// 	}
// 	return 0;
// }

// [lib] Compare the specified number of characters of two strings
int wcsncmp(const wchar_t* string1, const wchar_t* string2, size_t count)
{
	if (!count)
		return 0;
	while ((--count) && *string1 && (*string1 == *string2))
	{
		++string1;
		++string2;
	}

	return (int)(*string1 - *string2);
}

#define __ascii_towlower(c) ( (((c) >= L'A') && ((c) <= L'Z')) ? ((c) | 0x20) : (c) )

// [lib] Compare the specified number of characters of two strings, case ignored
int _wcsnicmp(const wchar_t* string1, const wchar_t* string2, size_t count)
{
	if (!count)
		return 0;

	wchar_t f, l;

	do {
		f = __ascii_towlower(*string1);
		l = __ascii_towlower(*string2);
		++string1;
		++string2;
	} while ( (--count) && f && (f == l) );

	return (int)(f - l);
}
*/

/*
// Concatenates the two strings and one argument (limited swprintf replacement)
template <>
int swprintf_s(wchar_t* buffer, size_t sizeOfBuffer, const wchar_t* str1, wchar_t* arg1, const wchar_t* str2)
{
	size_t len = wcscpylen_s(buffer, sizeOfBuffer, str1);
	len += wcscpylen_s(buffer + len, sizeOfBuffer - len, arg1);
	len += wcscpylen_s(buffer + len, sizeOfBuffer - len, str2);
	return (int)len;
}

template <>
int swprintf_s(wchar_t* buffer, size_t sizeOfBuffer, const wchar_t* str1, size_t arg1, const wchar_t* str2)
{
	wchar_t val[21];  // Maximum length of 64-bit value is 20 characters
	wchar_t* res = val + 20;
	*--res = L'\0';
	if (arg1 == 0)
		*--res = L'0';
	else
		do
		{
			*--res = L'0' + (arg1 % 10L);
			arg1 /= 10L;
		} while (arg1 != 0);
 	return swprintf_s(buffer, sizeOfBuffer, str1, res, str2);
}

template <>
int swprintf_s(wchar_t* buffer, size_t sizeOfBuffer, const wchar_t* str1, ULONG arg1, const wchar_t* str2)
{
	return swprintf_s(buffer, sizeOfBuffer, str1, (size_t)arg1, str2);
}

// Special version for swprintf_s<ULONG> with hex format instead of decimal
int swprintf_s_hex(wchar_t* buffer, size_t sizeOfBuffer, const wchar_t* str1, ULONG arg1, const wchar_t* str2)
{
	wchar_t val[17] = L"0000000000000000";    // Maximum length of 64-bit value is 16 characters
	wchar_t* res = val + 16;
	if (arg1 == 0)
		res -= 8;
	else
	{
		do
		{
			BYTE d = arg1 % 16L;
			*--res = ((d < 10) ? (L'0' + d) : (L'a' - 10 + d));
			arg1 /= 16L;
		} while (arg1 != 0);
		res = val + ((res - val) / 8) * 8;
	}
 	return swprintf_s(buffer, sizeOfBuffer, str1, res, str2);
}
*/
