#version 430
in vec2 g_texPos;
in vec3 g_normal;
uniform sampler2D albedoMap;

void main()  
{  
    vec4 color = texture(albedoMap,g_texPos);
    gl_FragColor = color;
}  