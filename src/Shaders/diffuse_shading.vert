// Vertex shader for per-pixel diffuse shading.The
// teapot is a good object to test this shader, since
// the .obj file includes surface normals.

// The shader computes the unit light direction and unit
// surface normal, which are passed to the fragment
// shader as varying variables.

varying vec3 normal, lightDir0, lightDir1, reflection0, reflection1, eyeDir;

void main()
{	
    // Note that gl_LightSource, gl_NormalMatrix, and gl_Normal
    // are pre-defined variables that access the current OpenGL
    // state.
    lightDir0 = normalize(vec3(gl_LightSource[0].position));
    lightDir1 = normalize(vec3(gl_LightSource[1].position));
    normal = normalize(gl_NormalMatrix * gl_Normal);

    reflection0 = -reflect(lightDir0, normal);
    reflection1 = -reflect(lightDir1, normal);

    eyeDir = -normalize(vec3(gl_ModelViewMatrix * gl_Vertex));
	
    // ftransform() is a built-in function that applies all
    // transformations (i.e., modelview and 
    // projection) to a vertex.
    gl_Position = ftransform();
}
