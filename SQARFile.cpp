#include "pch.h"
#include "SqarFile.h"

namespace Fs::Sqar::impl
{
	static constexpr ulong HashingMetaFlag = 0x4000000000000;

	SqarFile::SqarFile(UDataStream stream)
	{
		// Hash - 64
		// USiz - 32
		// CSiz - 32
		// MD5  - 128
		Hash = stream.ReadUInt64() ^ (((ulong)XM[0] << 32) | XM[0]);
		MetaFlag = (Hash & HashingMetaFlag) > 0;
		CompressedSize = stream.ReadUInt32() ^ XM[1];
		UncompressedSize = stream.ReadUInt32() ^ XM[2];

		DataHash = Data::MD5(stream.ReadBytes(16));

		DataOffset = stream.GetPosition();

		uint hashLow = (uint)Hash;
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

	ulong SqarFile::GetUncompressedSize()
	{
		return UncompressedSize;
	}

	ulong SqarFile::GetCompressedSize()
	{
		return CompressedSize;
	}

	ulong SqarFile::GetDataOffset()
	{
		return DataOffset;
	}

	ulong SqarFile::GetHash()
	{
		return Hash;
	}

	bool SqarFile::IsCompressed()
	{
		return CompressedSize != UncompressedSize;
	}

	bool SqarFile::IsEncrypted()
	{
		return Encryption != 0;
	}
}