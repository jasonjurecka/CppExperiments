#include "Include/StringHash.h"

namespace StringHash
{
	HashValue GetHash(const char* _toHash)
	{
		HashValue retval = NULL_HASH;

		if (_toHash)
		{
			HashValue val = NULL_HASH;
			const char* iter = _toHash;
			uint32_t index = 0;

			while ((*iter) != '\0')
			{
				val = (uint32_t)(*iter);
				retval += (val * (index + 1) * s_PrimeTable[(val%s_PrimeNumCount)]);
				iter++; //move to next
				index++;
			}
		}

		return retval;
	}

	HashValue GetHash(const std::string& _toHash)
	{
		return GetHash(_toHash.c_str());
	}
}