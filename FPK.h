#pragma once
#include "pch.h"
#include "IO.h"
#include "FPKEntry.h"

namespace Fs
{
	namespace FPK
	{
		class FPK
		{
		public:
			FPK(UDataStream&);
			uint GetFileCount();
			uint GetReferenceCount();
			NamedFileBlob* GetFiles();

		private:
			ubyte* Data;
			uint FileCount;
			uint ReferenceCount;
			impl::FPKFile* Files;
			impl::FPKReference* References;
		};
	}
}