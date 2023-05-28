#version 330

uniform sampler2D tex;
uniform sampler2D textureMap1;

out vec4 pixelColor;

in vec2 iTexCoord;
in vec2 iTexCoord1;
in vec4 ic;
in vec4 n;
in vec4 l1;
in vec4 l2;
in vec4 l3;
in vec4 v;

void main(void) {
    vec4 kd = mix(texture(tex, iTexCoord), texture(textureMap1, iTexCoord1), 0.3);
    vec4 ks = vec4(1, 1, 1, 1);

    vec4 mn = normalize(n);
    vec4 mv = normalize(v);

    vec4 ml1 = normalize(l1);
    vec4 ml2 = normalize(l2);
    vec4 ml3 = normalize(l3);

	// wektory odbicia lustrzanego
    vec4 mr1 = reflect(-ml1, mn);
    vec4 mr2 = reflect(-ml2, mn);
    vec4 mr3 = reflect(-ml3, mn);

	// obliczenie czynnika oœwietlenia
    float nl1 = clamp(dot(mn, ml1), 0, 1);
    float nl2 = clamp(dot(mn, ml2), 0, 1);
    float nl3 = clamp(dot(mn, ml3), 0, 1);

	// obliczenie czynnika odbicia
    float rv1 = pow(clamp(dot(mr1, mv), 0, 1), 50);
    float rv2 = pow(clamp(dot(mr2, mv), 0, 1), 50);
    float rv3 = pow(clamp(dot(mr3, mv), 0, 1), 50);

    pixelColor = vec4(kd.rgb * (nl1 + nl2 + nl3), kd.a) + vec4(ks.rgb * (rv1 + rv2 + rv3), 0);
}
