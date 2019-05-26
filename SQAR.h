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
			Data::bytell_hash_map<ulong, impl::SQARFile*> Entries;
			ubyte* Data;

			void FormatHeader(ubyte* __restrict bytes);
			ulong* DecryptSectionList(ulong* sections);
			ubyte* DecryptData(uint hashLow, ulong dataOffset, ulong size);
		};
	}
}