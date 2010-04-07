// Vertex shader for per-pixel diffuse shading.The
// teapot is a good object to test this shader, since
// the .obj file includes surface normals.

// The shader computes the unit light direction and unit
// surface normal, which are passed to the fragment
// shader as varying variables.

varying vec3 normal, lightDir[2], reflection[2], eyeDir;
varying float dist[2];

void main()
{	
    vec3 aux;
    // Note that gl_LightSource, gl_NormalMatrix, and gl_Normal
    // are pre-defined variables that access the current OpenGL
    // state.
    if (gl_LightSource[0].position[3] == 0.0) {
      // We have a directional light
      lightDir[0] = normalize(vec3(gl_LightSource[0].position));
    } else {
      // We have a positional or spot light
      aux = vec3(gl_LightSource[0].position - gl_Vertex)
      lightDir[0] = normalize(aux);
      dist[0] = length(aux);
    }
    
    if (gl_LightSource[1].position[3] == 0.0) {
      // We have a directional light
      lightDir[1] = normalize(vec3(gl_LightSource[1].position));
    } else {
      // We have a positional or spot light
      aux = vec3(gl_LightSource[1].position - gl_Vertex)
      lightDir[1] = normalize(aux);
      dist[1] = length(aux);
    }
    
    normal = normalize(gl_NormalMatrix * gl_Normal);

    reflection[0] = -reflect(lightDir[0], normal);
    reflection[1] = -reflect(lightDir[1], normal);

    eyeDir = -normalize(vec3(gl_ModelViewMatrix * gl_Vertex));
	
    // ftransform() is a built-in function that applies all
    // transformations (i.e., modelview and 
    // projection) to a vertex.
    gl_Position = ftransform();
}
