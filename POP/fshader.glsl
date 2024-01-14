#version 150
in vec3 v_position;
in vec3 v_normal;

out vec4 fragColor;

uniform vec4 color;
uniform vec3 camera;

void main() {
   /*vec3 L = normalize(light_position - v_position);
   float NL = max(dot(normalize(v_normal), L), 0.0);
   vec3 color = vec3(0.39, 1.0, 0.0);
   vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);*/

   vec3 normal = normalize(-1 * v_normal);

   if(length(normal) == 0.0)
   {
       fragColor = vec4(color.xyz,1);
   }
    else
   {
       vec3 lightPos = vec3(1000,20,-1000);
       vec3 d = vec3(-1,0,0);//normalize(lightPos - v_position);
       float a = dot(d,normal);
       a = max(0,a);

       vec3 re = -reflect(normalize(camera - v_position),normal);
       float b = dot(re,normal);

       vec3 diffuse = vec3(0.05,0.05,0.05) + (0.95 * (vec3(color) * a));// + (0.2 * (vec3(1,1,1) * b));
       fragColor = vec4(diffuse,1); // color * (a > 0 ? a : -a);//vec4(1.0,1.0,1.0,1.0);//vec4(col, 1.0);
   }
}
