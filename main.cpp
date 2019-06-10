#include "pch.h"
#include "IO.h"
#include "Sqar.h"

using namespace Fs;

#define CreateFileForReading(x) CreateFile(x, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING , NULL)

int main()
{
	{
		auto stream = ReadFile(CreateFileForReading(L"C:\\Program Files (x86)\\Steam\\steamapps\\common\\MGS_TPP\\master\\chunk0.dat"));
		auto archive = Sqar::Sqar(stream);
		auto buffer = (Sqar::SqarFileInformation*)new ubyte[archive.GetFileCount() * 16];
		archive.PopulateFileInfo(buffer);
		delete[] buffer;
	}

	{
		auto stream = ReadFile(CreateFileForReading(L"C:\\Program Files (x86)\\Steam\\steamapps\\common\\MGS_TPP\\master\\chunk1.dat"));
		auto archive = Sqar::Sqar(stream);
		auto buffer = (Sqar::SqarFileInformation*)new ubyte[archive.GetFileCount() * 16];
		archive.PopulateFileInfo(buffer);
		delete[] buffer;
	}

	{
		auto stream = ReadFile(CreateFileForReading(L"C:\\Program Files (x86)\\Steam\\steamapps\\common\\MGS_TPP\\master\\chunk2.dat"));
		auto archive = Sqar::Sqar(stream);
		auto buffer = (Sqar::SqarFileInformation*)new ubyte[archive.GetFileCount() * 16];
		archive.PopulateFileInfo(buffer);
		delete[] buffer;
	}

	{
		auto stream = ReadFile(CreateFileForReading(L"C:\\Program Files (x86)\\Steam\\steamapps\\common\\MGS_TPP\\master\\chunk3.dat"));
		auto archive = Sqar::Sqar(stream);
		auto buffer = (Sqar::SqarFileInformation*)new ubyte[archive.GetFileCount() * 16];
		archive.PopulateFileInfo(buffer);
		delete[] buffer;
	}

	{
		auto stream = ReadFile(CreateFileForReading(L"C:\\Program Files (x86)\\Steam\\steamapps\\common\\MGS_TPP\\master\\chunk4.dat"));
		auto archive = Sqar::Sqar(stream);
		auto buffer = (Sqar::SqarFileInformation*)new ubyte[archive.GetFileCount() * 16];
		archive.PopulateFileInfo(buffer);
		delete[] buffer;
	}

	return 0;
}