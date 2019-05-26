#pragma once
#include "pch.h"
#include "IO.h"
#include "MD5.h"

namespace Fs
{
	namespace FPK::impl
	{
		class FPKString
		{
		public:
			FPKString();
			FPKString(UDataStream);
			ulong Length;
			char* String;
		};

		class FPKFile
		{
		public:
			FPKFile(UDataStream);
			ulong GetDataOffset();
			ulong GetDataSize();
			FPKString GetName();

		private:
			ulong DataOffset;
			ulong DataSize;
			FPKString Name;
			Data::MD5 DataHash;
		};

		class FPKReference
		{
		public:
			FPKReference(UDataStream);
		private:
			FPKString ReferenceName;
		};
	}
}