#pragma once

#include <cstddef>
#include <type_traits>

namespace std_static
{
namespace Implementation
{

template <typename T>
using aligned_storage_type = typename std::aligned_storage_t<sizeof(T), alignof(T)>::type;
using difference_type = ptrdiff_t;
using size_type = size_t;

} // namespace Implementation
} // namespace std_static
