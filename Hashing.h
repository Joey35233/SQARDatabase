#pragma once
#include "pch.h"
#include "city.h"

ulong Hash(const char* string);
ulong Hash(const char* string, uint length);

ulong HashName(const char* string);
ulong HashName(const char* string, uint length);

ulong HashFilePath(const char* string);
ulong HashFilePath(const char* string, uint length);

ulong HashExtension(const char* string);
ulong HashExtension(const char* string, uint length);

ulong HashFilePathWithExtension(const char* string);
ulong HashFilePathWithExtension(const char* string, uint length);

ulong HashFilePathWithExtension(const char* string, const char* extString);
ulong HashFilePathWithExtension(const char* string, uint length, const char* extString, uint extLength);