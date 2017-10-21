$input v_color0, v_texcoord0

#include "bgfx_shader.sh"
SAMPLER2D(s_texture0, 0);

// void main()
// {
// 	gl_FragColor = v_color0 * texture2D(s_texture0, v_texcoord0);
// }

#define RADIUS 0.48


vec3 lightPos = vec3(-1.49275, -1.13349988, 0);

float getHeight(vec2 coord, float radius) {
    return sqrt(radius * radius - coord.x * coord.x  - coord.y * coord.y);
}

vec3 getNormal(vec2 coord, float radius) {
    return normalize(vec3(coord.xy, getHeight(coord, radius)));
}

void main()
{
    vec2 center = vec2(0.5, 0.5);
    vec2 current = v_texcoord0;
    float dist = distance(current, center);
    if (dist < RADIUS) {
        vec2 sphereXY = current - center;
        float rim = pow(dist / RADIUS, 8) * 3.0 + 1.0;
        // float rim = 1.0;
        vec3 diffuse = texture2D(s_texture0, v_texcoord0).rgb;
        // vec3 diffuse = vec3(1, 1, 1);
        vec3 normal = getNormal(sphereXY, RADIUS);
        vec3 lightDirection = normalize(lightPos - vec3(current.xy, 0));
        float diffuseTerm = clamp(dot(lightDirection, normal), 0.10, 1);
        gl_FragColor = vec4(diffuseTerm * diffuse * rim, 1.0);
        // gl_FragColor *= gl_FragColor.a;
    } else {
        // gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
        discard;
    }
}