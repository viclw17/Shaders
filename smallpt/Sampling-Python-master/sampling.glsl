vec2 resolution = iResolution;
vec2 mouse      = iMouse;
float time      = iGlobalTime;

float timeScale = 3.;
float zoomOut = 5.;
const int iteration = 50;
float seed = 0.;

float rand() {
  return fract(sin(seed++)*43758.5453123);
}

vec2 random_spherical(vec2 uv)
{
    // Correct Range [0;pi] [-pi;pi]
    float theta = uv.x * rand();
    float phi = (uv.y * rand() * 2.) - rand();
    // Switch to cartesian coordinates
    float x = sin(theta) * cos(phi);
    float y = cos(theta) * cos(phi);
    return vec2(x,y);
}

float grid(in float step, in float position, in float pixelWidth) {
    #define ALTERNATIONS 10.0
    float   m           = mod(position, step),
            distance    = min(m, step - m),
            intensity   = clamp(0.75 * pixelWidth / distance, 0.0, 1.0),
            alternation = mod(floor((position + 0.5 * step) / step), ALTERNATIONS);

    return intensity * (1.0 - (min(alternation, ALTERNATIONS - alternation) / (0.6 * ALTERNATIONS)));
}

vec3 mandelbrot(vec2 c)
{
    const float B = 16.;
    float l = 0.0;
    vec2  z = vec2(0.0);
    for( int i=0; i<iteration; i++ )
    {
        // 1. z = z*z + c
        // z = vec2( z.x*z.x - z.y*z.y, 2.0*z.x*z.y ) + c;
        // 2. Shortcut
        z = mat2(z,-z.y,z.x) * z + c;
        if( dot(z,z)>(B*B) ) break;
        l += 1.0;
    }
    return vec3(l/(float(iteration)));
}

/* Draw a circle at vec2 `pos` with radius `rad` and
* color `color`.
*/
vec4 circle(vec2 uv, vec2 pos, float rad, vec3 color)
{
	float d = length(pos - uv) - rad;
	float t = clamp(d, 0.0, 1.0);
	return vec4(color, 1.0 - t);
}

void main(void)
{
    // Calculate & Normalize UV coordianates
    // vec2 uv = gl_FragCoord.xy/iResolution.xy - .5;
    // uv.x *= iResolution.x / iResolution.y;
    // Shoutcut
    vec2 uv = ( gl_FragCoord.xy - .5*iResolution.xy ) / iResolution.y;
    vec4 color;

    vec2 center = iResolution.xy * 0.5;
    // center = random_spherical(uv);
	float radius = 10.;
    // color = mandelbrot(uv*zoomOut);

    // for(int i=0; i<=5; i++)
    // {
    //     color = vec3(random_spherical(uv),1);
    // }
    // Background layer
	vec4 layer1 = vec4(0);

	// Circle
	vec3 red = vec3(1,0,0);
	vec4 layer2 = circle(gl_FragCoord.xy, center, radius, red);

	// Blend the two
	color = mix(layer1, layer2, layer2.a);



    float   viewSize    = 5.,
            centerX     = 0.,
            left        = -viewSize + centerX,
            right       =  viewSize + centerX,
            top         =  viewSize,
            bottom      = -viewSize;
    // convert fragment's pixel position to graph space location
    float   locationX   = left   + (right - left) * gl_FragCoord.x / iResolution.x,
            locationY   = bottom + (top - bottom) * gl_FragCoord.y / iResolution.y;
            locationX  *= iResolution.x / iResolution.y;
    // calculate width of a pixel in graph space
    float   pixelWidth  = (right - left) / iResolution.x;

    float   gridColor   = 0.5 * grid(1.0, locationY, pixelWidth) +
                          0.5 * grid(1.0, locationX, pixelWidth);

    gl_FragColor = color+vec4(0,gridColor,gridColor,1);
}
