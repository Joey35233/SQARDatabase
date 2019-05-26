#pragma once
#include "SQARFile.h"
#include "IO.h"
#include "bytell_hash_map.h"

namespace Fs
{
	namespace SQAR
	{
		class SQAR
		{
		public:
			SQAR(UDataStream&);
			FileBlob GetEntry(ulong hash);
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
			uint BlockShiftCount;
			ubyte* Data;
			Data::bytell_hash_map<ulong, ulong> Entries;

			void FormatHeader(ubyte* __restrict bytes);
			void DecryptSectionList(ulong* sections);
			ubyte* DecryptData(uint hashLow, ulong dataOffset, ulong size);
		};
	}
}