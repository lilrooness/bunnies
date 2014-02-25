// simple toon fragment shader

varying vec3 normal, lightDir;

void main()
{
	float intensity;
	vec4 colour;

	
	// the cosine, which we will store in a variable named intensity, 
    // can be computed with the dot function provided by GLSL
	intensity = max(dot(lightDir,normal),0.0); 

    // Compute a colour so that the brightest colours are used when the cosine is larger 
	if (intensity > 0.98)
		colour = vec4(0.8,0.8,0.8,1.0);
	else if (intensity > 0.5)
		colour = vec4(0.4,0.4,0.8,1.0);	
	else if (intensity > 0.25)
		colour = vec4(0.2,0.2,0.4,1.0);
	else
		colour = vec4(0.1,0.1,0.1,1.0);		
	
    // set the gl_FragColor based on the computed colour:	
	gl_FragColor = colour;
}
