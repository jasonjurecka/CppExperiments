#pragma once

/*
	Note: This macro setup produces a data structure of a type that is defined as a resource type

	Doing it this way provides a built in data version member for all resource types that are not
	default types (ie int float ... enum).

	Example :

	RSC_DATA_BEGIN(Vector2)
	RSC_DATA(Vector2, float, m_1)
	RSC_DATA(Vector2, float, m_2)
	RSC_DATA_END(Vector2)

	struct Vector2
	{
		float m_1;
		float m_2;
	};
*/
#undef RSC_DATA
#undef RSC_DATA_W_DEFAULT
#undef RSC_DATA_BEGIN
#undef RSC_DATA_END

#define RSC_DATA(structName, type, varname) type varname;
#define RSC_DATA_W_DEFAULT(structName, type, varname, default) type varname = default;
#define RSC_DATA_BEGIN(structName) struct structName {
#define RSC_DATA_END(structName) };
