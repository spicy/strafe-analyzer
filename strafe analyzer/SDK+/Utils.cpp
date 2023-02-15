#include "utils.hpp"
c_utils g_utils;

uintptr_t c_utils::find_signature(const char* module, const char* signature)
{
	const char* pat = signature;
	DWORD firstmatch = 0;
	DWORD rangestart = (DWORD)GetModuleHandleA(module);
	MODULEINFO miModInfo;

	GetModuleInformation(GetCurrentProcess(), (HMODULE)rangestart, &miModInfo, sizeof(MODULEINFO));

	DWORD rangeEnd = rangestart + miModInfo.SizeOfImage;

	for (DWORD pCur = rangestart; pCur < rangeEnd; pCur++)
	{
		if (!*pat)
			return firstmatch;

		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == GET_BYTE(pat))
		{
			if (!firstmatch)
				firstmatch = pCur;

			if (!pat[2])
				return firstmatch;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else
				pat += 2;
		}
		else
		{
			pat = signature;
			firstmatch = 0;
		}
	}

	return 0u;
}

