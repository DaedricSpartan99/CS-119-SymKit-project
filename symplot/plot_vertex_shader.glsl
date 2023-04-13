attribute vec3 vertex;
attribute vec4 color;

uniform mat4 projection;

varying vec4 frag_color;

void main()
{
    gl_Position = projection * vec4(vertex, 1.0);
    frag_color = color;
}
