#pragma once
#include "pch.h"
#include "city.h"
#include "bytell_hash_map.h"

namespace Data
{
	namespace Hashing
	{
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

		constexpr const char* FileExtensions[]
		{
			"1.ftexs",
			"1.nav2",
			"2.ftexs",
			"3.ftexs",
			"4.ftexs",
			"5.ftexs",
			"6.ftexs",
			"ag.evf",
			"aia",
			"aib",
			"aibc",
			"aig",
			"aigc",
			"aim",
			"aip",
			"ait",
			"atsh",
			"bnd",
			"bnk",
			"cc.evf",
			"clo",
			"csnav",
			"dat",
			"des",
			"dnav",
			"dnav2",
			"eng.lng",
			"ese",
			"evb",
			"evf",
			"fag",
			"fage",
			"fago",
			"fagp",
			"fagx",
			"fclo",
			"fcnp",
			"fcnpx",
			"fdes",
			"fdmg",
			"ffnt",
			"fmdl",
			"fmdlb",
			"fmtt",
			"fnt",
			"fova",
			"fox",
			"fox2",
			"fpk",
			"fpkd",
			"fpkl",
			"frdv",
			"fre.lng",
			"frig",
			"frt",
			"fsd",
			"fsm",
			"fsml",
			"fsop",
			"fstb",
			"ftex",
			"fv2",
			"fx.evf",
			"fxp",
			"gani",
			"geom",
			"ger.lng",
			"gpfp",
			"grxla",
			"grxoc",
			"gskl",
			"htre",
			"info",
			"ita.lng",
			"jpn.lng",
			"json",
			"lad",
			"ladb",
			"lani",
			"las",
			"lba",
			"lng",
			"lpsh",
			"lua",
			"mas",
			"mbl",
			"mog",
			"mtar",
			"mtl",
			"nav2",
			"nta",
			"obr",
			"obrb",
			"param",
			"parts",
			"path",
			"pftxs",
			"ph",
			"phep",
			"phsd",
			"por.lng",
			"qar",
			"rbs",
			"rdb",
			"rdf",
			"rnav",
			"rus.lng",
			"sad",
			"sand",
			"sani",
			"sbp",
			"sd.evf",
			"sdf",
			"sim",
			"simep",
			"snav",
			"spa.lng",
			"spch",
			"sub",
			"subp",
			"tgt",
			"tre2",
			"txt",
			"uia",
			"uif",
			"uig",
			"uigb",
			"uil",
			"uilb",
			"utxl",
			"veh",
			"vfx",
			"vfxbin",
			"vfxdb",
			"vnav",
			"vo.evf",
			"vpc",
			"wem",
			"wmv",
			"xml"
		};
		extern Data::bytell_hash_map<uint, const char*> FileExtensionMap;
	}
}