#include "pch.h"
#include "IO.h"
#include "SQAR.h"
#include "Hashing.h"

int main()
{
	auto stream = ReadFile(L"chunk0.dat");

	auto archive = new SQAR(stream);

	ulong hash = HashFilePathWithExtension("/Assets/fox/pack/ui/prefab/ui_prefab_list.fpk");
	WriteFile(L"ui_prefab_list.fpk", archive->GetEntry(hash >> 32));

	return 0;
}