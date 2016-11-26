#ifndef COMMON_REF_H
#define COMMON_REF_H

/// Ref` is a base class for an object whose lifetime is managed by a ref.

/// See \ref topic_refs for details. This class is often used in 
/// conjunction with `RefPtr`. When the ref count on the 
/// object reaches under zero, it will be deleted.
class Ref
{
    // We don't want those guys....
    // ... unless we
    // a. find a way of copying interfaces...
    // b. handle refs
    Ref(const Ref& src);
    Ref& operator=(const Ref& rhs);

protected:
    Ref();
    virtual ~Ref() = 0;

public:
	void retain();
	void release();
	
	unsigned int getReferenceCount();

private:
	unsigned int _reference_count;
};

#endif // COMMON_REF_H