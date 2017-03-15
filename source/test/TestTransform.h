
#include "io/Logger.h"
#include "math/Vector3.h"
#include "math/Transform.h"

using namespace te;
int main()
{
    cLog << "fanxiaochen";

    Vector3 v(1, 2, 3);
    cLog << v;

    Matrix trans = Matrix::translate(1, 2, 4);
    cLog << trans;

    Matrix scale = Matrix::scale(1, 2, 4);
    cLog << scale;

    Quaternion q(Vector3(60, 0, 0));
    cLog << q;

    Matrix rotate = Matrix::rotate(60, 0, 0);
    cLog << rotate;

    return 0;
}