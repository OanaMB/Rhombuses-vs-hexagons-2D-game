#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 frag_position;
in vec3 frag_normal;
in vec3 frag_tex;
in vec3 frag_color;

// Output
//layout(location = 0) out vec4 out_position;
layout(location = 1) out vec4 out_position;
//layout(location = 2) out vec4 out_texture;
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Write pixel out color
   out_position = vec4(frag_position,1);
  // out_normal = vec4(frag_normal,1);
  //out_texture = vec4(frag_tex,1);
    out_color = vec4(frag_color,1);

}
