#include "pch.h"
#include "PInvoke.h"
#include "Fpk.h"

#define CreateFileForReading(x) CreateFile(x, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING , NULL)

using namespace Fs;

// I hate this code so much
void GetFileInfo(HANDLE fileHandle, uint* fileInfoCount, Fs::Sqar::SqarFileInformation** fileInfo)
{
	auto stream = ReadFile(fileHandle);
	auto archive = Sqar::Sqar(stream);

	*fileInfoCount = archive.GetFileCount();
	*fileInfo = (Sqar::SqarFileInformation*)CoTaskMemAlloc(*fileInfoCount * sizeof(Sqar::SqarFileInformation));
	archive.PopulateFileInfo(*fileInfo);

	return;
}

void GetFpk()
{
	auto fpkHash = Data::Hashing::HashFilePathWithExtension("/Assets/tpp/pack/location/afgh/pack_large/afgh_ruins.fpkd");

	auto stream = ReadFile(CreateFileForReading(L"D:\\SteamLibrary\\steamapps\\common\\MGS_TPP\\master\\chunk2.dat"));
	auto archive = Sqar::Sqar(stream);
	archive.InitFileList();
	auto blob = archive.GetEntry(fpkHash);
	auto fpk = Fs::Fpk::Fpk(UDataStream(blob.data));
	fpk.GetFileCount();

	return;
}