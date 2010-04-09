// Vertex shader for per-pixel diffuse shading.The
// teapot is a good object to test this shader, since
// the .obj file includes surface normals.

// The shader computes the unit light direction and unit
// surface normal, which are passed to the fragment
// shader as varying variables.

varying vec3 normal, L[2], R[2], eyeDir;
varying float d[2];

void main()
{	
  vec3 aux;

    // Note that gl_LightSource, gl_NormalMatrix, and gl_Normal
    // are pre-defined variables that access the current OpenGL
    // state.
    if (gl_LightSource[0].position[3] == 0.0) {
        // We have a directional light
        L[0] = normalize(vec3(gl_LightSource[0].position));
    } else {
        // We have a positional or spot light
        aux = vec3(gl_LightSource[0].position - (gl_ModelViewMatrix * gl_Vertex));
        L[0] = normalize(aux);
        d[0] = length(aux);
    }
    
    if (gl_LightSource[1].position[3] == 0.0) {
        // We have a directional light
        L[1] = normalize(vec3(gl_LightSource[1].position));
    } else {
        // We have a positional or spot light
        aux = vec3(gl_LightSource[1].position - (gl_ModelViewMatrix * gl_Vertex));
        L[1] = normalize(aux);
        d[1] = length(aux);
    }
    
    normal = normalize(gl_NormalMatrix * gl_Normal);

    R[0] = -reflect(L[0], normal);
    R[1] = -reflect(L[1], normal);

    eyeDir = -normalize(vec3(gl_ModelViewMatrix * gl_Vertex));
	
    // ftransform() is a built-in function that applies all
    // transformations (i.e., modelview and 
    // projection) to a vertex.
    gl_Position = ftransform();
}
