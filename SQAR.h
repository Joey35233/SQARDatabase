#pragma once
#include "SqarFile.h"
#include "IO.h"
#include "bytell_hash_map.h"

namespace Fs
{
	namespace Sqar
	{
		struct SqarFileInformation
		{
			uint offset;
			uint size;
			ulong hash;
		};

		class Sqar
		{
		public:
			Sqar(UDataStream);
			~Sqar();

			uint GetFileCount();
			FileBlob GetEntry(ulong);
			void InitFileList();
			void PopulateFileInfo(SqarFileInformation*);

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
			ulong GetSectionEntry(uint);
			ulong* DecryptSectionList(ulong* sections);
			ubyte* DecryptData(uint hashLow, ulong dataOffset, ulong size);
		};
	}
}