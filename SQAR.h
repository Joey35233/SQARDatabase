#pragma once
#include "UDataStream.h"
#include "SQARFile.h"

class SQAR
{
public:
	SQAR(UDataStream&);
	SQARFile* GetEntry(uint i);
	ubyte* GetFile(uint i);
	uint GetFileCount();

private:
	uint Signature;
	uint Flags;
	uint FileCount;
	uint UnknownCount;
	uint BlockFileEnd;
	uint FirstFileOffset;
	uint Version;
	uint Unknown;
	SQARFile* Entries;
	ubyte* Data;

	void FormatHeader(ubyte* __restrict bytes);
	ulong* DecryptSectionList(ulong* sections);
	ubyte* DecryptData(uint hashLow, ulong dataOffset, ulong size);
};