#pragma once

#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <emmintrin.h>
#include <string>

using ubyte = uint8_t;
using ushort = uint16_t;
using uint = uint32_t;
using ulong = uint64_t;

static constexpr uint XM[]
{
	0x41441043,
	0x11C22050,
	0xD05608C3,
	0x532C7319
};

static constexpr uint Magic1 = 0xA0F8EFE6;
static constexpr uint Magic2 = 0xE3F8EFE6;