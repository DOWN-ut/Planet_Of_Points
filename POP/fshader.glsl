#version 150
in vec3 v_position;
in vec3 v_normal;

out vec4 fragColor;

uniform vec4 color;

void main() {
   /*vec3 L = normalize(light_position - v_position);
   float NL = max(dot(normalize(v_normal), L), 0.0);
   vec3 color = vec3(0.39, 1.0, 0.0);
   vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);*/

   vec3 lightPos = vec3(100,20,-100);
   vec3 d = lightPos - v_position;
   float a = dot(d,v_normal);

   vec3 diffuse = vec3(v_normal);// * a;
   fragColor = vec4(diffuse,1); // color * (a > 0 ? a : -a);//vec4(1.0,1.0,1.0,1.0);//vec4(col, 1.0);
}
