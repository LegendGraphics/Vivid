
in vec2 texCoords;
uniform sampler2D albedoMap;

void main()  
{  
    vec4 color = texture2D(albedoMap,texCoords.xy);
    gl_FragColor = color;  
}  