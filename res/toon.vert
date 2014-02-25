// simple toon vertex shader

// The normal and light direction will be available in the fragment shader
varying vec3 normal, lightDir;

void main()
{	
    // Obtain the current state for the OpenGL light direction and surface normal at this vertex
	lightDir = normalize(vec3(gl_LightSource[0].position));
	normal = normalize(gl_NormalMatrix * gl_Normal);

    // Tell the rasterizer where this vertex is:
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
   // Note that you may see a special GLSL function used here that
   // optimises this step:	gl_Position = ftransform();
}
