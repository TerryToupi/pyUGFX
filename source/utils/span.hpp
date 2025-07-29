#ifndef __SPAN_HPP__
#define __SPAN_HPP__

#include <initializer_list>
#include <stdexcept>

namespace utils
{
    template <typename T>
    class Span {
    public:
        Span() 
            : m_Data(nullptr), m_Size(0) {}

        Span(const T* data, size_t size) 
            : m_Data(data), m_Size(size) {}

        template <size_t N>
        Span(const T(&arr)[N]) 
            : m_Data(arr), m_Size(N) {}

        Span(const std::initializer_list<T>& list)
            : m_Data(list.begin()), m_Size(list.size()) {}

        const T* data() const { return m_Data; }
        size_t size() const { return m_Size; }

        const T* begin() const { return m_Data; }
        const T* end() const { return m_Data + m_Size; }

        const T& at(size_t idx) const { 
            if (idx >= m_Size) {
                throw std::out_of_range("Span out of Range!");
            }
            return m_Data[idx];
        } 

        const T& operator[](size_t idx) const {
            return at(idx);
        }

    private:
        const T* m_Data = nullptr;
        size_t m_Size = 0;
    };
}

#endif