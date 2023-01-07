#include "../src/LIB_StaticDeque.hpp"
#include "unity/unity.h"

#include <vector>

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
}

void Test_Insert(void)
{
    { // (1)
        uint8_t value = 111;
        static constexpr size_t DEQUE_SINK_SIZE = 8u;
        static_deque<uint8_t, DEQUE_SINK_SIZE> UT_dequeSink({66, 77, 88, 99, 11, 22}); 

        auto insertPos = UT_dequeSink.insert((UT_dequeSink.begin() += 3), value);   

        std::vector<uint32_t> UT_correctLayout{66, 77, 88, 111, 99, 11, 22};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_dequeSink.begin()));
        TEST_ASSERT_EQUAL(111, *insertPos);    
    }

    { // (2)
    }

    { // (3)
        static constexpr size_t DEQUE_SINK_SIZE = 10u;
        static_deque<uint8_t, DEQUE_SINK_SIZE> UT_dequeSink({66, 77, 88, 99, 11, 22}); 

        auto insertPos = UT_dequeSink.insert((UT_dequeSink.begin() += 3), static_cast<static_deque<uint8_t, DEQUE_SINK_SIZE>::size_type>(4), 111);   

        std::vector<uint32_t> UT_correctLayout{66, 77, 88, 111, 111, 111, 111, 99, 11, 22};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_dequeSink.begin()));
        TEST_ASSERT_EQUAL(111, *insertPos);    
    }

    { // (4)
        static constexpr size_t DEQUE_SOURCE_SIZE = 6u;
        static_deque<uint8_t, DEQUE_SOURCE_SIZE> UT_dequeSource({11, 12, 13, 14, 15, 16});  

        static constexpr size_t DEQUE_SINK_SIZE = 9u;
        static_deque<uint32_t, DEQUE_SINK_SIZE> UT_dequeSink({33, 44 ,55});  

        auto insertPos = UT_dequeSink.insert(++(UT_dequeSink.begin()), UT_dequeSource.begin(), UT_dequeSource.end());

        std::vector<uint32_t> UT_correctLayout{33, 11, 12, 13, 14, 15 ,16, 44, 55};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_dequeSink.begin()));
        TEST_ASSERT_EQUAL(11, *insertPos);
    }

    { // (5)
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
    static_deque<uint8_t, DEQUE_SOURCE_SIZE> UT_dequeSource({11, 12, 13, 14, 15, 16}); 

    static constexpr size_t DEQUE_SINK_SIZE = 8u;
    static_deque<uint8_t, DEQUE_SINK_SIZE> UT_dequeSink{88, 99, 110, 120};
    UT_dequeSink.swap(UT_dequeSource);

    {
        std::vector<uint32_t> UT_correctLayout{11, 12, 13, 14, 15, 16};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_dequeSink.begin()));
    }
    {
        std::vector<uint32_t> UT_correctLayout{88, 99, 110, 120};
        TEST_ASSERT_TRUE(std::equal(UT_correctLayout.begin(), UT_correctLayout.end(), UT_dequeSource.begin()));
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
    { // Copy-assignment (to derived class)
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

    { // Initializer-List assignment (to derived class)
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

    { // Copy-assignment (to base class)
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

    { // Initializer-List assignment (to base class)
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
    return UNITY_END();

    return 0;
}
