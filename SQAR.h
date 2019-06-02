#pragma once
#include "SQARFile.h"
#include "IO.h"
#include "bytell_hash_map.h"

namespace Fs
{
	namespace SQAR
	{
		struct SQARFileInformation
		{
			uint offset;
			uint size;
			ulong hash;
		};

		class SQAR
		{
		public:
			SQAR(UDataStream);
			~SQAR();

			uint GetFileCount();
			FileBlob GetEntry(ulong);
			void InitFileList();
			void PopulateFileInfo(SQARFileInformation*);

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