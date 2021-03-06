// Fragment shader for per-pixel diffuse shading. The
// teapot is a good object to test this shader, since
// the .obj file includes surface normals.

// The shader computes the dot product between the unit
// surface normal and light direction, which were 
// passed as varying inputs from the vertex shader. The
// result is multiplied with the vertex color, which is 
// accessed through a pre-defined varying variable.

varying vec3 normal, L[2], R[2], eyeDir;
varying float d[2];

vec4 ambient(int light)
{
    return gl_LightModel.ambient * gl_FrontMaterial.ambient + 
        gl_LightSource[light].ambient *
        gl_FrontMaterial.ambient;
}

vec4 diffuse(int light)
{
    return 
        gl_LightSource[light].diffuse *
        max(dot(normalize(normal), normalize(L[light])),0.0) *
        gl_FrontMaterial.diffuse;
}

vec4 specular(int light)
{
    return 
        gl_LightSource[light].specular *
        pow(max(dot(normalize(eyeDir), normalize(R[light])), 0.0),
            gl_FrontMaterial.shininess) *
        gl_FrontMaterial.specular;
}


vec4 directional(int light)
{
    return diffuse(light) + specular(light);
}

vec4 spot(int light, float spotEffect)
{
    float att;
    att = pow(spotEffect, gl_LightSource[light].spotExponent) /
        (gl_LightSource[light].constantAttenuation +
         gl_LightSource[light].linearAttenuation * d[light] +
         gl_LightSource[light].quadraticAttenuation * d[light] * d[light]);

    return (diffuse(light) + specular(light)) * att;
}

vec4 point(int light)
{
    float att;
    att = 1.0 / (gl_LightSource[light].constantAttenuation +
                 gl_LightSource[light].linearAttenuation * d[light] +
                 gl_LightSource[light].quadraticAttenuation * d[light] * d[light]);

    return (diffuse(light) + specular(light)) * att;
}

vec4 lightcolor(int light)
{
    vec4 color;
    float spotEffect;
    color = ambient(light);
    // determine whether or not it is a directional light
    if (gl_LightSource[light].position[3] == 0.0) {
            color += directional(light);   
        } else {
            // Now find out whether this is a spot or a point.
            if (gl_LightSource[light].spotCutoff != 180.0) {
                // We have a spot light.  Determine if we are in the cone.
                spotEffect = dot(normalize(-L[light]), 
                                 normalize(gl_LightSource[light].spotDirection));
                if ( spotEffect >= gl_LightSource[light].spotCosCutoff) {
                    // We are in the cone of light, set color.
                    color += spot(light, spotEffect);
                }
            } else {
                // We have a point light.
                color += point(light);
            }
        }
    
    return color;
}

void main()
{	
    vec4 c[2];
    
    c[0] = lightcolor(0);
    c[1] = lightcolor(1);
    
    gl_FragColor = c[0] + c[1];
}
