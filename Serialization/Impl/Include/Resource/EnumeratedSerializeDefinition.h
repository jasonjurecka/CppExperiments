#pragma once

/*
	Note: This macro setup produces a function (EnumeratedSerializeFunctions) that is the enumerated members of a type
	that is defined as a resource type

	Using templates here allows for better code generation as resource types that are considered
	is_trivially_copyable_v will never use this code and thus save code size and get a performance gain
	for copy of those objects.

	Example :

	RSC_DATA_BEGIN(Vector2)
	RSC_DATA(Vector2, float, m_1)
	RSC_DATA(Vector2, float, m_2)
	RSC_DATA_END(Vector2)

	template <>
	std::vector<EnumeratedSerializeFunc>& EnumeratedSerializeFunctions<Vector2>()
	{
		static std::vector<EnumeratedSerializeFunc> s_Enumerated = {
			&EnumeratedSerialize<float, offsetof(Vector2, m_1)>,
			&EnumeratedSerialize<float, offsetof(Vector2, m_2)>,
		};
		return s_Enumerated;
	}
*/

#undef RSC_DATA
#undef RSC_DATA_W_DEFAULT
#undef RSC_DATA_BEGIN
#undef RSC_DATA_END

#define RSC_DATA(structName, type, varname) &EnumeratedSerialize<type, offsetof(structName, varname)>,
#define RSC_DATA_W_DEFAULT(structName, type, varname, default) &EnumeratedSerialize<type, offsetof(structName, varname)>,

#define RSC_DATA_BEGIN(structName) template <> std::vector<EnumeratedSerializeFunc>& EnumeratedSerializeFunctions<structName>(){\
	static std::vector<EnumeratedSerializeFunc> s_Enumerated = {
#define RSC_DATA_END(structName) }; return s_Enumerated;}