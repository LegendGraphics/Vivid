#include <iostream>

class Allocator
{
public:
    explicit Allocator()
    {
        std::cout << "Allocator construction" << std::endl;
    }

    ~Allocator()
    {
        std::cout << "Allocator destruction" << std::endl;
    }

    /// operator new, with debug line info
    void* operator new(size_t sz, const char* file, int line)
    {
        std::cout << "call Allocator::operator new on file:" << file << "  line:" << line << std::endl;
        void* ptr = malloc(sz);
        return ptr;
    }

    void* operator new(size_t sz)
    {
        void* ptr = malloc(sz);
        return ptr;
    }

    void* operator new(size_t sz, void* ptr)
    {
        (void)sz;
        return ptr;
    }

    void operator delete(void* ptr)
    {
        free(ptr);
    }
};

class Buffer : public Allocator
{
protected:
    size_t _width;
    size_t _height;
    size_t _depth;

public:
    Buffer(size_t w, size_t h, size_t d)
        :_width(w),
        _height(h),
        _depth(d)
    {}
};

int main()
{
    // the two ways are the same

    // the actual process
    Buffer* p = (Buffer*)::operator new(sizeof(Buffer)); // malloc
    new(p) Buffer(1, 2, 3); // construction
    p->~Buffer();   // destruction
    ::operator delete(p); // free
    std::cout << std::endl;

    // the process we write
    Buffer* t = new Buffer(1, 2, 3);
    delete t;
    std::cout << std::endl;

    // with debug info from windows macros
    Buffer* d = new(__FILE__, __LINE__) Buffer(1, 2, 3);
    delete d;
    std::cout << std::endl;

    getchar();
    return 0;
}