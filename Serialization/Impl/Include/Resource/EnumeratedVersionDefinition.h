#pragma once

/*
	Note: This macro setup produces a function (Version) that is the data version of a type
	that is defined as a resource type

	Example :

	RSC_DATA_BEGIN(Vector2)
	RSC_DATA(Vector2, float, m_1)
	RSC_DATA(Vector2, float, m_2)
	RSC_DATA_END(Vector2)

	template <>
	DataVersion Version<Vector2>()
	{
		static constexpr const DataVersion s_Version = StringHash::GetHash_constexprString_Array({
			"Vector2",
			"float",
			"m_1",
			"float",
			"m_2",
		});
		static_assert(s_Version != 0, "Version calculation failed");
		return s_Version;
	}
*/

#undef RSC_DATA
#undef RSC_DATA_W_DEFAULT
#undef RSC_DATA_BEGIN
#undef RSC_DATA_END

#define RSC_DATA(structName, type, varname) #type, #varname,
#define RSC_DATA_W_DEFAULT(structName, type, varname, default) #type, #varname,

#define RSC_DATA_BEGIN(structName) template <> DataVersion Version<structName>() {\
	static constexpr const DataVersion s_Version = StringHash::GetHash_constexprString_Array({ #structName,

#define RSC_DATA_END(structName) }); static_assert(s_Version != 0, "Version calculation failed"); return s_Version; }