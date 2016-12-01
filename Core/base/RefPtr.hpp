#ifndef COMMON_REFPTR_HPP
#define COMMON_REFPTR_HPP

// non-template parts of RefPtr
class RefPtrBase
{

};


template <typename T>
class RefPtr
{
public:
    RefPtr(T* ptr = 0);
    RefPtr(const RefPtr<T>& r);
    RefPtr& operator=(T* ptr);
    RefPtr& operator=(const RefPtr<T>& r);
    ~RefPtr();

    T* operator->();
    const T* operator->() const;
    operator bool() const;
    T* get();
    const T* get() const;

private:
    T* _ptr;
};

template <typename T>
RefPtr<T>::RefPtr(T* ptr)
{
    _ptr = ptr;
    if (_ptr) _ptr->retain();
}

template <typename T>
RefPtr<T>::RefPtr(const RefPtr<T>& r)
{
    _ptr = r._ptr;
    if (_ptr) _ptr->retain();
}

template <typename T>
RefPtr<T>& RefPtr<T>::operator=(T* ptr)
{
    if (ptr) ptr->retain();
    if (_ptr && (_ptr->release(), _ptr->getReferenceCount() == 0))
        delete _ptr;
    _ptr = ptr;
    return *this;
}

template <typename T>
RefPtr<T>& RefPtr<T>::operator=(const RefPtr<T>& r)
{
    if (r._ptr) r._ptr->retain();
    if (_ptr && (_ptr->release(), _ptr->getReferenceCount() == 0))
        delete _ptr;
    _ptr = r._ptr;
    return *this;
}

template <typename T>
RefPtr<T>::~RefPtr()
{
    if (_ptr && (_ptr->release(), _ptr->getReferenceCount() == 0))
        delete _ptr;
}

template <typename T>
T* RefPtr<T>::operator->()
{
    return _ptr;
}

template <typename T>
const T* RefPtr<T>::operator->() const
{
    return _ptr;
}

template <typename T>
T* RefPtr<T>::get()
{
    return _ptr;
}

template <typename T>
const T* RefPtr<T>::get() const
{
    return _ptr;
}

template <typename T>
RefPtr<T>::operator bool() const
{
    return _ptr != NULL;
}

#endif // COMMON_REFPTR_HPP