#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 frag_position;
in vec3 frag_normal;
in vec3 frag_tex;
//in vec3 frag_color;

uniform vec3 Color;
uniform float hp;

// Output
layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_position;

void main()
{
   if (hp < 100.f) {
   float damagePercentage = hp / 100 + 0.2f;

    // Calculate a darkening factor based on damagePercentage
    float darkeningFactor = damagePercentage;
    
    // Darken the initial color
    vec3 darkenedColor = Color * darkeningFactor;

    // Output the darkened color
    out_color = vec4(darkenedColor, 1);
   } else {
   out_position = vec4(frag_position,1);
   out_color = vec4(Color,1);
   }

}
