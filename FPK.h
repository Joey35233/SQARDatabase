#pragma once
#include "pch.h"
#include "IO.h"
#include "FpkEntry.h"

namespace Fs
{
	namespace Fpk
	{
		class Fpk
		{
		public:
			Fpk(UDataStream);
			uint GetFileCount();
			uint GetReferenceCount();
			NamedFileBlob* GetFiles();

		private:
			ubyte* Data;
			uint FileCount;
			uint ReferenceCount;
			impl::FpkFile* Files;
			impl::FpkReference* References;
		};
	}
}