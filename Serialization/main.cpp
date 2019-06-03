#include "Include/Resource/Definition.h"
#include "Vector.resourceType"

#include "Include/Resource/Serialize.h"
#include "Include/Resource/Deserialize.h"

int main()
{
	const Resourcing::Vector3 test = {12.0f, 3.0f, 0.0f};

	std::filesystem::path outpath = "serializeTest.txt";
	Resourcing::SerializeToFile(test, outpath);

	std::ifstream file;
	file.open(outpath, std::ifstream::binary | std::ifstream::in);
	Resourcing::Vector3 result;
	Resourcing::Deserialize(result, file);

	assert(test.m_1 == result.m_1);
	assert(test.m_2 == result.m_2);
	assert(test.m_3 == result.m_3);

	// TODO:  Tests for the string hashing impl
	return 0;
}
