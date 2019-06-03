#pragma once

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp) &&
	enable_vector_math_operators<std::tuple<Tp...>>::complex, float>::type
	addterms(const std::tuple<Tp...>& /*unused*/)
{
	return 0.0f;
}

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if < I < sizeof...(Tp) &&
	enable_vector_math_operators<std::tuple<Tp...>>::complex, float>::type
	addterms(const std::tuple<Tp...>& vector)
{
	return std::get<I>(vector) + addterms<I + 1, Tp...>(vector);
}

template< typename vecType,
	typename std::enable_if<enable_vector_math_operators<vecType>::complex, int32_t>::type = 0>
	inline float Magnitude(const vecType& vec)
{
	vecType result = vec * vec;
	float fresult = addterms(result);
	return sqrtf(fresult);
}

template< typename vecType,
	typename std::enable_if<enable_vector_math_operators<vecType>::complex, int32_t>::type = 0>
	inline vecType Normalize(const vecType& vec)
{
	float mag = Magnitude(vec);
	return vec / mag;
}

template< typename vecType,
	typename std::enable_if<enable_vector_math_operators<vecType>::complex, int32_t>::type = 0>
	inline float DotProduct(const vecType& l_vec, const vecType& r_vec)
{
	vecType result = l_vec * r_vec;
	return addterms(result);
}

template< typename vecType,
	typename std::enable_if<enable_vector_math_operators<vecType>::complex, int32_t>::type = 0>
	vecType CrossProduct(const vecType& /*unused*/, const vecType& /*unused*/)
{
	static_assert(0, "CrossProduct not specialized for type");
}
