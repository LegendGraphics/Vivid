
#include <vector>
#include "math/Vector3.h"
#include "io/logger.h"

struct Vector
{
public:
    Vector(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    virtual ~Vector() {}

    float x, y, z;
};

using namespace te;
int main()
{
    Vector3 a(1, 2, 3), b(4, 5, 6), c(7, 8, 9);
    //Vector a(1, 2, 3), b(4, 5, 6), c(7, 8, 9);
    std::vector<Vector3> test = { a,b,c };
    float* s = &test[0].x;
    for (int i = 0; i < 10; i++)
        std::cout << s[i] << std::endl;
    return 0;
}