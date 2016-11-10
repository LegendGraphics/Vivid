#ifndef COMMON_REF_H
#define COMMON_REF_H

class Ref
{
public:
    Ref();
	void retain();
	void release();
	
	unsigned int getReferenceCount();

protected:
	virtual ~Ref();

private:
	unsigned int _reference_count;
};

#endif // COMMON_REF_H