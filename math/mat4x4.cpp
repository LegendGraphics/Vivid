
#include "math/mat4x4.h"

Mat4x4::Mat4x4()
{
    for (int i = 0; i < 4; ++ i)
        for (int j = 0; j < 4; ++ j)
            _m[i][j] = 0;
}

Mat4x4::Mat4x4(const Mat4x4& m)
{
    for (int i = 0; i < 4; ++ i)
        for (int j = 0; j < 4; ++ j)
            _m[i][j] = m(i, j);
}

Mat4x4::~Mat4x4(){}

Mat4x4& Mat4x4::operator=(const Mat4x4& m)
{
    for (int i = 0; i < 4; ++ i)
        for (int j = 0; j < 4; ++ j)
            _m[i][j] = m(i, j);
    return *this;
}
