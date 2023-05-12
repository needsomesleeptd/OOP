//
// Created by Андрей on 01.05.2023.
//

#ifndef DZ2_OOP_UTILS_CONCEPTS_H_
#define DZ2_OOP_UTILS_CONCEPTS_H_

#include <type_traits>
#include <concepts>
#include "iterator"

template<typename T>
concept Comparable =
requires(T a, T b) {
	{ a < b } -> std::convertible_to<bool>;
	{ a > b } -> std::convertible_to<bool>;
	{ a == b } -> std::convertible_to<bool>;
};

template<typename T>
concept ValidNodeData = Comparable<T> && std::is_default_constructible<T>::value && std::is_copy_constructible<T>::value;

template<typename From, typename To>
concept Convertible = std::is_convertible<From, To>::value;

template<class T>
concept Container =
requires(T container) {
	typename T::value_type;
	typename T::size_type;
	typename T::iterator;
	typename T::const_iterator;
	{ container.begin() } noexcept -> std::same_as<typename T::iterator>;
	{ container.end() } noexcept -> std::same_as<typename T::iterator>;
	{ container.size() } noexcept -> std::same_as<typename T::size_type>;

};

#endif //DZ2_OOP_UTILS_CONCEPTS_H_
