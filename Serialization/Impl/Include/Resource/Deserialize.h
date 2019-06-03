#pragma once

#include <cassert>
#include <fstream>
#include <functional>
#include <vector>

namespace Resourcing
{
	using EnumeratedDeserializeFunc = std::function<bool(void* structPtr, std::ifstream& inData)>;

	template <typename type>
	std::vector<EnumeratedDeserializeFunc>& EnumeratedDeserializeFunctions();

	template <typename type>
	bool EnumeratedDeserialize(const std::vector<EnumeratedDeserializeFunc>& funcs, type& outData, std::ifstream& inData)
	{
		assert(inData.is_open());
		void* vdata = static_cast<void*>(&outData);
		for (auto func : funcs)
		{
			if (!func(vdata, inData))
			{
				return false;
			}
		}
		return true;
	}

	template <typename type>
	bool Deserialize(type& outData, std::ifstream& inData)
	{
		assert(inData.is_open());
		if constexpr (std::is_trivially_copyable_v<type>)
		{
			inData.read(static_cast<char*>(static_cast<void*>(&outData)), sizeof(type));
			return true;
		}
		else
		{
			return EnumeratedDeserialize(EnumeratedDeserializeFunctions<type>(), outData, inData);
		}
	}

	template <typename type>
	bool Deserialize(std::vector<type>& vector, std::ifstream& inData)
	{
		assert(inData.is_open());
		uint32_t count = 0;
		if (Deserialize(count, inData))
		{
			vector.reserve(count);
			while (count > 0)
			{
				type temp;
				if (Deserialize(temp, inData))
				{
					vector.push_back(temp);
				}
				else
				{
					break;
				}
				count--;
			}
			return (vector.size() == vector.capacity());
		}
		return false;
	}

	template <typename type, size_t num>
	bool Deserialize(std::array<type, num>& array, std::ifstream& inData)
	{
		assert(inData.is_open());
		uint32_t count = 0;
		if (Deserialize(count, inData))
		{
			assert(static_cast<uint32_t>(num) == count);
			for (type& item : array)
			{
				if (!Deserialize(item, inData))
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}

	template<typename type, std::size_t dataOffset = 0>
	bool EnumeratedDeserialize(void* structPtr, std::ifstream& inData)
	{
		assert(inData.is_open());
		//Convert to expected type
		type* dataptr = reinterpret_cast<type*>((reinterpret_cast<char*>(structPtr) + dataOffset));
		return Deserialize(*dataptr, inData);
	}
}