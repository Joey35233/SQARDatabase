#pragma once
#include "Database.Test.g.h"

namespace winrt::Database::implementation
{
	struct Test : TestT<Test>
	{
		Test() = default;

		void Dat();
	};
}