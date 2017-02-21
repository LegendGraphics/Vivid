
#include "common/Camera.h"

namespace te
{
    void Camera::setCameraMode(CameraMode mode)
    {
        _mode = mode;
    }

    void Camera::setViewTransform(const Vector3& eye, const Vector3& center, const Vector3& up)
    {
        /*Mat4x4 mat;
        Vec3 z_axis = center - eye;
        z_axis = z_axis.normalize();

        Vec3 x_axis = z_axis.cross(up);
        x_axis = x_axis.normalize();

        Vec3 y_axis = x_axis.cross(z_axis);
        y_axis = y_axis.normalize();


        mat(0, 0) = x_axis.x();
        mat(0, 1) = x_axis.y();
        mat(0, 2) = x_axis.z();
        mat(0, 3) = -x_axis.dot(eye);

        mat(1, 0) = y_axis.x();
        mat(1, 1) = y_axis.y();
        mat(1, 2) = y_axis.z();
        mat(1, 3) = -y_axis.dot(eye);

        mat(2, 0) = z_axis.x();
        mat(2, 1) = z_axis.y();
        mat(2, 2) = z_axis.z();
        mat(2, 3) = -z_axis.dot(eye);

        mat(3, 3) = 1;

        return Transform(mat);*/
    }

    void Camera::setViewTransform(float fov, float aspect, float znear, float zfar)
    {

    }

    void Camera::setOrthoTransform(float left, float right, float bottom, float top, float znear /* = -1.0 */, float zfar /* = 1.0 */)
    {
        /*Mat4x4 mat;
        mat(0, 0) = 2 / (right - left);
        mat(1, 1) = 2 / (top - bottom);
        mat(2, 2) = -2 / (zfar - znear);
        mat(0, 3) = -(right + left) / (right - left);
        mat(1, 3) = -(top + bottom) / (top - bottom);
        mat(2, 3) = -(zfar + znear) / (zfar - znear);
        mat(3, 3) = 1;

        return Transform(mat);*/
    }
}