#pragma once

#include <string>

using HashValue = uint32_t;

namespace StringHash
{
	static constexpr HashValue NULL_HASH = 0;

	//Prime table used in calculating the string hash
	static constexpr uint32_t s_PrimeNumCount = 168;
	static constexpr uint32_t s_PrimeTable[] = {
		2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
		53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107,
		109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
		173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
		233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283,
		293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359,
		367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431,
		433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491,
		499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571,
		577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641,
		643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709,
		719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787,
		797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859,
		863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
		947, 953, 967, 971, 977, 983, 991, 997
	};

	class constexprString {
		const char* p;
		std::size_t sz;
	public:
		template<std::size_t N>
		constexpr constexprString(const char(&a)[N]) : p(a), sz(N - 1) {}
		constexpr char operator[](std::size_t n) const { return (n >= sz) ? '\0' : p[n]; }
		constexpr std::size_t size() const { return sz; }
		constexpr const char* operator*() const { return p; }
	};

	constexpr HashValue GetHash_constexprString(const char* _toHash, uint32_t size)
	{
		HashValue final = NULL_HASH;
		for (uint32_t index = 0; index < size; index++)
		{
			final += (static_cast<uint32_t>(_toHash[index]) * (index + 1)
				* s_PrimeTable[(static_cast<uint32_t>(_toHash[index]) % s_PrimeNumCount)]);
		}
		return final;
	}

	constexpr HashValue GetHash_constexprString(const constexprString& _toHash)
	{
		return GetHash_constexprString(*_toHash, static_cast<uint32_t>(_toHash.size()));
	}

	template<std::uint32_t N>
	constexpr HashValue GetHash_constexprString_Array(const constexprString(&_toHash)[N])
	{
		HashValue final = NULL_HASH;
		for (uint32_t index = 0; index < N; index++)
		{
			final += (GetHash_constexprString(_toHash[index]) * s_PrimeTable[(index % s_PrimeNumCount)]);
		}
		return final;
	}
};

constexpr HashValue operator "" _Hash(const char* toHash, std::size_t size)
{
	return StringHash::GetHash_constexprString(toHash, static_cast<uint32_t>(size));
}

static_assert("Test"_Hash == StringHash::GetHash_constexprString("Test"), "hash operator test failed");

#define CONST_STRING_HASH(str) StringHash::GetHash_constexprString(str)
#define CONST_STRING_HASH_ARRAY(strarray) StringHash::GetHash_constexprString_Array(strarray)
#define LITERAL_AS_STRING(str) #str

static_assert((sizeof(StringHash::s_PrimeTable) / sizeof(StringHash::s_PrimeTable[0])) == StringHash::s_PrimeNumCount,
	"s_PrimeTable size is not what s_PrimeNumCount thinks it is");

static_assert(CONST_STRING_HASH("") == StringHash::NULL_HASH, "Compile time null string hash test");
static_assert(CONST_STRING_HASH("Boot") == 660413, "Compile time \"Boot\" string hash test");
static_assert(""_Hash == StringHash::NULL_HASH, "Compile time null string hash test");
static_assert("Boot"_Hash == 660413, "Compile time \"Boot\" string hash test");