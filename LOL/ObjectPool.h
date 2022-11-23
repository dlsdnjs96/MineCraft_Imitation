#pragma once
#include "stdafx.h"


template <typename T>
class ObjectPool
{
private:
    std::queue<T*> pool;

public:
    T* CreateObj();
    void Initialize(int count);
    T* GetObj();
    void ReturnObj(T* t);
};

template <typename T>
inline T* ObjectPool<T>::CreateObj()
{
    return new T;
}

template <typename T>
inline void ObjectPool<T>::Initialize(int count)
{
    for (int i = 0; i < count; i++)
        pool.push(new T);
}

template <typename T>
inline T* ObjectPool<T>::GetObj()
{
    if (pool.empty())
        return new T;
    else {
        T* temp = pool.front();
        pool.pop();
        return temp;
    }
}

template <typename T>
inline void ObjectPool<T>::ReturnObj(T* t)
{
    pool.push(t);
}
