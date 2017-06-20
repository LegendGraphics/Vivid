
#include "io/Logger.h"
#include "math/Vector3.h"
#include "math/Transform.h"

using namespace te;
int main()
{
    cLog << "fanxiaochen";

    Vector3 v(1, 2, 3);
    cLog << v;

    // test translation
    Matrix trans = Matrix::translate(1, 2, 4);
    cLog << trans;

    // test scale
    Matrix scale = Matrix::scale(1, 2, 4);
    cLog << scale;

    // test quaternion
    Quaternion q(Vector3(0, 0, 60));
    cLog << q;

    // test rotation based on quaternion
    Matrix rotate_z = Matrix::rotate(0, 0, 60);
    Matrix rotate_y = Matrix::rotate(0, 60, 0);
    Matrix rotate_x = Matrix::rotate(60, 0, 0);
    cLog << rotate_z;
    cLog << rotate_y;
    cLog << rotate_x;

    // test ortho
    Vector4 o(-50, -100, -50, 1);
    Matrix orth = Matrix::ortho(-50, 100, -100, 50, -5, -50);
    cLog << orth;
    cLog << orth * o;

    // test perspective
    Matrix pers = Matrix::perspective(60, 4.0 / 3, -10, -1000);
    cLog << pers;
    Vector4 p(40 / (sqrt(3)*3.0), 10.0 / sqrt(3), -10, 1);
    cLog << pers * p;

    // test lookat
    Vector3 eye(10, 0, 0), center(0, 0, 0), up(0, 0, 1);
    Vector4 c(0, 0, 0, 1);
    Matrix lookat = Matrix::lookAt(eye, center, up);
    cLog << lookat;
    cLog << lookat * c;

    return 0;
}