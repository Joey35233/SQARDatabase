#include "pch.h"
#include "Hashing.h"

ska::bytell_hash_map<uint, const char*> FileExtensionMap;

ulong Hash(const char* string)
{
	return Hash(string, strlen(string));
}
ulong Hash(const char* string, uint length)
{
	const ulong seed0 = 0x9ae16a3b2f90404f;
	ulong seed1 = 0;
	for (int i = length - 1, j = 0; i >= 0 && j < sizeof(ulong); i--, j++)
	{
		((ubyte*)&seed1)[j] = string[i];
	}

	return CityHash64WithSeeds(string, length, seed0, seed1);
}

ulong HashName(const char* string)
{
	return HashName(string, strlen(string));
}
ulong HashName(const char* string, uint length)
{
	return Hash(string, length) | 0x4000000000000;
}

ulong HashFilePath(const char* string)
{
	return HashFilePath(string, strlen(string));
}
ulong HashFilePath(const char* string, uint length)
{
#ifdef _DEBUG
	// Test if string starts with "/Assets/"
	if (*(ulong*)string == 0x2f7374657373412f)
	{
		string += 8;
		length -= 8;
	}
	else
		DebugBreak();
#else
	string += 8;
	length -= 8;
#endif

	return Hash(string, length) & 0x3FFFFFFFFFFFF;
}

ulong HashExtension(const char* string)
{
	return HashExtension(string, strlen(string));
}
ulong HashExtension(const char* string, uint length)
{
	return Hash(string, length) & 0x1FFF;
}

ulong HashFilePathWithExtension(const char* string)
{
	return HashFilePathWithExtension(string, strlen(string));
}
ulong HashFilePathWithExtension(const char* string, uint length)
{
	char extBuffer[]{ '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };
	uint extLength = 0;
	{
		uint i = length - 1;
		while (string[i] != '.')
		{
			auto sChar = string[i];
			auto index = length - i - 1;
			extBuffer[7 - index] = sChar;

			i--;
		}
		*(ulong*)extBuffer >>= 8 * (9 - length + i);
		extLength = length - i - 1;
	}

	length -= extLength + 1;

	return HashFilePathWithExtension(string, length, extBuffer, extLength);
}

ulong HashFilePathWithExtension(const char* string, const char* extString)
{
	return HashFilePathWithExtension(string, strlen(string), extString, strlen(extString));
}
ulong HashFilePathWithExtension(const char* string, uint length, const char* extString, uint extLength)
{
	auto pathHash = HashFilePath(string, length);
	auto extHash = HashExtension(extString, extLength);

	return extHash << 51 | pathHash;
}