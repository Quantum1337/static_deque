# stds::deque
A static implementation of [std::deque](https://en.cppreference.com/w/cpp/container/deque) with
focus on embedded devices where the usage of a heap is not allowed

**How to use**

You can define a empty stds::deque as follow:

```c++
constexpr size_t MAX_SIZE = 10;
stds::deque<uint32_t, MAX_SIZE> myDeque();
```

Pass elements to it:

```c++
myDeque.push_back(10);
myDeque.push_front(20);
```

You can assign the stds::deque to a reference which is independent 
from the maximum size and use it as usual

```c++
stds::deque<uint32_t>& myDequeRef = myDeque;
myDequeRef.push_front(30);
```

**Test Coverage**
lines: 100.0% (347 out of 347)
functions: 97.9% (825 out of 843)
branches: 88.4% (84 out of 95)

## LICENSE

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
