#pragma once

#include <stdint.h>
#include <tuple>

template<typename Type>
struct enable_vector_math_operators {
	static const bool basic = false;
	static const bool complex = false;
};

#include "Vector_Add.hpp"
#include "Vector_Subtract.hpp"
#include "Vector_Multiply.hpp"
#include "Vector_Divide.hpp"
#include "Vector_Misc.hpp"

using Vector2f = std::tuple<float, float>;
using Vector3f = std::tuple<float, float, float>;
using Vector4f = std::tuple<float, float, float, float>;
using Vector2i = std::tuple<int32_t, int32_t>;
using Vector3i = std::tuple<int32_t, int32_t, int32_t>;
using Vector4i = std::tuple<int32_t, int32_t, int32_t, int32_t>;

// Non-const access X Y Z W
template<typename t, size_t I = 0, typename = std::enable_if_t<std::is_floating_point_v < std::tuple_element_t< I, t >>>>
float& X(t & vec) { return std::get<I>(vec); }

template<typename t, size_t I = 1, typename = std::enable_if_t<std::is_floating_point_v < std::tuple_element_t< I, t >>>>
float& Y(t & vec) { return std::get<I>(vec); }

template<typename t, size_t I = 2, typename = std::enable_if_t<std::is_floating_point_v < std::tuple_element_t< I, t >>>>
float& Z(t & vec) { return std::get<I>(vec); }

template<typename t, size_t I = 3, typename = std::enable_if_t<std::is_floating_point_v < std::tuple_element_t< I, t >>>>
float& W(t & vec) { return std::get<I>(vec); }

template<typename t, size_t I = 0, typename = std::enable_if_t<std::is_integral_v < std::tuple_element_t< I, t >>>>
int32_t& X(t & vec) { return std::get<I>(vec); }

template<typename t, size_t I = 1, typename = std::enable_if_t<std::is_integral_v < std::tuple_element_t< I, t >>>>
int32_t& Y(t & vec) { return std::get<I>(vec); }

template<typename t, size_t I = 2, typename = std::enable_if_t<std::is_integral_v < std::tuple_element_t< I, t >>>>
int32_t& Z(t & vec) { return std::get<I>(vec); }

template<typename t, size_t I = 3, typename = std::enable_if_t<std::is_integral_v < std::tuple_element_t< I, t >>>>
int32_t& W(t & vec) { return std::get<I>(vec); }

// Const access X Y Z W
template<typename t, size_t I = 0, typename = std::enable_if_t<std::is_floating_point_v < std::tuple_element_t< I, t >>>>
float X(const t & vec) { return std::get<I>(vec); }

template<typename t, size_t I = 1, typename = std::enable_if_t<std::is_floating_point_v < std::tuple_element_t< I, t >>>>
float Y(const t & vec) { return std::get<I>(vec); }

template<typename t, size_t I = 2, typename = std::enable_if_t<std::is_floating_point_v < std::tuple_element_t< I, t >>>>
float Z(const t & vec) { return std::get<I>(vec); }

template<typename t, size_t I = 3, typename = std::enable_if_t<std::is_floating_point_v < std::tuple_element_t< I, t >>>>
float W(const t & vec) { return std::get<I>(vec); }

template<typename t, size_t I = 0, typename = std::enable_if_t<std::is_integral_v < std::tuple_element_t< I, t >>>>
int32_t X(const t & vec) { return std::get<I>(vec); }

template<typename t, size_t I = 1, typename = std::enable_if_t<std::is_integral_v < std::tuple_element_t< I, t >>>>
int32_t Y(const t & vec) { return std::get<I>(vec); }

template<typename t, size_t I = 2, typename = std::enable_if_t<std::is_integral_v < std::tuple_element_t< I, t >>>>
int32_t Z(const t & vec) { return std::get<I>(vec); }

template<typename t, size_t I = 3, typename = std::enable_if_t<std::is_integral_v < std::tuple_element_t< I, t >>>>
int32_t W(const t & vec) { return std::get<I>(vec); }

template<>
struct enable_vector_math_operators<Vector2f> {
	static const bool basic = true;
	static const bool complex = true;
};

template<>
struct enable_vector_math_operators<Vector3f> {
	static const bool basic = true;
	static const bool complex = true;
};

template<>
struct enable_vector_math_operators<Vector4f> {
	static const bool basic = true;
	static const bool complex = true;
};

template<>
struct enable_vector_math_operators<Vector2i> {
	static const bool basic = true;
};

template<>
struct enable_vector_math_operators<Vector3i> {
	static const bool basic = true;
};

template<>
struct enable_vector_math_operators<Vector4i> {
	static const bool basic = true;
};

template<>
inline Vector3f CrossProduct(const Vector3f& l_vec, const Vector3f& r_vec)
{
	return{ std::get<1>(l_vec) * std::get<2>(r_vec) - std::get<2>(l_vec) * std::get<1>(r_vec),
		std::get<2>(l_vec) * std::get<0>(r_vec) - std::get<0>(l_vec) * std::get<2>(r_vec),
		std::get<0>(l_vec) * std::get<1>(r_vec) - std::get<1>(l_vec) * std::get<0>(r_vec) };
}
