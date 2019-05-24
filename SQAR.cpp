#include "pch.h"
#include "SQAR.h"
#include <zlib.h>

static constexpr ubyte XM_Header[]
{
	0x00, 0x00, 0x00, 0x00,
	0x43, 0x10, 0x44, 0x41,
	0x50, 0x20, 0xC2, 0x11,
	0xC3, 0x08, 0x56, 0xD0,
	0x19, 0x73, 0x2C, 0x53,
	0x43, 0x10, 0x44, 0x41,
	0x43, 0x10, 0x44, 0x41,
	0x50, 0x20, 0xC2, 0x11
};

SQAR::SQAR(UDataStream& stream)
	: Data(stream.ReadBytes(0))
{
	// Copy header
	FormatHeader(stream.ReadBytes(32));

	auto sections = DecryptSectionList((ulong*)stream.ReadBytes(FileCount * 8));

	// Determines the alignment block size.
	int blockShiftBits = (Flags & 0x800) > 0 ? 12 : 10;

	auto entries = (SQARFile*)malloc(sizeof(SQARFile) * FileCount);
	for (uint i = 0; i < FileCount; i++)
	{
		auto section = sections[i];

		ulong sectionBlock = section >> 40;
		ulong hash = section & 0xFFFFFFFFFF;
		ulong sectionOffset = sectionBlock << blockShiftBits;
		stream.Seek(sectionOffset);

		entries[i] = SQARFile(stream);
		auto hashStart = hash & 0xFFFFFFFF;
		Entries.emplace(hashStart, entries + i); // remove extension prefix - temporary
	}
}

void SQAR::FormatHeader(ubyte* __restrict bytes)
{
	for (int i = 0; i < 32; ++i)
		((ubyte*)this)[i] = XM_Header[i] ^ bytes[i];
}

ulong* SQAR::DecryptSectionList(ulong* sections)
{
	ulong* result = new ulong[FileCount];

	for (int i = 0; i < FileCount; i += 1)
	{
		uint i1 = (uint)sections[i];
		uint i2 = sections[i] >> 32;
		int index1 = (i + ((i * sizeof(ulong)) / 5)) % 4;
		int index2 = (i + ((i * sizeof(ulong) + sizeof(uint)) / 5)) % 4;
		i1 ^= XM[index1];
		i2 ^= XM[index2];

		result[i] = (ulong)i2 << 32 | i1;
	}

	return result;
}

FileBlob SQAR::GetEntry(ulong hash)
{
	auto entry = Entries[hash];
	ubyte* buffer = nullptr;

	auto uncompressedSize = entry->GetUncompressedSize();
	auto dataOffset = entry->GetDataOffset();

	if (entry->IsCompressed())
	{
		auto compressedSize = entry->GetCompressedSize();

		auto decryptedData = DecryptData((uint)hash, dataOffset, compressedSize);
		buffer = new ubyte[uncompressedSize];
		uLong ucSize = uncompressedSize;
		uncompress(buffer, &ucSize, decryptedData, compressedSize);

		return { uncompressedSize, buffer };
	}

	memcpy(buffer, Data + dataOffset, uncompressedSize);
	return { uncompressedSize, buffer };
}

ubyte* SQAR::DecryptData(uint hashLow, ulong dataOffset, ulong size)
{
	auto data = Data + dataOffset;

	auto blocks = size / sizeof(ulong);
	for (uint i = 0; i < blocks; i++)
	{
		uint offset = i * sizeof(ulong);

		uint index = (2 * ((hashLow + offset / 11) % 4));

		*(ulong*)(data + offset) ^= (ulong)DecryptionTable[index + 1] << 32 | DecryptionTable[index];
	}

	uint remaining = size % sizeof(ulong);
	uint startOffset = blocks * sizeof(long);
	for (uint i = 0; i < remaining; i++)
	{
		uint offset = startOffset + i;

		uint index = (2 * ((hashLow + (offset - (offset % sizeof(long))) / 11) % 4));
		uint decryptionIndex = offset % sizeof(long);
		uint xorMask = decryptionIndex < 4 ? DecryptionTable[index] : DecryptionTable[index + 1];
		ubyte xorMaskByte = ((xorMask >> (8 * decryptionIndex)) & 0xff);
		data[offset] ^= xorMaskByte;
	}

	return data;
}

uint SQAR::GetFileCount()
{
	return FileCount;
}