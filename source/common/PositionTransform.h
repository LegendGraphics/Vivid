//#ifndef COMMON_TRANSFORM_H
//#define COMMON_TRANSFORM_H
//
//#include "common/Component.h"
//#include "math/Vector3.h"
//#include "math/Quaternion.h"
//
//namespace te
//{
//    class Transform : public Component
//    {
//    public:
//        enum class TransformRef
//        {
//            RELATIVE_TO_PARENT,
//            RELATIVE_TO_WORLD
//        };
//
//    public:
//        Transform();
//        Transform(const Vector3& position);
//        Transform(float x, float y, float z);
//        virtual ~Transform();
//
//        virtual void init();
//        virtual void update();
//
//        void translate(const Vector3& translation);
//        void translate(float x, float y, float z);
//
//        void rotate(const Vector3& euler_angles);
//        void rotate(float rx, float ry, float rz);
//
//        void scale(const Vector3& scale);
//        void scale(float sx, float sy, float sz);
//
//        // using local as example
//        // but I need to keep both local and world transform data
//        const Vector3& getLocalPosition();
//        const Vector3& getLocalScale();
//        const Vector3& getLocalEulerAngles();
//        const Quaternion& getLocalRotation();
//
//        const Vector3& getWorldPosition();
//        const Vector3& getWorldScale();
//        const Vector3& getWorldEulerAngles();
//        const Quaternion& getWorldRotation();
//
//        Matrix getTranslateMatrix(const TransformRef& tr);
//        Matrix getScaleMatrix(const TransformRef& tr);
//        Matrix getRotateMatrix(const TransformRef& tr);
//        Matrix getInnerMatrix(const TransformRef& tr);
//
//    protected:
//        Vector3 _local_pos;
//        Vector3 _local_scale;
//        Vector3 _local_euler_angles;
//        Quaternion _local_rot;
//
//        Vector3 _world_pos;
//        Vector3 _world_scale;
//        Vector3 _world_euler_angles; // (x, y, z) = (roll, pitch, yaw)
//        Quaternion _world_rot; // use quaternion to represent rotation? how about euler angles?    
//
//        bool _dirty;
//
//    };
//}
//
//
//#endif // COMMON_TRANSFORM_H