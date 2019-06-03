#pragma once

#include "Include/StringHash/StringHash.h"

#include <array>

namespace Resourcing
{
	using DataVersion = HashValue;
	using TypeId = HashValue;
	using FileId = HashValue;

	using String32 = std::array<char, 32>;
	using String128 = std::array<char, 128>;
}