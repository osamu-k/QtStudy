#ifdef GL_ES
precision mediump float;
#endif

const float c_zero = 0.0;
const float c_one  = 1.0;

struct light {
    vec4    position;
    vec4    ambient_color;
    vec4    diffuse_color;
    vec4    specular_color;
    vec3    spot_direction;
    vec3    attenuation_factors;
    bool    compute_distance_attenuation;
    float   spot_exponent;
    float   spot_cutoff_angle;
};
uniform light u_light;

struct material {
    vec4    ambient_color;
    vec4    diffuse_color;
    vec4    specular_color;
    float   specular_exponent;
};
uniform material u_material;

varying vec3 v_lightDirection;
varying vec3 v_eyeDirection;
varying vec4 v_texcoord;
varying vec4 v_color;
varying vec3 v_normal;

void main(void)
{
    vec4 color = vec4(c_zero, c_zero, c_zero, c_zero);
    float att_factor = c_one;
    float ndotl, ndoth;
    vec3 halfplane;

    if (u_light.compute_distance_attenuation){
        vec3 att_dist;
        att_dist.x = c_one;
        att_dist.z = dot(v_lightDirection, v_lightDirection);
        att_dist.y = sqrt(att_dist.z);
        att_factor = c_one / dot(att_dist, u_light.attenuation_factors);
    }

    vec3 lightDirection = normalize(v_lightDirection);
    vec3 eyeDirection = normalize(v_eyeDirection);

    if (u_light.spot_cutoff_angle < 180.0)
    {
        float spot_factor = dot(-lightDirection, u_light.spot_direction);
        if (spot_factor >= cos(radians(u_light.spot_cutoff_angle)))
            spot_factor = pow(spot_factor, u_light.spot_exponent);
        else
            spot_factor = c_zero;
        att_factor *= spot_factor;
    }

    if (att_factor > c_zero)
    {
//        color += (u_light.ambient_color * u_material.ambient_color);
        color += (u_light.ambient_color * v_color);
        ndotl = max(c_zero, dot(v_normal, lightDirection));
//        color += (ndotl * u_light.diffuse_color * u_material.diffuse_color);
        color += (ndotl * u_light.diffuse_color * v_color);
//        halfplane = normalize(lightDirection + vec3(c_zero, c_zero, c_one));
        halfplane = normalize(lightDirection + eyeDirection);
        ndoth = max(c_zero, dot(v_normal, halfplane));
        if (ndoth > c_zero)
        {
            color += (pow(ndoth, u_material.specular_exponent) *
                      u_material.specular_color *
                      u_light.specular_color);
        }
    }

    gl_FragColor = color;
}
