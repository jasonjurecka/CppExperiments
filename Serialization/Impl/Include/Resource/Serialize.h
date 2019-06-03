#pragma once

#include <cassert>
#include <filesystem>
#include <functional>
#include <vector>

namespace Resourcing
{
	using EnumeratedSerializeFunc = std::function<bool(const void*, std::vector<uint8_t>&)>;

	template <typename type>
	std::vector<EnumeratedSerializeFunc>& EnumeratedSerializeFunctions();

	template <typename type>
	bool EnumeratedSerialize(const std::vector<EnumeratedSerializeFunc>& funcs, const type& data, std::vector<uint8_t>& outData)
	{
		const void* vdata = static_cast<const void*>(&data);
		for (auto func : funcs)
		{
			if (!func(vdata, outData))
			{
				return false;
			}
		}
		return true;
	}

	template <typename type>
	bool Serialize(const type& data, std::vector<uint8_t>& outData)
	{
		if constexpr(std::is_trivially_copyable_v<type>)
		{
			outData.resize(outData.size() + sizeof(type));
			auto* output = outData.data();
			output += outData.size() - sizeof(type);
			type* outVersion = reinterpret_cast<type*>(output);
			*outVersion = data;
			return true;
		}
		else
		{
			return EnumeratedSerialize(EnumeratedSerializeFunctions<type>(), data, outData);
		}
		
	}

	template <typename type>
	bool Serialize(const std::vector<type>& vector, std::vector<uint8_t>& outData)
	{
		auto size = static_cast<uint32_t>(vector.size());
		bool result = Serialize(size, outData);
		if (result)
		{
			for (const auto& item : vector)
			{
				result = Serialize(item, outData);
				if (!result)
				{
					break;
				}
			}
		}
		return result;
	}

	template <typename type, size_t num>
	bool Serialize(const std::array<type, num>& array, std::vector<uint8_t>& outData)
	{
		auto size = static_cast<uint32_t>(num);
		bool result = Serialize(size, outData);
		if (result)
		{
			for (const auto& item : array)
			{
				result = Serialize(item, outData);
				if (!result)
				{
					break;
				}
			}
		}
		return result;
	}

	template<typename type, std::size_t dataOffset = 0>
	bool EnumeratedSerialize(const void* structPtr, std::vector<uint8_t>& outData)
	{
		//Convert to expected type
		const type* dataptr = reinterpret_cast<const type*>((reinterpret_cast<const char*>(structPtr) + dataOffset));
		return Serialize(*dataptr, outData);
	}

	template<typename type>
	bool SerializeToFile(const type& resource, const std::filesystem::path& resourcePath)
	{
		assert(resourcePath.has_filename());
		std::vector<uint8_t> serializedData;
		if (!Resourcing::Serialize(resource, serializedData))
		{
			return false;
		}

		auto dirPath = resourcePath.parent_path();
		if (!std::filesystem::exists(dirPath))
		{
			std::filesystem::create_directories(dirPath);
		}

		std::ofstream outFile;
		outFile.open(resourcePath, std::ofstream::binary | std::ofstream::out);
		assert(outFile.is_open());
		outFile.write(reinterpret_cast<const char*>(serializedData.data()), serializedData.size());
		outFile.close();
		return true;
	}
}