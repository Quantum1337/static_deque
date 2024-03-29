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

#include "Implementation/deque_Iterator.hpp"
#include "Implementation/deque_Types.hpp"
#include "Implementation/deque_Assert.hpp"

#include <algorithm>

namespace stds
{

template<typename T, Implementation::size_type=static_cast<Implementation::size_type>(0)>
class deque;

template<typename T>
class deque<T>
{
    public:
        // -- Traits
        using value_type = T;
        using reference = value_type&;
        using const_reference = value_type const&;
        using pointer = value_type*;
        using const_pointer = value_type const*;
        using size_type = Implementation::size_type;
        using difference_type = Implementation::difference_type;
        using iterator = Implementation::base_iterator<value_type, deque>;
        using const_iterator = Implementation::base_iterator<value_type const, deque>;
        using reverse_iterator = std::reverse_iterator<Implementation::base_iterator<value_type, deque>>;
        using const_reverse_iterator = std::reverse_iterator<Implementation::base_iterator<value_type const, deque>>;

        // -- Assignment operator
        deque& operator=(deque const& _other)
        {
            assign(_other.begin(), _other.end());
            return *this;
        }
        deque& operator=(deque&& _other)
        {              
            clear();
            internal_rangeInit(std::make_move_iterator(_other.begin()), 
                               std::make_move_iterator(_other.end()), 
                               back_inserter(*this));
            _other.clear();
            return *this;
        }
        deque& operator=(std::initializer_list<T> _ilist)
        {
            assign(_ilist);
            return *this;
        }

        // -- Assign
        void assign(size_type _count, T const& _value)
        {
            assert_count_in_range(_count);

            clear();
            unchecked_push_back_count(_count, _value); 
        }
        template<class InputIt>
        void assign(InputIt _first, InputIt _last)
        {            
            clear();
            internal_rangeInit(_first, _last, back_inserter(*this));                
        }
        void assign(std::initializer_list<T> _iList)
        {
            clear();
            internal_rangeInit(_iList.begin(), _iList.end(), back_inserter(*this));
        }
    
        // -- Element access
        reference at(size_type _pos)
        {
            assert_access_in_range(_pos);

            return (*this)[_pos];
        }    
        const_reference at(size_type _pos) const
        {
            assert_access_in_range(_pos);

            return (*this)[_pos];
        }

        reference operator[](size_type _pos) { return *(begin() += _pos); }
        const_reference operator[](size_type _pos) const { return *(cbegin() += _pos); }

        reference front() { return *begin(); }
        const_reference front() const { return *cbegin(); }

        reference back() { return *std::prev(end()); }
        const_reference back() const { return *std::prev(cend()); }

        // -- Iterators
        iterator begin() noexcept { return m_tail; };
        const_iterator begin() const noexcept { return m_tail; };
        const_iterator cbegin() const noexcept { return m_tail; };

        iterator end() noexcept { return m_head; };
        const_iterator end() const noexcept { return m_head; };
        const_iterator cend() const noexcept { return m_head; };

        reverse_iterator rbegin() noexcept { return reverse_iterator(m_head); };
        const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(m_head); };
        const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(m_head); };

        reverse_iterator rend() noexcept { return reverse_iterator(m_tail); };
        const_reverse_iterator rend() const noexcept { return const_reverse_iterator(m_tail); };
        const_reverse_iterator crend() const noexcept { return const_reverse_iterator(m_tail); };

        // -- Capacity
        size_type max_size() const { return m_capacity; };
        size_type size() const { return std::distance(m_tail, m_head); };
        bool empty() const { return (m_tail == m_head); };
        bool full() const { return (static_cast<size_type>(std::distance(m_tail, m_head)) == m_capacity); };

        // -- Modifiers
        void clear() noexcept
        {
            std::for_each(rbegin(), rend(), back_destroyer(*this));
        }

        iterator insert(const_iterator _pos, T const& _value)
        {
            assert_space_left();
            assert_iterator_in_range(_pos);

            return unchecked_insert_value(_pos, 1, _value); 
        }
        iterator insert(const_iterator _pos, T&& _value)
        {
            assert_space_left();
            assert_iterator_in_range(_pos);
            
            return unchecked_insert_value(_pos, 1, std::move(_value)); 
        }
        iterator insert(const_iterator _pos, size_type _count, const_reference _value)
        {
            assert_iterator_in_range(_pos);
            assert_count_in_range(size() + _count);

            return unchecked_insert_value(_pos, _count, _value);
        }
        template<class InputIt>
        iterator insert(const_iterator _pos, InputIt _first, InputIt _last)
        {
            assert_iterator_in_range(_pos);
            assert_valid_iterator_pair(_first, _last);
            assert_count_in_range(size() + std::distance(_first, _last)); //LCOV_EXCL_BR_LINE: We are not testing throw branches

            return unchecked_insert_it(_pos, _first, _last); //LCOV_EXCL_BR_LINE: We are not testing throw branches                          
        }
        iterator insert(const_iterator _pos, std::initializer_list<T> _iList)
        {
            assert_iterator_in_range(_pos);
            assert_count_in_range(size() + _iList.size());

            return unchecked_insert_it(_pos, _iList.begin(), _iList.end());
        }

        template<class... Args>
        iterator emplace(const_iterator _pos, Args&&... _args)
        {
            assert_space_left();
            assert_iterator_in_range(_pos);

            return unchecked_insert_value(_pos, 1, std::forward<Args>(_args)...);
        }

        iterator erase(const_iterator _pos)
        {
            assert_iterator_in_range(_pos);

            return unchecked_erase(_pos, std::next(_pos));
        }
        iterator erase(const_iterator _first, const_iterator _last)
        {
            assert_iterator_pair_in_range(_first, _last);

            return unchecked_erase(_first, _last);
        }

        void push_back(T const& _value)
        {
            assert_space_left();

            unchecked_push_back(_value);           
        }
        void push_back(T&& _value)
        {
            assert_space_left();

            unchecked_push_back(std::move(_value));
        }

        template<class... Args>
        void emplace_back(Args&&... _args)
        {
            assert_space_left(); 

            unchecked_push_back(std::forward<Args>(_args)...);          
        }

        void pop_back()
        {
            assert_has_elements();

            unchecked_pop_back();
        }

        void push_front(T const& _value)
        {
            assert_space_left();

            unchecked_push_front(_value);           
        }
        void push_front(T&& _value)
        {
            assert_space_left();

            unchecked_push_front(std::move(_value));
        }

        template<class... Args>
        void emplace_front(Args&&... _args)
        {
            assert_space_left(); 

            unchecked_push_front(std::forward<Args>(_args)...);          
        }

        void pop_front()
        {
            assert_has_elements();

            unchecked_pop_front();
        }

        void resize(size_type _count)
        {
            assert_count_in_range(_count); 

            unchecked_resize(_count);
        }
        void resize(size_type _count, value_type const& _value)
        {
            assert_count_in_range(_count);

            unchecked_resize(_count, _value);
        }

        void swap(deque& _other) noexcept
        {
            internal_swap(_other);
        }

    protected:

        // -- Constructor
        deque(pointer _storage, size_type _storageSize)
        : m_tail{static_cast<difference_type>(_storageSize / 2), _storage, *this}
        , m_head{m_tail}
        , m_capacity{_storageSize - 1u}
        {
            // This static assert validates the exclusion of AutosarC++19_03-A5.0.4: 
            // Only non-polymorphic or final classes can be used as elements
            static_assert((!std::is_class<T>::value || !std::is_polymorphic<T>::value) || std::is_final<T>::value,
                        "static_deque is not allowed for polymorphic and non-final classes");
        }

        // -- Destructor
        ~deque() { clear(); }

        // Lambdas for the functors below are also possible here and might be more readable !
        // -- Functors
        class back_destroyer
        {
            public:
                back_destroyer(deque& _deque): m_deque{_deque} {}     
                void operator()(const_reference _value) { static_cast<void>(_value); m_deque.unchecked_pop_back(); };
            private:
                deque& m_deque;
        };
        class front_destroyer
        {
            public:
                front_destroyer(deque& _deque): m_deque{_deque} {}
                void operator()(const_reference _value) { static_cast<void>(_value); m_deque.unchecked_pop_front(); };
            private:
                deque& m_deque;
        };

        // -- Iterator adapter (back inserter)
        template<typename TContainer>
        class back_insert_iterator : public std::iterator<std::output_iterator_tag, void, void, void, void>
        {
            public:
                back_insert_iterator(TContainer& _container)
                : m_container{_container} { }

                back_insert_iterator& operator=(typename TContainer::value_type const& _value)
                {
                    m_container.unchecked_push_back(_value);
                    return *this;
                }

                back_insert_iterator& operator=(typename TContainer::value_type&& _value)
                {
                    m_container.unchecked_push_back(std::move(_value));
                    return *this;
                }

                back_insert_iterator& operator*(){ return *this; }
                back_insert_iterator& operator++(){ return *this; }
                back_insert_iterator operator++(int){ return *this; }
            private:
                TContainer& m_container;
        }; 
        template<typename TContainer>
        inline back_insert_iterator<TContainer> back_inserter(TContainer& _container)
        { 
            return back_insert_iterator<TContainer>(_container); 
        }

        // -- Internal business logic
        iterator unchecked_erase(const_iterator _first, const_iterator _last)
        {
            if(_first != _last)
            {
                if(_first == begin())
                {
                    std::for_each(_first, _last, front_destroyer(*this)); //LCOV_EXCL_BR_LINE: We are not testing std::for_each branches
                    return to_iterator(_last);
                }
                else if (_last == end())
                {
                    std::for_each(std::make_reverse_iterator(_last), std::make_reverse_iterator(_first), back_destroyer(*this)); //LCOV_EXCL_BR_LINE: We are not testing std::for_each branches
                    return end();
                }
                else
                {
                    //ToDo: Pop_Back / Pop_Front depends on distance to begin() / end()
                    static_cast<void>(std::rotate(to_iterator(_first), to_iterator(_last), end())); //LCOV_EXCL_BR_LINE: We are not testing std::rotate branches
                    std::for_each(std::make_reverse_iterator(_last), std::make_reverse_iterator(_first), back_destroyer(*this)); //LCOV_EXCL_BR_LINE: We are not testing std::for_each branches
                    return to_iterator(_first);
                }
            }
            else
            {
                return to_iterator(_last);
            }
        }

        template<class InputIt>
        iterator unchecked_insert_it(const_iterator _pos, InputIt _first, InputIt _last)
        {
            iterator oldEnd{end()};
            (void) std::copy(_first, _last, back_inserter(*this));

            iterator positionToInsert{to_iterator(_pos)};
            (void) std::rotate(positionToInsert, oldEnd, end());   
            return positionToInsert;                            
        }
        template<typename... Type>
        iterator unchecked_insert_value(const_iterator _pos, size_type _count, Type&&... _value) noexcept
        {
            iterator oldEnd{end()};
            unchecked_push_back_count(_count, std::forward<Type>(_value)...);
            
            iterator positionToInsert{to_iterator(_pos)};
            (void) std::rotate(positionToInsert, oldEnd, end());
            return positionToInsert;
        }

        template<typename... Type>
        void unchecked_resize(size_type _count, Type&&... _value)
        {
            size_type curSize = size();

            if(_count < curSize)
            {
                reverse_iterator newEnd(begin() + static_cast<difference_type>(_count)); //LCOV_EXCL_BR_LINE: We are not testing throw branches
                std::for_each(rbegin(), newEnd, back_destroyer(*this)); //LCOV_EXCL_BR_LINE: We are not testing std::for_each branches
            }
            else if(_count > curSize)
            {
                unchecked_push_back_count((_count - curSize), std::forward<Type>(_value)...);
            }   
            // else: Same size as before  
        }

        template<typename... Type>
        void unchecked_push_back_count(size_type _count, Type&&... _value)
        {
            while (_count != 0)
            {
                unchecked_push_back(std::forward<Type>(_value)...);
                --_count;
            }
        }
        template<typename... Type>
        void unchecked_push_back(Type&&... _value)
        {
            new (&(*m_head)) T(std::forward<Type>(_value)...);
            ++m_head;
        }

        void unchecked_pop_back()
        {
            --m_head;
            (*m_head).~T();
        }

        template<typename... Type>
        void unchecked_push_front(Type&&... _value)
        {
            iterator tryTail(m_tail);

            --tryTail;
            new (&(*tryTail)) T(std::forward<Type>(_value)...);

            m_tail = tryTail;
        }

        void unchecked_pop_front()
        {
            (*m_tail).~T();
            ++m_tail;
        }

        void internal_swap(deque& _other) noexcept
        {
            if(size() < _other.size())
            {
                iterator pos = std::swap_ranges(begin(), end(), _other.begin());

                assert_count_in_range(size() + std::distance(pos, _other.end()));
                unchecked_insert_it(cend(), 
                                    std::make_move_iterator(pos), 
                                    std::make_move_iterator(_other.end()));

                _other.erase(pos, _other.cend());
            }
            else
            {
                iterator pos = std::swap_ranges(_other.begin(), _other.end(), begin());

                _other.insert(_other.cend(), 
                              std::make_move_iterator(pos), 
                              std::make_move_iterator(end()));

                unchecked_erase(pos, cend());
            }
        }

        template<typename InputIt, typename OutputIt>
        void internal_rangeInit(InputIt _first, InputIt _last, OutputIt _output)
        {
            assert_valid_iterator_pair(_first, _last);
            assert_count_in_range(std::distance(_first, _last));

            (void) std::copy(_first, _last, _output);
        }

        iterator to_iterator(const_iterator _iterator) noexcept
        {
            return begin() + (_iterator - begin());
        }

        // -- Asserts
        void assert_space_left() const noexcept
        {
            DEQUE_ASSERT(!full());
        }

        void assert_has_elements() const noexcept
        {
            DEQUE_ASSERT(!empty());
        }

        void assert_count_in_range(size_type _count) const noexcept
        {
            DEQUE_ASSERT(_count <= max_size());
        }

        void assert_access_in_range(size_type _count) const noexcept
        {
            DEQUE_ASSERT(_count <= size());
        }

        template<typename InputIt>
        void assert_iterator_in_range(InputIt _it) const noexcept
        {
            DEQUE_ASSERT(begin() <= _it);
            DEQUE_ASSERT(_it <= end());
        }

        template<typename InputIt>
        void assert_valid_iterator_pair(InputIt _first, InputIt _last) const noexcept
        {
            DEQUE_ASSERT(_first <= _last);
        }

        template<typename InputIt>
        void assert_iterator_pair_in_range(InputIt _first, InputIt _last) const noexcept
        {
            assert_iterator_in_range(_first);
            assert_iterator_in_range(_last);
            assert_valid_iterator_pair(_first, _last);
        }

    private:
        iterator        m_tail;
        iterator        m_head;
        size_type const m_capacity;
};


template <typename T, Implementation::size_type N>
class deque final : public deque<T>
{
    private:
        using base = deque<T>;
        
    public:
        // -- Traits
        using value_type = typename base::value_type;
        using reference = typename base::reference;
        using const_reference = typename base::const_reference;
        using pointer = typename base::pointer;
        using const_pointer = typename base::const_pointer;
        using size_type = typename base::size_type;
        using difference_type = typename base::difference_type;
        using iterator = typename base::iterator;
        using const_iterator = typename base::const_iterator;
        using reverse_iterator = typename base::reverse_iterator;
        using const_reverse_iterator = typename base::const_reverse_iterator;

        // -- Constructors
        deque()
        : base(static_cast<pointer>(static_cast<void*>(m_storage)), STORAGE_SIZE)
        {
            static_assert(STORAGE_SIZE > 1, "Invalid size");
        }
        explicit deque(size_type _count, T const& _value)
        : deque()
        {
            this->assert_count_in_range(_count);

            this->unchecked_push_back_count(_count, _value);       
        }
        explicit deque(size_type _count)
        : deque()
        {
            this->assert_count_in_range(_count);

            this->unchecked_push_back_count(_count, std::move(T())); 
        }
        template<class InputIt>
        deque(InputIt _first, InputIt _last)
        : deque()
        {
            this->internal_rangeInit(_first, _last, this->back_inserter(*this));
        }
        deque(deque const& _other) : deque(static_cast<base const&>(_other)) {}
        deque(base const& _other)  
        : deque()
        {
            this->internal_rangeInit(_other.begin(), _other.end(), this->back_inserter(*this));
        }
        deque(deque&& _other) : deque(std::move(static_cast<base&>(_other))) {}
        deque(base&& _other)
        : deque()
        {
            this->internal_rangeInit(std::make_move_iterator(_other.begin()), 
                                     std::make_move_iterator(_other.end()), 
                                     this->back_inserter(*this));
            _other.clear();
        }
        deque(std::initializer_list<T> _iList)
        : deque()
        {
            this->internal_rangeInit(_iList.begin(), _iList.end(), this->back_inserter(*this));
        }

        // -- Assignments
        deque& operator=(deque const& _other) { return operator=(static_cast<const base&>(_other)); }
        deque& operator=(base const& _other)
        {
            base::operator=(_other);
            return *this;
        }
        deque& operator=(deque&& _other) { return operator=(std::move(static_cast<base&>(_other))); }
        deque& operator=(base&& _other)
        {
            base::operator=(std::move(_other));
            _other.clear();
            return *this;
        }
        deque& operator=(std::initializer_list<T> _iList)
        {
            base::operator=(_iList);
            return *this;
        }

        // -- Swap
        void swap(base& _other) noexcept
        {
            this->internal_swap(_other);
        }

    private:
        static constexpr size_type STORAGE_SIZE = N + 1u;

        using storage_type = Implementation::aligned_storage_type<T>;
        storage_type m_storage[STORAGE_SIZE];
};

template <typename T>
constexpr bool operator==(deque<T> const& _lhs, 
                          deque<T> const& _rhs) noexcept
{
    return ((_lhs.size() == _rhs.size()) && std::equal(_lhs.cbegin(), _lhs.cend(), _rhs.cbegin()));
}

template <typename T>
constexpr bool operator!=(deque<T> const& _lhs, 
                          deque<T> const& _rhs) noexcept
{
    return !(_lhs == _rhs);
}

template <typename T>
constexpr bool operator<(deque<T> const& _lhs, 
                         deque<T> const& _rhs) noexcept
{
    return std::lexicographical_compare(_lhs.begin(), _lhs.end(), _rhs.begin(), _rhs.end());
}

template <typename T>
constexpr bool operator<=(deque<T> const& _lhs, 
                          deque<T> const& _rhs) noexcept
{
    return !(_rhs < _lhs);
}

template <typename T>
constexpr bool operator>(deque<T> const& _lhs, 
                         deque<T> const& _rhs) noexcept
{
    return (_rhs < _lhs);
}

template <typename T>
constexpr bool operator>=(deque<T> const& _lhs, 
                          deque<T> const& _rhs) noexcept
{
    return !(_lhs < _rhs);
}

template<typename T>
void swap(deque<T>& _lhs,
          deque<T>& _rhs) noexcept
{
    _lhs.swap(_rhs);
}

} // namespace stds
