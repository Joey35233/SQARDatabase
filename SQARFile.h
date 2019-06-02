#pragma once
#include "pch.h"
#include "IO.h"
#include "MD5.h"

namespace Fs
{
	namespace SQAR::impl
	{
		static constexpr uint DecryptionTable[]
		{
			0xBB8ADEDB,
			0x65229958,
			0x08453206,
			0x88121302,
			0x4C344955,
			0x2C02F10C,
			0x4887F823,
			0xF3818583
		};

		class SQARFile
		{
		public:
			SQARFile(UDataStream);
			ulong GetUncompressedSize();
			ulong GetCompressedSize();
			ulong GetDataOffset();
			ulong GetHash();
			bool IsCompressed();
			bool IsEncrypted();

		private:
			ulong Hash;
			uint Key;
			uint Encryption;
			bool MetaFlag;
			uint Version;
			uint UncompressedSize;
			uint CompressedSize;
			ulong DataOffset;
			Data::MD5 DataHash;
		};
	}
}