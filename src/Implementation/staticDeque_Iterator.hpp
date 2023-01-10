#pragma once

#include "staticDeque_Types.hpp"

#include <iterator>

namespace std_static
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
} // namespace std_static
