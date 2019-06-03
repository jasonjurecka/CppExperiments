#include "Include/Resource/Utility.h"

#include <string>

namespace Resourcing
{
	std::string MakeFilename(const HashValue namehash, const DataVersion resourceVersion)
	{
		return std::to_string(namehash) + "_" + std::to_string(resourceVersion);
	}
}