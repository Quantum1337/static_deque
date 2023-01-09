#pragma once

#include "LIB_StaticDeque_Types.hpp"

#include <iterator>

namespace std_static
{
namespace Implementation
{

template<typename T, typename TDequeBase>
class iterator
{
    public:
        // -- Traits
        using value_type = typename TDequeBase::value_type;
        using reference = T&;
        using pointer = T*;
        using difference_type = typename TDequeBase::difference_type;
        using iterator_category = std::random_access_iterator_tag;

        // -- Constructors
        iterator(difference_type _initialIndex, pointer _storage, TDequeBase& _base)
        : m_index{_initialIndex}
        , m_storage{_storage}
        , m_base{_base}
        {
        }
        iterator(iterator<value_type, TDequeBase> const& _other)
        : m_index(_other.m_index)
        , m_storage(_other.m_storage)
        , m_base{_other.m_base}
        {
        }
    
        // -- Assignment
        iterator& operator=(iterator const& _other)
        {
            m_index = _other.m_index;
            return *this;
        }

        // -- (+)
        iterator operator+(difference_type _offset) { return (iterator(*this) += _offset); }
        iterator& operator++() { ((++m_index) == storage_size()) ? m_index = 0 : m_index; return *this; }
        iterator& operator+=(difference_type _offset)
        {
            if(_offset >= 0)
            {
                m_index += _offset;
                (m_index >= storage_size()) ? m_index = (m_index - storage_size()) : m_index;
            }
            else
            {
                operator-= (-_offset);
            }
            return *this;
        }

        // -- (-)
        iterator operator-(difference_type _offset) { return (iterator(*this) -= _offset); }
        difference_type operator-(iterator const& _other) const { return ((iterator(*this) -= _other.m_index).m_index); }
        iterator& operator--() { ((m_index--) == 0) ? m_index = (storage_size() - 1u) : m_index; return *this; }
        iterator& operator-=(difference_type _offset)
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
        bool operator==(iterator const& _other) const { return (m_index == _other.m_index); }
        bool operator!=(iterator const& _other) const { return !(*this == _other); }
        bool operator<(iterator const& _other) const { return (distanceFromBegin(*this) < distanceFromBegin(_other)); }    
        bool operator<=(iterator const& _other) const { return !(_other < *this); }
        bool operator>(iterator const& _other) const { return (_other < *this); }
        bool operator>=(iterator const& _other) const { return !(*this < _other); }

    private:
        size_type storage_size() { return (m_base.max_size() + 1u); }
        difference_type distanceFromBegin(iterator& _iterator) { return (_iterator - m_base.begin()); }

        difference_type   m_index;
        pointer const     m_storage;
        TDequeBase const& m_base;

        friend class iterator<value_type const, TDequeBase>;
        friend class iterator<value_type, TDequeBase>;
};

} // namespace Implementation
} // namespace std_static
