#version 330


uniform sampler2D tex;

uniform float scale = 0.5; // Skala tekstury
uniform vec2 offset; // Przesuniêcie tekstury

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

//Zmienne interpolowane
in vec2 i_tc;

void main(void) {
	vec2 textureCoords = vec2(gl_FragCoord.x / scale + offset.x, gl_FragCoord.y / scale + offset.y);

	pixelColor=texture(tex,i_tc);
}
