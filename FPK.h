#pragma once
#include "pch.h"
#include "IO.h"
#include "FPKEntry.h"

class FPK
{
public:
	FPK(UDataStream&);
	uint GetFileCount();
	uint GetReferenceCount();
	NamedFileBlob* GetFiles();

private:
	ubyte* Data;
	uint FileCount;
	uint ReferenceCount;
	FPKFile* Files;
	FPKReference* References;
};