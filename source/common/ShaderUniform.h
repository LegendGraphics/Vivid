#ifndef COMMON_SHADER_UNIFORM_H
#define COMMON_SHADER_UNIFORM_H

#include <unordered_map>
#include "base/String.h"
#include "math/Vector3.h"
#include "math/Matrix.h"

namespace te
{
    enum class ShaderUniformType
    {
        SCALAR = 0,
        VECTOR2,
        VECTOR3,
        VECTOR4,
        MATRIX4X4,
        UINT,
        INT,
        BOOL,

        SCALAR_ARRAY,
        VECTOR2_ARRAY,
        VECTOR3_ARRAY,
        VECTOR4_ARRAY,
        MATRIX4X4_ARRAY,
        UINT_ARRAY,
        INT_ARRAY,
        BOOL_ARRAY,

        UNKNOWN_CLASS,
    };

    struct ShaderUniformValue
    {
        ShaderUniformType           type;
        std::vector<float>          data;
        size_t                      size;
    };

    struct ShaderUniform
    {
        //String                      name;
        ShaderUniformValue          value;
        int                         loc;
    };

    // store run-time uniforms in shader
    class ShaderUniforms
    {
    public:
        /*float getFloat(const String& name);
        Vector3 getVector3(const String& name);
        Matrix getMatrix(const String& name);

        void setFloat(const String& name, const float value);
        void setVector3(const String& name, const Vector3& value);
        void setMatrix(const String& name, const Matrix& value);*/
    public:
        auto& getUniforms() { return _uniforms; }

        bool hasUniform(const String& name);
        void addUniform(const String& name);
        void setUniform(const String& name, const float* value, int size, ShaderUniformType type);
        /*float* getUniformValue(const String& name);
        int getUniformSize(const String& name);
        ShaderUniformType getUniformType(const String& name);*/

    private:
        std::unordered_map<String, ShaderUniform>  _uniforms;
    };
}

#endif // COMMON_SHADER_UNIFORM_H