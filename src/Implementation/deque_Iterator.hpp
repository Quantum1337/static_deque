/*
MIT License

Copyright (c) 2023 Quantum1337

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include "deque_Types.hpp"

#include <iterator>

namespace stds
{
namespace Implementation
{

template<typename T, typename TDequeBase>
class base_iterator
{
    public:
        // -- Traits
        using value_type = typename TDequeBase::value_type;
        using reference = T&;
        using pointer = T*;
        using difference_type = typename TDequeBase::difference_type;
        using iterator_category = std::random_access_iterator_tag;

    private:
        using iterator = base_iterator<value_type, TDequeBase>;
        using const_iterator = base_iterator<value_type const, TDequeBase>;
        
    public:

        // -- Constructors
        base_iterator(difference_type _initialIndex, pointer _storage, TDequeBase& _base)
        : m_index{_initialIndex}
        , m_storage{_storage}
        , m_base{_base}
        {
        }
        base_iterator(iterator const& _other)
        : m_index(_other.m_index)
        , m_storage(_other.m_storage)
        , m_base{_other.m_base}
        {
        }
    
        // -- Assignment
        base_iterator& operator=(base_iterator const& _other)
        {
            m_index = _other.m_index;
            return *this;
        }

        // -- (+)
        base_iterator operator+(difference_type _offset) { return (base_iterator(*this) += _offset); }
        base_iterator& operator++() { (static_cast<size_type>((++m_index)) == storage_size()) ? m_index = 0 : m_index; return *this; }
        base_iterator& operator+=(difference_type _offset)
        {
            if(_offset >= 0)
            {
                m_index += _offset;
                (static_cast<size_type>(m_index) >= storage_size()) ? m_index = (m_index - storage_size()) : m_index;
            }
            else
            {
                operator-= (-_offset);
            }
            return *this;
        }

        // -- (-)
        base_iterator operator-(difference_type _offset) { return (base_iterator(*this) -= _offset); }
        difference_type operator-(const_iterator const& _other) const { return ((base_iterator(*this) -= _other.m_index).m_index); }
        base_iterator& operator--() { ((m_index--) == 0) ? m_index = (storage_size() - 1u) : m_index; return *this; }
        base_iterator& operator-=(difference_type _offset)
        {
            if(_offset >= 0)
            {
                m_index -= _offset; 
                (m_index < 0) ? m_index = ((m_index + storage_size())) : m_index;
            }
            else
            {
                operator+= (-_offset);
            }
            return *this;
        }

        // -- Access
        reference operator*() const { return m_storage[m_index]; }
        pointer operator->() const { return &(m_storage[m_index]); }

        // -- Binary operators
        bool operator==(const_iterator const& _other) const { return (m_index == _other.m_index); }
        bool operator!=(const_iterator const& _other) const { return !(*this == _other); }
        bool operator<(const_iterator const& _other) const { return (distanceFromBegin(*this) < distanceFromBegin(_other)); }    
        bool operator<=(const_iterator const& _other) const { return !(_other < *this); }
        bool operator>(const_iterator const& _other) const { return (_other < *this); }
        bool operator>=(const_iterator const& _other) const { return !(*this < _other); }

    private:
        size_type storage_size() { return (m_base.max_size() + 1u); }
        difference_type distanceFromBegin(const_iterator const& _iterator) const { return (_iterator - m_base.begin()); }

        difference_type   m_index;
        pointer const     m_storage;
        TDequeBase const& m_base;

        friend iterator;
        friend const_iterator;
};

} // namespace Implementation
} // namespace stds
