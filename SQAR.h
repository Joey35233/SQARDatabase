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
			SQAR(UDataStream);

			uint GetFileCount();
			FileBlob GetEntry(ulong);

		private:
			uint Signature;
			uint Flags;
			uint FileCount;
			uint UnknownCount;
			uint BlockFileEnd;
			uint FirstFileOffset;
			uint Version;
			uint Unknown;
			ubyte* Data;
			Data::bytell_hash_map<ulong, ulong> Entries;

			void InitHeader(ubyte*);
			void InitFileList(ubyte*);
			ulong* DecryptSectionList(ulong* sections);
			ubyte* DecryptData(uint hashLow, ulong dataOffset, ulong size);
		};
	}
}