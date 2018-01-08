#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <vector>
template<class T>
class Vector
{
    friend bool operator==(Vector<T>& op1, Vector<T>& op2);
    friend bool operator!=(Vector<T>& op1, Vector<T>& op2);
    friend bool operator<=(Vector<T>& op1, Vector<T>& op2);
    friend bool operator>=(Vector<T>& op1, Vector<T>& op2);
    friend bool operator<(Vector<T>& op1, Vector<T>& op2);
    friend bool operator>(Vector<T>& op1, Vector<T>& op2);
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;
    using size_type = size_t;

private:
    size_type reserved_size;
    size_type vector_size;
    T* storage;
    void realocate();

public:

    Vector():reserved_size(0),vector_size(0)
    {
        storage = new T[reserved_size];
    };
    Vector(std::initializer_list<T> _list)
    {
        vector_size = 0;
        reserved_size = _list.size()*2;
        storage = new T[reserved_size];

        for(typename std::initializer_list<T>::iterator i = _list.begin(); i != _list.end(); ++i )
        {

            push_back(*i);
        }
    }

    Vector(const Vector& _vector)
    {
        storage = new T[_vector.reserved_size];

        for(iterator i = this->begin(), j = _vector.begin();
        i < this->end(); ++i, ++j)
        {
            *i = *j;
        }
    }
    ~Vector()
    {
        delete [] storage;
    }
    /** Element access **/

    reference at(size_type pos);
    reference operator[](size_type pos);
    reference front();
    reference back();
    T* data()noexcept;

    /** Iterators **/
    iterator begin();
    const_iterator cbegin()const noexcept;
    iterator end();
    const_iterator cend()const noexcept;

    /**Capacity**/
    bool empty()const;
    size_type size()const;
    size_type max_size()const;
    size_type capacity()const noexcept;

    /**Modifiers**/
    void push_back(const T& value);
    void pop_back();
    void clear();
    void swap(T& value1, T& value2);
};

template<class T>
typename Vector<T>::reference Vector<T>::at(size_type pos)
{
    if(pos >= vector_size)
        throw std::out_of_range("'Pos' should be < size of vector!");
    return storage[pos];
}

template<class T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos)
{
    return storage[pos];
}

template<class T>
typename Vector<T>::reference Vector<T>::front()
{
    return storage[0];
}

template<class T>
typename Vector<T>::reference Vector<T>::back()
{
    return storage[vector_size-1];
}

template<class T>
T* Vector<T>::data() noexcept
{
    return storage;
}

template<class T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return storage;
}

template<class T>
typename Vector<T>::const_iterator Vector<T>::cbegin()const noexcept
{
    return storage;
}

template<class T>
typename Vector<T>::iterator Vector<T>::end()
{
    return storage + vector_size;
}

template<class T>
typename Vector<T>::const_iterator Vector<T>::cend()const noexcept
{
    return storage + vector_size;
}

template<class T>
bool Vector<T>::empty()const
{
    return vector_size == 0;
}

template<class T>
typename Vector<T>::size_type Vector<T>::size()const
{
    return vector_size;
}

template<class T>
typename Vector<T>::size_type Vector<T>::max_size()const
{
    return 18446744073709551615;
}

template<class T>
typename Vector<T>::size_type Vector<T>::capacity()const noexcept
{
    return reserved_size;
}

template<class T>
bool operator==(Vector<T>& op1, Vector<T>& op2)
{
    if(op1.size()!=op2.size())
        return false;
    for(typename Vector<T>::iterator i = op1.begin(),j = op2.begin();
            i < op1.end() || j < op2.end(); ++i, ++j)
    {
        if(*i != *j)
        {
            return false;
        }
    }
    return true;
}

template<class T>
bool operator!=(Vector<T>& op1, Vector<T>& op2)
{
    return !(op1.storage == op2.storage);
}

template<class T>
bool operator<(Vector<T>& op1, Vector<T>& op2)
{

}

template<class T>
bool operator<=(Vector<T>& op1, Vector<T>& op2)
{

}

template<class T>
bool operator>=(Vector<T>& op1, Vector<T>& op2)
{

}

template<class T>
void Vector<T>::swap(T& value1, T& value2)
{
    T temp = value1;
    value1 = value2;
    value2 = temp;
}

template<class T>
void Vector<T>::realocate()
{
    T* temp = new T[reserved_size];
    for(int i = 0; i < vector_size; ++i)
    {
        temp[i] = storage[i];
    }
    delete [] storage;
    storage = temp;
}

template<class T>
void Vector<T>::push_back(const T& value)
{
    if(vector_size==reserved_size)
    {
        reserved_size *=2;
        realocate();
    }
    storage[vector_size++] = value;
}

template<class T>
void Vector<T>::pop_back()
{
    storage[--vector_size].~T();

}

template<class T>
void Vector<T>::clear()
{
    if(vector_size > 0)
        --vector_size;
    for(; vector_size!=0; --vector_size)
        storage[vector_size].~T();
}


class A
{
    public:
    ~A()
    {
        std::cout<<"deleted"<<std::endl;
    };
};

int main()
{
    Vector<A> v{A(),A(),A()};
    return 0;
}
