#include "../src/staticDeque.hpp"
#include "unity/unity.h"

#include <vector>
#include <queue>
#include <stack>

using namespace std_static;

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void Test_Constructors(void)
{
    { // Default constructor
        static constexpr size_t DEQUE_SIZE = 5u;
        static_deque<uint8_t, DEQUE_SIZE> UT_deque;

        TEST_ASSERT_EQUAL(true, UT_deque.empty());
        TEST_ASSERT_EQUAL(false, UT_deque.full());
        TEST_ASSERT_EQUAL(DEQUE_SIZE, UT_deque.max_size());
        TEST_ASSERT_EQUAL(0u, UT_deque.size());
    }

    { // Count / lvalue constructor
        static constexpr size_t DEQUE_SIZE = 5u;
        uint8_t UT_lvalue = 22;
        static_deque<uint8_t, DEQUE_SIZE> UT_deque(5, UT_lvalue);

        std::vector<uint32_t> UT_correctLayout{22,22,22,22,22};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
    }
    
    { // Count constructor
        static constexpr size_t DEQUE_SIZE = 5u;
        static_deque<uint8_t, DEQUE_SIZE> UT_deque(5);

        std::vector<uint32_t> UT_correctLayout{0,0,0,0,0};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
    }

    { // Iterator constructor
        static constexpr size_t DEQUE_SIZE = 5u;
        std::vector<uint8_t> UT_correctLayout{55,66,77,88,99};
        static_deque<uint8_t, DEQUE_SIZE> UT_deque(UT_correctLayout.begin(), UT_correctLayout.end());

        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
    }

    { // Copy-constructor 
        static constexpr size_t DEQUE_SIZE = 8u;
        static_deque<uint32_t, DEQUE_SIZE> UT_dequeSource{99,88,77,66,55,44,33};

        static constexpr size_t DEQUE_SIZE_SINK = 7u;
        static_deque<uint32_t, DEQUE_SIZE_SINK> UT_dequeSink(UT_dequeSource);

        std::vector<uint32_t> UT_correctLayout{99, 88, 77, 66, 55, 44, 33};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_dequeSink.begin()));
        TEST_ASSERT_EQUAL(7, UT_dequeSink.size());
        TEST_ASSERT_TRUE(UT_dequeSink.full());
    }

    { // Move-constructor 
        static constexpr size_t DEQUE_SIZE = 8u;
        static constexpr size_t DEQUE_SIZE_SINK = 7u;
        static_deque<uint32_t, DEQUE_SIZE_SINK> UT_dequeSink(static_deque<uint32_t, DEQUE_SIZE>{99,88,77,66,55,44,33});

        std::vector<uint32_t> UT_correctLayout{99, 88, 77, 66, 55, 44, 33};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_dequeSink.begin()));
        TEST_ASSERT_EQUAL(7, UT_dequeSink.size());
    }

    { // Initializer list constructor
        static constexpr size_t DEQUE_SIZE = 6u;
        static_deque<uint32_t, DEQUE_SIZE> UT_deque({11, 12, 13, 14, 15, 16});

        std::vector<uint32_t> UT_correctLayout{11, 12, 13, 14, 15, 16};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
    }

}

void Test_LValue_PushBack(void)
{
    static constexpr size_t DEQUE_SIZE = 6u;
    static_deque<uint8_t, DEQUE_SIZE> UT_deque;
    std::vector<uint8_t> UT_lvalues{6, 10, 11, 12, 13, 14};

    UT_deque.push_back(UT_lvalues[0]);
    TEST_ASSERT_EQUAL(false, UT_deque.empty());
    TEST_ASSERT_EQUAL(6, UT_deque.back());
    TEST_ASSERT_EQUAL(6, UT_deque.front());

    UT_deque.push_back(UT_lvalues[1]);
    UT_deque.push_back(UT_lvalues[2]);
    UT_deque.push_back(UT_lvalues[3]);
    UT_deque.push_back(UT_lvalues[4]);
    TEST_ASSERT_EQUAL(false, UT_deque.full());
    TEST_ASSERT_EQUAL(DEQUE_SIZE - 1u, UT_deque.size());
    TEST_ASSERT_EQUAL(13, UT_deque.back());
    TEST_ASSERT_EQUAL(6, UT_deque.front());

    UT_deque.push_back(UT_lvalues[5]);
    TEST_ASSERT_EQUAL(14, UT_deque.back());
    TEST_ASSERT_EQUAL(6, UT_deque.front());
    TEST_ASSERT_EQUAL(true, UT_deque.full());
    TEST_ASSERT_EQUAL(DEQUE_SIZE, UT_deque.size());
}

void Test_LValue_PushFront(void)
{
    static constexpr size_t DEQUE_SIZE = 7u;
    static_deque<uint8_t, DEQUE_SIZE> UT_deque;
    std::vector<uint8_t> UT_lvalues{9, 10, 11, 12, 13, 14, 15};

    UT_deque.push_front(UT_lvalues[0]);
    TEST_ASSERT_EQUAL(false, UT_deque.empty());
    TEST_ASSERT_EQUAL(9, UT_deque.back());
    TEST_ASSERT_EQUAL(9, UT_deque.front());
    TEST_ASSERT_EQUAL(1u, UT_deque.size());

    UT_deque.push_front(UT_lvalues[1]);
    UT_deque.push_front(UT_lvalues[2]);
    UT_deque.push_front(UT_lvalues[3]);
    UT_deque.push_front(UT_lvalues[4]);
    UT_deque.push_front(UT_lvalues[5]);
    TEST_ASSERT_EQUAL(false, UT_deque.full());
    TEST_ASSERT_EQUAL(DEQUE_SIZE - 1u, UT_deque.size());
    TEST_ASSERT_EQUAL(9, UT_deque.back());
    TEST_ASSERT_EQUAL(14, UT_deque.front());

    UT_deque.push_front(UT_lvalues[6]);
    TEST_ASSERT_EQUAL(9, UT_deque.back());
    TEST_ASSERT_EQUAL(15, UT_deque.front());
    TEST_ASSERT_EQUAL(true, UT_deque.full());
    TEST_ASSERT_EQUAL(DEQUE_SIZE, UT_deque.size());
}

void Test_RValue_PushBack(void)
{
    static uint32_t moveCtorCalls{0};
    static uint32_t moveAssignmentCalls{0};  

    class Moveable_Item
    {
        public:
            Moveable_Item(uint32_t _1, uint32_t _2, uint32_t _3)
                : m_1{_1}, m_2{_2}, m_3{_3}
            {
            }

            Moveable_Item(Moveable_Item&& _other)
            {
                ++moveCtorCalls;
                m_1 = _other.m_1;
                m_2 = _other.m_2;
                m_3 = _other.m_3;
            }

            Moveable_Item& operator=(Moveable_Item&& _other)
            {
                ++moveAssignmentCalls;
                return *this;
            }

            bool operator==(Moveable_Item const &_other) const
            {
                return ((m_1 == _other.m_1) && (m_2 == _other.m_2) && (m_3 == _other.m_3));
            }

        private:
            uint32_t m_1;
            uint32_t m_2;
            uint32_t m_3;
    };

    static constexpr size_t DEQUE_SIZE = 5u;
    static_deque<Moveable_Item, DEQUE_SIZE> UT_deque;

    UT_deque.push_back(Moveable_Item(0, 1, 2));
    TEST_ASSERT_EQUAL(false, UT_deque.empty());
    {
        bool testPass; Moveable_Item(0, 1, 2) == UT_deque.back() ? testPass = true : testPass = false;
        TEST_ASSERT_TRUE(testPass);
    }
    {
        bool testPass; Moveable_Item(0, 1, 2) == UT_deque.front() ? testPass = true : testPass = false;
        TEST_ASSERT_TRUE(testPass);
    }
    TEST_ASSERT_EQUAL(1u, UT_deque.size());

    UT_deque.push_back(Moveable_Item(3, 4, 5));
    UT_deque.push_back(Moveable_Item(6, 7, 8));
    UT_deque.push_back(Moveable_Item(9, 10, 11));
    TEST_ASSERT_EQUAL(false, UT_deque.full());
    TEST_ASSERT_EQUAL(DEQUE_SIZE - 1u, UT_deque.size());
    {
        bool testPass; Moveable_Item(9, 10, 11) == UT_deque.back() ? testPass = true : testPass = false;
        TEST_ASSERT_TRUE(testPass);
    }
    {
        bool testPass; Moveable_Item(0, 1, 2) == UT_deque.front() ? testPass = true : testPass = false;
        TEST_ASSERT_TRUE(testPass);
    }

    UT_deque.push_back(Moveable_Item(12, 13, 14));
    {
        bool testPass; Moveable_Item(12, 13, 14) == UT_deque.back() ? testPass = true : testPass = false;
        TEST_ASSERT_TRUE(testPass);
    }
    {
        bool testPass; Moveable_Item(0, 1, 2) == UT_deque.front() ? testPass = true : testPass = false;
        TEST_ASSERT_TRUE(testPass);
    }
    TEST_ASSERT_EQUAL(true, UT_deque.full());
    TEST_ASSERT_EQUAL(DEQUE_SIZE, UT_deque.size());
    TEST_ASSERT_EQUAL(UT_deque.size(), moveCtorCalls);
    TEST_ASSERT_EQUAL(0u, moveAssignmentCalls);
}

void Test_RValue_PushFront(void)
{
    static uint32_t moveCtorCalls{0};
    static uint32_t moveAssignmentCalls{0};  

    class Moveable_Item
    {
        public:
            Moveable_Item(uint32_t _1, uint32_t _2, uint32_t _3)
                : m_1{_1}, m_2{_2}, m_3{_3}
            {
            }

            Moveable_Item(Moveable_Item&& _other)
            {
                ++moveCtorCalls;
                m_1 = _other.m_1;
                m_2 = _other.m_2;
                m_3 = _other.m_3;
            }

            Moveable_Item& operator=(Moveable_Item&& _other)
            {
                ++moveAssignmentCalls;
                return *this;
            }

            bool operator==(Moveable_Item const &_other) const
            {
                return ((m_1 == _other.m_1) && (m_2 == _other.m_2) && (m_3 == _other.m_3));
            }

        private:
            uint32_t m_1;
            uint32_t m_2;
            uint32_t m_3;
    };

    static constexpr size_t DEQUE_SIZE = 7u;
    static_deque<Moveable_Item, DEQUE_SIZE> UT_deque;

    UT_deque.push_front(Moveable_Item(0, 1, 2));
    TEST_ASSERT_EQUAL(false, UT_deque.empty());
    {
        bool testPass; Moveable_Item(0, 1, 2) == UT_deque.back() ? testPass = true : testPass = false;
        TEST_ASSERT_TRUE(testPass);
    }
    {
        bool testPass; Moveable_Item(0, 1, 2) == UT_deque.front() ? testPass = true : testPass = false;
        TEST_ASSERT_TRUE(testPass);
    }
    TEST_ASSERT_EQUAL(1u, UT_deque.size());

    UT_deque.push_front(Moveable_Item(3, 4, 5));
    UT_deque.push_front(Moveable_Item(6, 7, 8));
    UT_deque.push_front(Moveable_Item(9, 10, 11));
    UT_deque.push_front(Moveable_Item(12, 13, 14));
    UT_deque.push_front(Moveable_Item(15, 16, 17));
    TEST_ASSERT_EQUAL(false, UT_deque.full());
    TEST_ASSERT_EQUAL(DEQUE_SIZE - 1u, UT_deque.size());
    {
        bool testPass; Moveable_Item(0, 1, 2) == UT_deque.back() ? testPass = true : testPass = false;
        TEST_ASSERT_TRUE(testPass);
    }
    {
        bool testPass; Moveable_Item(15, 16, 17) == UT_deque.front() ? testPass = true : testPass = false;
        TEST_ASSERT_TRUE(testPass);
    }

    UT_deque.push_front(Moveable_Item(18, 19, 20));
    {
        bool testPass; Moveable_Item(0, 1, 2) == UT_deque.back() ? testPass = true : testPass = false;
        TEST_ASSERT_TRUE(testPass);
    }
    {
        bool testPass; Moveable_Item(18, 19, 20) == UT_deque.front() ? testPass = true : testPass = false;
        TEST_ASSERT_TRUE(testPass);
    }
    TEST_ASSERT_EQUAL(true, UT_deque.full());
    TEST_ASSERT_EQUAL(DEQUE_SIZE, UT_deque.size());
    TEST_ASSERT_EQUAL(UT_deque.size(), moveCtorCalls);
    TEST_ASSERT_EQUAL(0u, moveAssignmentCalls);
}

void Test_PopFront_PopBack(void)
{
    static constexpr size_t DEQUE_SIZE = 8u;
    static_deque<uint8_t, DEQUE_SIZE> UT_deque({11, 12, 13, 14, 15, 16});     

    {
        UT_deque.pop_front();
        std::vector<uint32_t> UT_correctLayout{12, 13, 14, 15, 16};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
    }

    {
        UT_deque.pop_front();
        std::vector<uint32_t> UT_correctLayout{13, 14, 15, 16};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
    }

    {
        UT_deque.pop_front();
        std::vector<uint32_t> UT_correctLayout{14, 15, 16};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
    }

    {
        UT_deque.pop_back();
        std::vector<uint32_t> UT_correctLayout{14, 15};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
    }

    {
        UT_deque.pop_back();
        std::vector<uint32_t> UT_correctLayout{14};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
    }

    {
        UT_deque.pop_back();
        std::vector<uint32_t> UT_correctLayout{};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
        TEST_ASSERT_TRUE(UT_deque.empty());
    }

}

void Test_ElementAccess(void)
{
    static constexpr size_t DEQUE_SIZE = 4u;
    static_deque<uint32_t, DEQUE_SIZE> UT_deque;

    UT_deque.push_back(5);
    UT_deque.push_back(6);
    UT_deque.push_back(7);
    UT_deque.push_back(8);

    TEST_ASSERT_EQUAL(5, UT_deque[0]);
    TEST_ASSERT_EQUAL(6, UT_deque[1]);
    TEST_ASSERT_EQUAL(7, UT_deque[2]);
    TEST_ASSERT_EQUAL(8, UT_deque[3]);
    TEST_ASSERT_EQUAL(5, UT_deque.at(0));
    TEST_ASSERT_EQUAL(6, UT_deque.at(1));
    TEST_ASSERT_EQUAL(7, UT_deque.at(2));
    TEST_ASSERT_EQUAL(8, UT_deque.at(3));

    UT_deque[1] = 11;
    UT_deque.at(3) = 13;

    TEST_ASSERT_EQUAL(11, UT_deque[1]);
    TEST_ASSERT_EQUAL(13, UT_deque[3]);
    TEST_ASSERT_EQUAL(11, UT_deque.at(1));
    TEST_ASSERT_EQUAL(13, UT_deque.at(3));

    const static_deque<uint32_t, DEQUE_SIZE> UT_deque_2 = UT_deque;

    TEST_ASSERT_EQUAL(11, UT_deque_2[1]);
    TEST_ASSERT_EQUAL(13, UT_deque_2.at(3));
}

void Test_Insert(void)
{
    { // Copy insert (1)
        uint8_t value = 111;
        static constexpr size_t DEQUE_SINK_SIZE = 8u;
        static_deque<uint8_t, DEQUE_SINK_SIZE> UT_dequeSink({66, 77, 88, 99, 11, 22}); 

        auto insertPos = UT_dequeSink.insert((UT_dequeSink.begin() += 3), value);   

        std::vector<uint32_t> UT_correctLayout{66, 77, 88, 111, 99, 11, 22};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_dequeSink.begin()));
        TEST_ASSERT_EQUAL(111, *insertPos);    
    }

    { // Move insert (2)
        uint8_t value = 111;
        static constexpr size_t DEQUE_SINK_SIZE = 8u;
        static_deque<uint8_t, DEQUE_SINK_SIZE> UT_dequeSink({66, 77, 88, 99, 11, 22}); 

        auto insertPos = UT_dequeSink.insert((UT_dequeSink.begin() += 3), std::move(value));   

        std::vector<uint32_t> UT_correctLayout{66, 77, 88, 111, 99, 11, 22};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_dequeSink.begin()));
        TEST_ASSERT_EQUAL(111, *insertPos); 
    }

    { // Count copy insert (3)
        static constexpr size_t DEQUE_SINK_SIZE = 10u;
        static_deque<uint8_t, DEQUE_SINK_SIZE> UT_dequeSink({66, 77, 88, 99, 11, 22}); 

        auto insertPos = UT_dequeSink.insert((UT_dequeSink.begin() -= -3), static_cast<static_deque<uint8_t, DEQUE_SINK_SIZE>::size_type>(4), 111);   

        std::vector<uint32_t> UT_correctLayout{66, 77, 88, 111, 111, 111, 111, 99, 11, 22};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_dequeSink.begin()));
        TEST_ASSERT_EQUAL(111, *insertPos);    
    }

    { // Iterator insert (4)
        static constexpr size_t DEQUE_SOURCE_SIZE = 6u;
        static_deque<uint8_t, DEQUE_SOURCE_SIZE> UT_dequeSource({11, 12, 13, 14, 15, 16});  

        static constexpr size_t DEQUE_SINK_SIZE = 9u;
        static_deque<uint32_t, DEQUE_SINK_SIZE> UT_dequeSink({33, 44 ,55});  

        auto insertPos = UT_dequeSink.insert(++(UT_dequeSink.begin()), UT_dequeSource.begin(), UT_dequeSource.end());

        std::vector<uint32_t> UT_correctLayout{33, 11, 12, 13, 14, 15 ,16, 44, 55};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_dequeSink.begin()));
        TEST_ASSERT_EQUAL(11, *insertPos);
    }

    { // Initializer list insert (5)
        static constexpr size_t DEQUE_SINK_SIZE = 9u;
        static_deque<uint32_t, DEQUE_SINK_SIZE> UT_dequeSink({33, 44 ,55});  

        auto insertPos = UT_dequeSink.insert((UT_dequeSink.begin() += 2), {11, 12, 13, 14, 15, 16});

        std::vector<uint32_t> UT_correctLayout{33, 44, 11, 12, 13, 14, 15 ,16, 55};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_dequeSink.begin()));
        TEST_ASSERT_EQUAL(11, *insertPos);
    }
}

void Test_Swap(void)
{
    static constexpr size_t DEQUE_SOURCE_SIZE = 8u;
    static_deque<uint8_t, DEQUE_SOURCE_SIZE> UT_deque_1({11, 12, 13, 14, 15, 16}); 

    static constexpr size_t DEQUE_SINK_SIZE = 7u;
    static_deque<uint8_t, DEQUE_SINK_SIZE> UT_deque_2{88, 99, 110, 120};

    UT_deque_2.swap(UT_deque_1);

    {
        std::vector<uint32_t> UT_correctLayout{11, 12, 13, 14, 15, 16};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque_2.begin()));
    }
    {
        std::vector<uint32_t> UT_correctLayout{88, 99, 110, 120};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque_1.begin()));
    }

    UT_deque_2.swap(UT_deque_1);

    {
        std::vector<uint32_t> UT_correctLayout{11, 12, 13, 14, 15, 16};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque_1.begin()));
    }
    {
        std::vector<uint32_t> UT_correctLayout{88, 99, 110, 120};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque_2.begin()));
    }

    static_deque<uint8_t>& UT_deque_3 = UT_deque_2;

    UT_deque_3.swap(UT_deque_1);
    {
        std::vector<uint32_t> UT_correctLayout{11, 12, 13, 14, 15, 16};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque_3.begin()));
    }
    {
        std::vector<uint32_t> UT_correctLayout{88, 99, 110, 120};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque_1.begin()));
    }
}

void Test_Clear(void)
{
    static constexpr size_t DEQUE_SIZE = 8u;
    static_deque<uint8_t, DEQUE_SIZE> UT_deque({11, 12, 13, 14, 15, 16}); 
    TEST_ASSERT_EQUAL(false, UT_deque.empty());
    TEST_ASSERT_EQUAL(false, UT_deque.full());
    TEST_ASSERT_EQUAL(6, UT_deque.size());

    UT_deque.clear();
    TEST_ASSERT_EQUAL(true, UT_deque.empty());
    TEST_ASSERT_EQUAL(false, UT_deque.full());
    TEST_ASSERT_EQUAL(0u, UT_deque.size());
}

void Test_Erase(void)
{
    { // (1)
        static constexpr size_t DEQUE_SIZE = 8u;
        static_deque<uint16_t, DEQUE_SIZE> UT_deque({11, 12, 13, 14, 15, 16});

        auto iter = UT_deque.erase(std::prev(UT_deque.end()));

        std::vector<uint32_t> UT_correctLayout{11, 12, 13, 14, 15};
        TEST_ASSERT_EQUAL(15 , *std::prev(iter));
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
        TEST_ASSERT_EQUAL(5, UT_deque.size());
    }
    {
        static constexpr size_t DEQUE_SIZE = 8u;
        static_deque<uint16_t, DEQUE_SIZE> UT_deque({11, 12, 13, 14, 15, 16});

        auto iter = UT_deque.erase(UT_deque.begin());

        std::vector<uint32_t> UT_correctLayout{12, 13, 14, 15, 16};
        TEST_ASSERT_EQUAL(12 , *iter);
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
        TEST_ASSERT_EQUAL(5, UT_deque.size());
    }

    { // (2)
        static constexpr size_t DEQUE_SIZE = 8u;
        static_deque<uint16_t, DEQUE_SIZE> UT_deque({11, 12, 13, 14, 15, 16});

        auto last = UT_deque.begin() += 3;
        auto iter = UT_deque.erase(UT_deque.begin(), last);
        
        std::vector<uint32_t> UT_correctLayout{14, 15, 16};
        TEST_ASSERT_EQUAL(14 , *iter);
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
        TEST_ASSERT_EQUAL(3, UT_deque.size());
    }
    {
        static constexpr size_t DEQUE_SIZE = 8u;
        static_deque<uint16_t, DEQUE_SIZE> UT_deque({11, 12, 13, 14, 15, 16});

        auto first = UT_deque.end() -= 4;
        auto iter = UT_deque.erase(first, UT_deque.end());

        std::vector<uint32_t> UT_correctLayout{11, 12};
        TEST_ASSERT_EQUAL(12 , *std::prev(iter));
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
        TEST_ASSERT_EQUAL(2, UT_deque.size());
    }
    {
        static constexpr size_t DEQUE_SIZE = 8u;
        static_deque<uint16_t, DEQUE_SIZE> UT_deque({11, 12, 13, 14, 15, 16});

        auto first = UT_deque.begin() += 1;
        auto last = UT_deque.end() -= 2;
        auto iter = UT_deque.erase(first, last);

        std::vector<uint32_t> UT_correctLayout{11, 15, 16};
        TEST_ASSERT_EQUAL(15 , *iter);
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
        TEST_ASSERT_EQUAL(3, UT_deque.size());
    }
    {
        static constexpr size_t DEQUE_SIZE = 8u;
        static_deque<uint16_t, DEQUE_SIZE> UT_deque({11, 12, 13, 14, 15, 16});

        auto first = UT_deque.end() -= 4;
        auto last = UT_deque.end() -= 4;
        auto iter = UT_deque.erase(first, last);

        std::vector<uint32_t> UT_correctLayout{11, 12, 13, 14, 15, 16};
        TEST_ASSERT_EQUAL(13, *iter);
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
        TEST_ASSERT_EQUAL(6, UT_deque.size());
    }
}

void Test_Resize(void)
{

    static constexpr size_t DEQUE_SIZE_SINK = 10u;
    static_deque<uint32_t, DEQUE_SIZE_SINK> UT_deque{111, 222, 333};

    UT_deque.resize(6);

    {
        std::vector<uint32_t> UT_correctLayout{111, 222, 333, 0, 0, 0};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
        TEST_ASSERT_EQUAL(6, UT_deque.size());
    }

    UT_deque.resize(10, 10);

    {
        std::vector<uint32_t> UT_correctLayout{111, 222, 333, 0, 0, 0, 10, 10, 10 ,10};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
        TEST_ASSERT_EQUAL(10, UT_deque.size());
    }

    UT_deque.resize(6);

    {
        std::vector<uint32_t> UT_correctLayout{111, 222, 333, 0, 0, 0};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
        TEST_ASSERT_EQUAL(6, UT_deque.size());
    }

    UT_deque.resize(6);

    {
        std::vector<uint32_t> UT_correctLayout{111, 222, 333, 0, 0, 0};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
        TEST_ASSERT_EQUAL(6, UT_deque.size());
    }

    UT_deque.resize(1);

    {
        std::vector<uint32_t> UT_correctLayout{111};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_deque.begin()));
        TEST_ASSERT_EQUAL(1, UT_deque.size());
    }
}

void Test_EmplaceBack(void)
{

    struct SomeData
    {
        SomeData(uint32_t _value, uint32_t* _ptr, uint32_t& _ref)
        : value(_value)
        , ptr(_ptr)
        , ref(_ref)
        {
        }

        uint32_t  value;
        uint32_t* ptr;
        uint32_t& ref;
    };

    static constexpr size_t DEQUE_SIZE = 8u;
    static_deque<SomeData, DEQUE_SIZE> UT_deque;

    uint32_t dataForPtr = 1234;
    uint32_t dataForRef = 5678;

    UT_deque.emplace_back(32, &dataForPtr, dataForRef);

    SomeData returnData = UT_deque.back();

    TEST_ASSERT_EQUAL(32, returnData.value);
    TEST_ASSERT_EQUAL(1234, *returnData.ptr);
    TEST_ASSERT_EQUAL(5678, returnData.ref);

}

void Test_EmplaceFront(void)
{
    struct SomeData
    {
        SomeData(uint32_t _value, uint32_t* _ptr, uint32_t& _ref)
        : value(_value)
        , ptr(_ptr)
        , ref(_ref)
        {
        }

        uint32_t  value;
        uint32_t* ptr;
        uint32_t& ref;
    };

    static constexpr size_t DEQUE_SIZE = 8u;
    static_deque<SomeData, DEQUE_SIZE> UT_deque;

    uint32_t dataForPtr = 1122;
    uint32_t dataForRef = 3344;

    UT_deque.emplace_front(55, &dataForPtr, dataForRef);

    SomeData returnData = UT_deque.front();

    TEST_ASSERT_EQUAL(55, returnData.value);
    TEST_ASSERT_EQUAL(1122, *returnData.ptr);
    TEST_ASSERT_EQUAL(3344, returnData.ref);

}

void Test_Emplace(void)
{
    struct SomeData
    {
        SomeData(uint32_t _value, uint32_t* _ptr)
        : value(_value)
        , ptr(_ptr)
        {
        }

        SomeData(SomeData const& _other)
        : value(_other.value)
        , ptr(_other.ptr)
        {
        }

        SomeData& operator=(SomeData&& _other)
        {
            ptr = _other.ptr;
            value = _other.value;
            return *this;
        }

        uint32_t  value;
        uint32_t* ptr;
    };
    uint32_t dataForPtr1 = 5566;
    uint32_t dataForPtr2 = 6655;
    uint32_t dataForPtr3 = 9933;

    static constexpr size_t DEQUE_SIZE = 8u;
    static_deque<SomeData, DEQUE_SIZE> UT_deque(5, SomeData(99, &dataForPtr1));

    {
        UT_deque.emplace((UT_deque.begin() += 1), 22, &dataForPtr2);
        TEST_ASSERT_EQUAL(6, UT_deque.size());
    }

    {
        UT_deque.emplace((UT_deque.begin() += 3), 33, &dataForPtr3);
        TEST_ASSERT_EQUAL(7, UT_deque.size());
    }

    TEST_ASSERT_EQUAL(99, UT_deque[0].value);
    TEST_ASSERT_EQUAL(5566, *(UT_deque[0].ptr));

    TEST_ASSERT_EQUAL(22, UT_deque[1].value);
    TEST_ASSERT_EQUAL(6655, *(UT_deque[1].ptr));

    TEST_ASSERT_EQUAL(33, UT_deque[3].value);
    TEST_ASSERT_EQUAL(9933, *(UT_deque[3].ptr));

    TEST_ASSERT_EQUAL(99, UT_deque[6].value);
    TEST_ASSERT_EQUAL(5566, *(UT_deque[6].ptr));
}

void Test_Assignments(void)
{
    { // Copy-assignment (to derived class) (1)
        static constexpr size_t DEQUE_SIZE = 8u;
        static_deque<uint32_t, DEQUE_SIZE> UT_dequeSource{99,88,77,66,55,44,33};

        static constexpr size_t DEQUE_SIZE_SINK = 7u;
        static_deque<uint32_t, DEQUE_SIZE_SINK> UT_dequeSink{111, 222, 333};
        TEST_ASSERT_EQUAL(3, UT_dequeSink.size());
        TEST_ASSERT_FALSE(UT_dequeSink.full());

        UT_dequeSink = UT_dequeSource;

        std::vector<uint32_t> UT_correctLayout{99, 88, 77, 66, 55, 44, 33};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_dequeSink.begin()));
        TEST_ASSERT_EQUAL(7, UT_dequeSink.size());
        TEST_ASSERT_TRUE(UT_dequeSink.full());
    }

    { // Move-assignment (to derived class) (2)
        static constexpr size_t DEQUE_SIZE = 8u;
        static_deque<uint32_t, DEQUE_SIZE> UT_dequeSource{99,88,77,66,55,44,33};

        static constexpr size_t DEQUE_SIZE_SINK = 7u;
        static_deque<uint32_t, DEQUE_SIZE_SINK> UT_dequeSink{111, 222, 333};
        TEST_ASSERT_EQUAL(3, UT_dequeSink.size());
        TEST_ASSERT_FALSE(UT_dequeSink.full());

        UT_dequeSink = std::move(UT_dequeSource);

        std::vector<uint32_t> UT_correctLayout{99, 88, 77, 66, 55, 44, 33};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_dequeSink.begin()));
        TEST_ASSERT_EQUAL(7, UT_dequeSink.size());
        TEST_ASSERT_TRUE(UT_dequeSink.full());
    }

    { // Initializer-List assignment (to derived class) (3)
        static constexpr size_t DEQUE_SIZE_SINK = 7u;
        static_deque<uint32_t, DEQUE_SIZE_SINK> UT_dequeSink{111, 222, 333};
        TEST_ASSERT_EQUAL(3, UT_dequeSink.size());
        TEST_ASSERT_FALSE(UT_dequeSink.full());

        UT_dequeSink = {88, 99, 11, 22, 33, 44};

        std::vector<uint32_t> UT_correctLayout{88, 99, 11, 22, 33, 44};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_dequeSink.begin()));
        TEST_ASSERT_EQUAL(6, UT_dequeSink.size());
        TEST_ASSERT_FALSE(UT_dequeSink.full());
    }

    { // Copy-assignment (to base class) (1)
        static constexpr size_t DEQUE_SIZE = 8u;
        static_deque<uint32_t, DEQUE_SIZE> UT_dequeSource{88,77,66,55,44,33,22};

        static constexpr size_t DEQUE_SIZE_SINK = 7u;
        static_deque<uint32_t, DEQUE_SIZE_SINK> UT_dequeSink{111, 222, 333};
        TEST_ASSERT_EQUAL(3, UT_dequeSink.size());
        TEST_ASSERT_FALSE(UT_dequeSink.full());

        static_deque<uint32_t>& UT_dequeSinkBase = UT_dequeSink; 
        UT_dequeSinkBase = UT_dequeSource;

        std::vector<uint32_t> UT_correctLayout{88, 77, 66, 55, 44, 33, 22};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_dequeSinkBase.begin()));
        TEST_ASSERT_EQUAL(7, UT_dequeSinkBase.size());
        TEST_ASSERT_TRUE(UT_dequeSinkBase.full());
    }

    { // Copy-assignment (to base class) (2)
        static constexpr size_t DEQUE_SIZE = 8u;
        static_deque<uint32_t, DEQUE_SIZE> UT_dequeSource{88,77,66,55,44,33,22};

        static constexpr size_t DEQUE_SIZE_SINK = 7u;
        static_deque<uint32_t, DEQUE_SIZE_SINK> UT_dequeSink{111, 222, 333};
        TEST_ASSERT_EQUAL(3, UT_dequeSink.size());
        TEST_ASSERT_FALSE(UT_dequeSink.full());

        static_deque<uint32_t>& UT_dequeSinkBase = UT_dequeSink; 
        UT_dequeSinkBase = std::move(UT_dequeSource);

        std::vector<uint32_t> UT_correctLayout{88, 77, 66, 55, 44, 33, 22};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_dequeSinkBase.begin()));
        TEST_ASSERT_EQUAL(7, UT_dequeSinkBase.size());
        TEST_ASSERT_TRUE(UT_dequeSinkBase.full());
    }

    { // Initializer-List assignment (to base class) (3)
        static constexpr size_t DEQUE_SIZE_SINK = 7u;
        static_deque<uint32_t, DEQUE_SIZE_SINK> UT_dequeSink{111, 222, 333};
        TEST_ASSERT_EQUAL(3, UT_dequeSink.size());
        TEST_ASSERT_FALSE(UT_dequeSink.full());

        static_deque<uint32_t>& UT_dequeSinkBase = UT_dequeSink; 
        UT_dequeSinkBase = {88, 99, 11, 22, 33, 44, 55};

        std::vector<uint32_t> UT_correctLayout{88, 99, 11, 22, 33, 44, 55};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_dequeSinkBase.begin()));
        TEST_ASSERT_EQUAL(7, UT_dequeSinkBase.size());
        TEST_ASSERT_TRUE(UT_dequeSinkBase.full());
    }
}

void Test_ContainerAdapter_Queue(void)
{
    static constexpr size_t DEQUE_SIZE = 8;
    std::queue<uint32_t, static_deque<uint32_t, DEQUE_SIZE>> UT_queue;

    UT_queue.push(2);
    UT_queue.push(3);
    UT_queue.push(4);
    UT_queue.push(5);
    UT_queue.push(6);
    UT_queue.push(7);
    UT_queue.push(8);

    for (size_t i = 2; i < 9; i++)
    {
        TEST_ASSERT_EQUAL(i, UT_queue.front());
        UT_queue.pop();
    }
}

void Test_ContainerAdapter_Stack(void)
{
    static constexpr size_t DEQUE_SIZE = 8;
    std::stack<uint32_t, static_deque<uint32_t, DEQUE_SIZE>> UT_stack;

    UT_stack.push(8);
    UT_stack.push(7);
    UT_stack.push(6);
    UT_stack.push(5);
    UT_stack.push(4);
    UT_stack.push(3);
    UT_stack.push(2);

    for (size_t i = 2; i < 9; i++)
    {
        TEST_ASSERT_EQUAL(i, UT_stack.top());
        UT_stack.pop();
    }
}

// Copied from https://github.com/microsoft/STL/blob/main/tests/tr1/tests/deque/test.cpp and adapted to unity
void Test_STLStandardTests()
{
    class Copyable_int { // wrap an integer, copyable
    public:
        Copyable_int(int v = 0) : val(v) { // construct from value
        }

        Copyable_int(const Copyable_int& x) : val(x.val) { // construct from copied value
        }

        Copyable_int& operator=(const Copyable_int& x) { // copy value
            val = x.val;
            return *this;
        }

        operator int() const { // convert to int
            return val;
        }

        bool operator==(const Copyable_int& x) const { // compare for equality
            return val == x.val;
        }

        bool operator!=(const Copyable_int& x) const { // compare for equality
            return val != x.val;
        }

        bool operator<(const Copyable_int& x) const { // compare for order
            return val < x.val;
        }

        int val;

        Copyable_int(Copyable_int&& x) : val(x.val) { // construct from moved value
            x.val = -1;
        }

        Copyable_int& operator=(Copyable_int&& x) { // move value
            val   = x.val;
            x.val = -1;
            return *this;
        }
    };

    class Movable_int : public Copyable_int { // wrap a move-only integer
    public:
        typedef Copyable_int Mybase;

        Movable_int(int v = 0) : Mybase(v) { // construct from value
        }

        Movable_int(int v1, int v2) : Mybase(v2 + (v1 << 4)) { // construct from two values
        }

        Movable_int(int v1, int v2, int v3) : Mybase(v3 + (v2 << 4) + (v1 << 8)) { // construct from three values
        }

        Movable_int(int v1, int v2, int v3, int v4)
            : Mybase(v4 + (v3 << 4) + (v2 << 8) + (v1 << 12)) { // construct from four values
        }

        Movable_int(int v1, int v2, int v3, int v4, int v5)
            : Mybase(v5 + (v4 << 4) + (v3 << 8) + (v2 << 12) + (v1 << 16)) { // construct from five values
        }

        Movable_int(Movable_int&& right) : Mybase(right.val) { // construct from moved value
            right.val = -1;
        }

        Movable_int& operator=(Movable_int&& right) { // assign from moved value
            if (this != &right) { // different, move it
                val       = right.val;
                right.val = -1;
            }
            return *this;
        }

        operator int() const { // convert to int
            return val;
        }

        bool operator==(const Movable_int& x) const { // compare for equality
            return val == x.val;
        }

        bool operator!=(const Movable_int& x) const { // compare for equality
            return val != x.val;
        }

        bool operator<(const Movable_int& x) const { // compare for order
            return val < x.val;
        }

        Movable_int(const Movable_int&)            = delete;
        Movable_int& operator=(const Movable_int&) = delete;
    };

    typedef static_deque<char, 50u> Mycont;

    char carr[] = "abc";

    Mycont v0;
    TEST_ASSERT_TRUE(v0.empty());
    TEST_ASSERT_EQUAL(v0.size(), 0);

    Mycont v1(5), v1a(6, 'x'), v1b(7, 'y');
    TEST_ASSERT_EQUAL(v1.size(), 5);
    TEST_ASSERT_EQUAL(v1.back(), '\0');
    TEST_ASSERT_EQUAL(v1a.size(), 6);
    TEST_ASSERT_EQUAL(v1a.back(), 'x');
    TEST_ASSERT_EQUAL(v1b.size(), 7);
    TEST_ASSERT_EQUAL(v1b.back(), 'y');

    Mycont v2(v1a);
    TEST_ASSERT_EQUAL(v2.size(), 6);
    TEST_ASSERT_EQUAL(v2.front(), 'x');

    Mycont v2a(v2);
    TEST_ASSERT_EQUAL(v2a.size(), 6);
    TEST_ASSERT_EQUAL(v2a.front(), 'x');

    Mycont v3(v1a.begin(), v1a.end());
    TEST_ASSERT_EQUAL(v3.size(), 6);
    TEST_ASSERT_EQUAL(v3.front(), 'x');

    const Mycont v4(v1a.begin(), v1a.end());
    TEST_ASSERT_EQUAL(v4.size(), 6);
    TEST_ASSERT_EQUAL(v4.front(), 'x');
    v0 = v4;
    TEST_ASSERT_EQUAL(v0.size(), 6);
    TEST_ASSERT_EQUAL(v0.front(), 'x');
    TEST_ASSERT_EQUAL(v0[0], 'x');
    TEST_ASSERT_EQUAL(v0.at(5), 'x');

    v0.resize(8);
    TEST_ASSERT_EQUAL(v0.size(), 8);
    TEST_ASSERT_EQUAL(v0.back(), '\0');
    v0.resize(10, 'z');
    TEST_ASSERT_EQUAL(v0.size(), 10);
    TEST_ASSERT_EQUAL(v0.back(), 'z');
    TEST_ASSERT_TRUE(v0.size() <= v0.max_size());

    {
        Mycont::iterator p_it(v0.begin());
        Mycont::const_iterator p_cit(v4.begin());
        Mycont::reverse_iterator p_rit(v0.rbegin());
        Mycont::const_reverse_iterator p_crit(v4.rbegin());
        TEST_ASSERT_EQUAL(*p_it, 'x');
        TEST_ASSERT_EQUAL(*--(p_it = v0.end()), 'z');
        TEST_ASSERT_EQUAL(*p_cit, 'x');
        TEST_ASSERT_EQUAL(*--(p_cit = v4.end()), 'x');
        TEST_ASSERT_EQUAL(*p_rit, 'z');
        TEST_ASSERT_EQUAL(*--(p_rit = v0.rend()), 'x');
        TEST_ASSERT_EQUAL(*p_crit, 'x');
        TEST_ASSERT_EQUAL(*--(p_crit = v4.rend()), 'x');

        // Not possible to default construct the const_iterator
        // Mycont::const_iterator p_it1 = Mycont::const_iterator();
        // Mycont::const_iterator p_it2 = Mycont::const_iterator();
        // CHECK(p_it1 == p_it2); // check null forward iterator comparisons
    }

    { // check const iterators generators
        Mycont::const_iterator p_it(v0.cbegin());
        Mycont::const_iterator p_cit(v4.cbegin());
        Mycont::const_reverse_iterator p_rit(v0.crbegin());
        Mycont::const_reverse_iterator p_crit(v4.crbegin());
        TEST_ASSERT_EQUAL(*p_it, 'x');
        TEST_ASSERT_EQUAL(*--(p_it = v0.cend()), 'z');
        TEST_ASSERT_EQUAL(*p_cit, 'x');
        TEST_ASSERT_EQUAL(*--(p_cit = v4.cend()), 'x');
        TEST_ASSERT_EQUAL(*p_rit, 'z');
        TEST_ASSERT_EQUAL(*--(p_rit = v0.crend()), 'x');
        TEST_ASSERT_EQUAL(*p_crit, 'x');
        TEST_ASSERT_EQUAL(*--(p_crit = v4.crend()), 'x');

        // Not possible to default construct the const_iterator
        //Mycont::const_iterator p_it1 = Mycont::const_iterator();
        //Mycont::const_iterator p_it2 = Mycont::const_iterator();
        //CHECK(p_it1 == p_it2); // check null forward iterator comparisons
    }


    TEST_ASSERT_EQUAL(v0.front(), 'x');
    TEST_ASSERT_EQUAL(v4.front(), 'x');
    v0.push_front('a');
    TEST_ASSERT_EQUAL(v0.front(), 'a');
    v0.pop_front();
    TEST_ASSERT_EQUAL(v0.front(), 'x');
    TEST_ASSERT_EQUAL(v4.front(), 'x');

    v0.push_back('a');
    TEST_ASSERT_EQUAL(v0.back(), 'a');
    v0.pop_back();
    TEST_ASSERT_EQUAL(v0.back(), 'z');
    TEST_ASSERT_EQUAL(v4.back(), 'x');

    {
        Mycont v5;
        v5.resize(10);
        TEST_ASSERT_EQUAL(v5.size(), 10);
        TEST_ASSERT_EQUAL(v5[9], 0);

        Mycont v6(20, 'x');
        Mycont v7(std::move(v6));
        TEST_ASSERT_EQUAL(v6.size(), 0);
        TEST_ASSERT_EQUAL(v7.size(), 20);

        Mycont v6a(20, 'x');
        Mycont v7a(std::move(v6a));
        TEST_ASSERT_EQUAL(v6a.size(), 0);
        TEST_ASSERT_EQUAL(v7a.size(), 20);

        Mycont v8;
        v8 = std::move(v7);
        TEST_ASSERT_EQUAL(v7.size(), 0);
        TEST_ASSERT_EQUAL(v8.size(), 20);

        Mycont v8a(std::move(v8));
        TEST_ASSERT_EQUAL(v8.size(), 0);
        TEST_ASSERT_EQUAL(v8a.size(), 20);

        static_deque<Movable_int, 50> v9;
        v9.resize(10);
        TEST_ASSERT_EQUAL(v9.size(), 10);
        TEST_ASSERT_EQUAL(v9[9].val, 0);

        static_deque<Movable_int, 50> v10;
        Movable_int mi1(1);
        v10.push_back(std::move(mi1));
        TEST_ASSERT_EQUAL(mi1.val, -1);
        TEST_ASSERT_EQUAL(v10[0].val, 1);

        Movable_int mi2(2);
        v10.push_front(std::move(mi2));
        TEST_ASSERT_EQUAL(mi2.val, -1);
        TEST_ASSERT_EQUAL(v10[0].val, 2);

        Movable_int mi3(3);
        v10.insert(v10.begin(), std::move(mi3));
        TEST_ASSERT_EQUAL(mi3.val, -1);
        TEST_ASSERT_EQUAL(v10[0].val, 3);

        v10.emplace_front();
        TEST_ASSERT_EQUAL(v10[0].val, 0);
        v10.emplace_front(2);
        TEST_ASSERT_EQUAL(v10[0].val, 2);
        v10.emplace_front(3, 2);
        TEST_ASSERT_EQUAL(v10[0].val, 0x32);
        v10.emplace_front(4, 3, 2);
        TEST_ASSERT_EQUAL(v10[0].val, 0x432);
        v10.emplace_front(5, 4, 3, 2);
        TEST_ASSERT_EQUAL(v10[0].val, 0x5432);
        v10.emplace_front(6, 5, 4, 3, 2);
        TEST_ASSERT_EQUAL(v10[0].val, 0x65432);

        v10.emplace_back();
        TEST_ASSERT_EQUAL(v10.back().val, 0);
        v10.emplace_back(2);
        TEST_ASSERT_EQUAL(v10.back().val, 2);
        v10.emplace_back(3, 2);
        TEST_ASSERT_EQUAL(v10.back().val, 0x32);
        v10.emplace_back(4, 3, 2);
        TEST_ASSERT_EQUAL(v10.back().val, 0x432);
        v10.emplace_back(5, 4, 3, 2);
        TEST_ASSERT_EQUAL(v10.back().val, 0x5432);
        v10.emplace_back(6, 5, 4, 3, 2);
        TEST_ASSERT_EQUAL(v10.back().val, 0x65432);

        v10.emplace(v10.begin() + 1);
        TEST_ASSERT_EQUAL(v10[1].val, 0);
        v10.emplace(v10.begin() + 1, 2);
        TEST_ASSERT_EQUAL(v10[1].val, 2);
        v10.emplace(v10.begin() + 1, 3, 2);
        TEST_ASSERT_EQUAL(v10[1].val, 0x32);
        v10.emplace(v10.begin() + 1, 4, 3, 2);
        TEST_ASSERT_EQUAL(v10[1].val, 0x432);
        v10.emplace(v10.begin() + 1, 5, 4, 3, 2);
        TEST_ASSERT_EQUAL(v10[1].val, 0x5432);
        v10.emplace(v10.begin() + 1, 6, 5, 4, 3, 2);
        TEST_ASSERT_EQUAL(v10[1].val, 0x65432);
    }

    { // check for lvalue stealing
        static_deque<Copyable_int, 50> v11;
        Copyable_int ci1(1);
        v11.push_back(ci1);
        TEST_ASSERT_EQUAL(ci1.val, 1);
        TEST_ASSERT_EQUAL(v11[0].val, 1);

        Copyable_int ci2(2);
        v11.push_front(ci2);
        TEST_ASSERT_EQUAL(ci2.val, 2);
        TEST_ASSERT_EQUAL(v11[0].val, 2);

        Copyable_int ci3(3);
        v11.insert(v11.begin(), ci3);
        TEST_ASSERT_EQUAL(ci3.val, 3);
        TEST_ASSERT_EQUAL(v11[0].val, 3);
        TEST_ASSERT_EQUAL(v11[1].val, 2);

        static_deque<Copyable_int, 50> v12(v11);
        TEST_ASSERT_TRUE(v11 == v12);
        v11 = v12;
        TEST_ASSERT_TRUE(v11 == v12);

        static_deque<Copyable_int, 50> v13(std::make_move_iterator(v11.begin()), std::make_move_iterator(v11.end()));
        TEST_ASSERT_EQUAL(v13.front().val, 3);
        TEST_ASSERT_EQUAL(v11.front().val, -1);
    }

    v0.assign(v4.begin(), v4.end());
    TEST_ASSERT_EQUAL(v0.size(), v4.size());
    TEST_ASSERT_EQUAL(v0.front(), v4.front());
    v0.assign(4, 'w');
    TEST_ASSERT_EQUAL(v0.size(), 4);
    TEST_ASSERT_EQUAL(v0.front(), 'w');
    TEST_ASSERT_EQUAL(*v0.insert(v0.begin(), 'a'), 'a');
    TEST_ASSERT_EQUAL(v0.front(), 'a');
    TEST_ASSERT_EQUAL(*++v0.begin(), 'w');
    TEST_ASSERT_EQUAL(*v0.insert(v0.begin(), 2, 'b'), 'b');
    TEST_ASSERT_EQUAL(v0.front(), 'b');
    TEST_ASSERT_EQUAL(*++v0.begin(), 'b');
    TEST_ASSERT_EQUAL(*++ ++v0.begin(), 'a');
    TEST_ASSERT_EQUAL(*v0.insert(v0.end(), v4.begin(), v4.end()), *v4.begin());
    TEST_ASSERT_EQUAL(v0.back(), v4.back());
    TEST_ASSERT_EQUAL(*v0.insert(v0.end(), carr, carr + 3), *carr);
    TEST_ASSERT_EQUAL(v0.back(), 'c');
    v0.erase(v0.begin());
    TEST_ASSERT_EQUAL(v0.front(), 'b');
    TEST_ASSERT_EQUAL(*++v0.begin(), 'a');
    v0.erase(v0.begin(), ++v0.begin());
    TEST_ASSERT_EQUAL(v0.front(), 'a');

    // Does not make any sens for a static_deque
    // { // test added C++11 functionality
    //     Mycont v0x;
    //     v0x.push_back('a');
    //     v0x.shrink_to_fit();
    //     CHECK_INT(v0x.front(), 'a');
    // }

    {
        std::initializer_list<char> init{'a', 'b', 'c'};
        Mycont v11(init);
        TEST_ASSERT_EQUAL(v11.size(), 3);
        TEST_ASSERT_EQUAL(v11[2], 'c');

        v11.clear();
        v11 = init;
        TEST_ASSERT_EQUAL(v11.size(), 3);
        TEST_ASSERT_EQUAL(v11[2], 'c');

        TEST_ASSERT_EQUAL(*v11.insert(v11.begin() + 1, init), *init.begin());
        TEST_ASSERT_EQUAL(v11.size(), 6);
        TEST_ASSERT_EQUAL(v11[2], 'b');

        v11.assign(init);
        TEST_ASSERT_EQUAL(v11.size(), 3);
        TEST_ASSERT_EQUAL(v11[2], 'c');
    }

    v0.clear();
    TEST_ASSERT_TRUE(v0.empty());
    v0.swap(v1);
    TEST_ASSERT_TRUE(!v0.empty());
    TEST_ASSERT_TRUE(v1.empty());
    std::swap(v0, v1);
    TEST_ASSERT_TRUE(v0.empty());
    TEST_ASSERT_TRUE(!v1.empty());
    TEST_ASSERT_TRUE(v1 == v1);
    TEST_ASSERT_TRUE(v0 < v1);
    TEST_ASSERT_TRUE(v0 != v1);
    TEST_ASSERT_TRUE(v1 > v0);
    TEST_ASSERT_TRUE(v0 <= v1);
    TEST_ASSERT_TRUE(v1 >= v0);
}

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(Test_Constructors);
    RUN_TEST(Test_LValue_PushBack);
    RUN_TEST(Test_LValue_PushFront);
    RUN_TEST(Test_RValue_PushBack); 
    RUN_TEST(Test_RValue_PushFront);
    RUN_TEST(Test_PopFront_PopBack);
    RUN_TEST(Test_ElementAccess);
    RUN_TEST(Test_Insert);
    RUN_TEST(Test_Swap);
    RUN_TEST(Test_Clear);
    RUN_TEST(Test_Erase);
    RUN_TEST(Test_Resize);
    RUN_TEST(Test_EmplaceBack);
    RUN_TEST(Test_EmplaceFront);
    RUN_TEST(Test_Emplace);
    RUN_TEST(Test_Assignments);
    RUN_TEST(Test_ContainerAdapter_Queue);
    RUN_TEST(Test_ContainerAdapter_Stack);
    // Copied from https://github.com/microsoft/STL/blob/main/tests/tr1/tests/deque/test.cpp and adapted to unity
    RUN_TEST(Test_STLStandardTests);
    return UNITY_END();

    return 0;
}
