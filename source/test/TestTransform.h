
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

    Quaternion q(Vector3(0, 0, 60));
    cLog << q;

    Matrix rotate_z = Matrix::rotate(0, 0, 60);
    Matrix rotate_y = Matrix::rotate(0, 60, 0);
    Matrix rotate_x = Matrix::rotate(60, 0, 0);
    cLog << rotate_z;
    cLog << rotate_y;
    cLog << rotate_x;

    Matrix pers = Matrix::perspective(60, 3 / 4, 10, 1000);
    Matrix orth = Matrix::ortho(-50, 100, -100, 50, 5, -50);
    cLog << orth;


    return 0;
}