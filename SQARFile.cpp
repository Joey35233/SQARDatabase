#include "pch.h"
#include "SQARFile.h"

namespace Fs::SQAR::impl
{
	static constexpr ulong HashingMetaFlag = 0x4000000000000;

	SQARFile::SQARFile(UDataStream& stream)
	{
		// Hash - 64
		// UCSi - 32
		// CMSi - 32
		// MD5  - 128
		{
			// Can't compress this because the high part is second.
			uint hashLow = stream.ReadUInt32() ^ XM[0];
			uint hashHigh = stream.ReadUInt32() ^ XM[0];
			Hash = (ulong)hashHigh << 32 | hashLow;
		}
		MetaFlag = (Hash & HashingMetaFlag) > 0;
		CompressedSize = stream.ReadUInt32() ^ XM[1];
		UncompressedSize = stream.ReadUInt32() ^ XM[2];

		DataHash = Data::MD5(stream.ReadBytes(16));

		DataOffset = stream.GetPosition();

		uint hashLow = Hash & 0xFFFFFFFF;
		uint index = (2 * ((hashLow) % 4));
		ulong header = stream.ReadUInt64() ^ ((ulong)DecryptionTable[index + 1] << 32 | DecryptionTable[index]);

		Encryption = header;
		if (Encryption == Magic1 || Encryption == Magic2)
		{
			Key = header >> 32;
		}
		else
		{
			Encryption = 0;
		}
	}

	ulong SQARFile::GetUncompressedSize()
	{
		return UncompressedSize;
	}

	ulong SQARFile::GetCompressedSize()
	{
		return CompressedSize;
	}

	ulong SQARFile::GetDataOffset()
	{
		return DataOffset;
	}

	ulong SQARFile::GetHash()
	{
		return Hash;
	}

	bool SQARFile::IsCompressed()
	{
		return CompressedSize != UncompressedSize;
	}

	bool SQARFile::IsEncrypted()
	{
		return Encryption != 0;
	}
}