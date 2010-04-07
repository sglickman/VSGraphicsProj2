// Fragment shader for per-pixel diffuse shading. The
// teapot is a good object to test this shader, since
// the .obj file includes surface normals.

// The shader computes the dot product between the unit
// surface normal and light direction, which were 
// passed as varying inputs from the vertex shader. The
// result is multiplied with the vertex color, which is 
// accessed through a pre-defined varying variable.

varying vec3 normal, lightDir[2], reflection[2], eyeDir;
varying float dist[2];

void main()
{		
    vec4 lightc[2];
    float p = 1.0;
    float spotEffect;
    
    lightc[0] = gl_LightSource[0].ambient *
      gl_FrontMaterial.ambient;
    lightc[1] = gl_LightSource[1].ambient *
      gl_FrontMaterial.ambient;
    
    // determine whether or not lightc[0] is a directional light
    if (gl_LightSource[0].position[3] == 1.0) {
      lightc[0] += 
          gl_LightSource[0].diffuse * 
          max(dot(normalize(normal), normalize(lightDir[0])),0.0) * 
          gl_FrontMaterial.diffuse;
      
      lightc[0] += 
          gl_LightSource[0].specular *
          pow(max(dot(normalize(eyeDir), normalize(reflection[0])), 0.0),
              p) *
          gl_FrontMaterial.specular;          
    } else {
      // now find out whether this is a spot or a point.
      if (!gl_LightSource[0].spotDirection.equal(vec3(0,0,0))) {
        // We have a spot light.  Determine if we are in the cone.
        spotEffect = dot(normalize(-lightDir[0]), gl_LightSource[0].spotDirection)
        if ( spotEffect >= gl_LightSource[0].spotCosCutoff) {
            // We are in the cone of light, add to lightc[0].
            spotEffect = pow(spotEffect, gl_LightSource[0].spotExponent);
            lightc[0] *= spotEffect;
            lightc[0] +=
              gl_LightSource[0].diffuse *
              max(dot(normalize(normal), normalize(lightDir[0])), 0.0) *
              gl_FrontMaterial.diffuse *
              spotEffect;
              
            lightc[0] +=
              gl_LightSource[0].specular *
              pow(max(dot(normalize(eyeDir), normalize(reflection[0])), 0.0),
                p) *
              gl_FrontMaterial.specular *
              spotEffect;
          }
      } else {
        // We have a point light.
        
      }
    }
    
    if (gl_LightSource[1].position[3] == 1.0) {
      lightc[1] += 
          gl_LightSource[1].diffuse * 
          max(dot(normalize(normal), normalize(lightDir[1])),0.0) * 
          gl_FrontMaterial.diffuse;
      
      lightc[1] += 
          gl_LightSource[1].specular *
          pow(max(dot(normalize(eyeDir), normalize(reflection[1])), 0.0),
              p) *
          gl_FrontMaterial.specular;
    }
    
    gl_FragColor = lightc[0] + lightc[1];
}
