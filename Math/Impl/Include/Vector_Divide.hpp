#pragma once

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp) &&
	enable_vector_math_operators<std::tuple<Tp...>>::basic, void>::type
	div(const std::tuple<Tp...>& /*unused*/, const std::tuple<Tp...>& /*unused*/, std::tuple<Tp...>& /*unused*/)
{ }

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if < I < sizeof...(Tp), void>::type
	div(const std::tuple<Tp...>& left, const std::tuple<Tp...>& right, std::tuple<Tp...>& result)
{
	std::get<I>(result) = std::get<I>(left) / std::get<I>(right);
	div<I + 1, Tp...>(left, right, result);
}

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp) &&
	enable_vector_math_operators<std::tuple<Tp...>>::basic, void>::type
	div(const std::tuple<Tp...>& /*unused*/, const float& /*unused*/, std::tuple<Tp...>& /*unused*/)
{ }

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if < I < sizeof...(Tp), void>::type
	div(const std::tuple<Tp...>& left, const float& right, std::tuple<Tp...>& result)
{
	std::get<I>(result) = std::get<I>(left) / right;
	div<I + 1, Tp...>(left, right, result);
}

template< typename vecType,
	typename std::enable_if<enable_vector_math_operators<vecType>::basic, int32_t>::type = 0>
	vecType operator/(const vecType& l_vec3, const vecType& r_vec3)
{
	vecType result;
	div(l_vec3, r_vec3, result);
	return result;
}

template< typename vecType,
	typename std::enable_if<enable_vector_math_operators<vecType>::basic, int32_t>::type = 0>
	void operator/=(vecType& l_vec3, const vecType& r_vec3)
{
	div(l_vec3, r_vec3, l_vec3);
}

template< typename vecType,
	typename std::enable_if<enable_vector_math_operators<vecType>::basic, int32_t>::type = 0>
	vecType operator/(const vecType& l_vec3, const float r_scalar)
{
	vecType result;
	div(l_vec3, r_scalar, result);
	return result;
}

template< typename vecType,
	typename std::enable_if<enable_vector_math_operators<vecType>::basic, int32_t>::type = 0>
	void operator/=(vecType& l_vec3, const float r_scalar)
{
	div(l_vec3, r_scalar, l_vec3);
}
