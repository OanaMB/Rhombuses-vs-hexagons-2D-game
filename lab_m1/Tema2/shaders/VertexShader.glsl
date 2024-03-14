#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec3 v_texture;
//layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float hp;

// Output
// TODO(student): Output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec3 frag_tex;

void main()
{
    if(hp < 100.f) {
        // Deformation function - you can modify this based on your requirements
    float damagePercentage = hp/100; 
    float squishFactor = exp(-damagePercentage-0.2);
    vec3 deformedPosition = v_position * vec3(1.0f - squishFactor, 1.0f, 1.0f - squishFactor);

    // Output the deformed position for the fragment shader
    frag_position = deformedPosition;
    frag_normal = v_normal;
    frag_tex = v_texture;

    // Calculate the final position using the MVP matrix
    gl_Position = Projection * View * Model * vec4(deformedPosition, 1.0);

    } else {
     // Send output to fragment shader
    frag_position = v_position;
    frag_normal = v_normal;
    frag_tex = v_texture;
    
    // Compute gl_Position
    gl_Position = Projection * View * Model * vec4(v_position, 1.0);
    
    }
  
}
