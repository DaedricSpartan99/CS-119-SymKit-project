attribute vec3 vertex;
attribute vec4 color;

uniform mat4 projection;
uniform mat4 modelview;

varying vec4 frag_color;

void main()
{
    gl_Position = projection * modelview * vec4(vertex, 1.0);
    frag_color = color;
}
