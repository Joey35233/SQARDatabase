#pragma once
#include "pch.h"
#include "IO.h"
#include "MD5.h"

namespace Fs
{
	namespace Fpk::impl
	{
		class FpkString
		{
		public:
			FpkString();
			FpkString(UDataStream&);
			ulong Length;
			char* String;
		};

		class FpkFile
		{
		public:
			FpkFile(UDataStream&);
			ulong GetDataOffset();
			ulong GetDataSize();
			FpkString GetName();

		private:
			ulong DataOffset;
			ulong DataSize;
			FpkString Name;
			Data::MD5 DataHash;
		};

		class FpkReference
		{
		public:
			FpkReference(UDataStream&);
		private:
			FpkString ReferenceName;
		};
	}
}