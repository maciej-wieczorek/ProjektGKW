#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


uniform vec4 color=vec4(1,1,1,1);
uniform vec4 lightDir=vec4(0,0,1,0);

//Atrybuty
layout (location=0) in vec3 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location=1) in vec3 normal; //wektor normalny w wierzcholku
layout (location=2) in vec2 aTexCord;


//Zmienne interpolowane
out vec4 i_color;
out vec2 texCord;

void main(void) {

    gl_Position=P*V*M*vec4(vertex, 1);

    mat4 G=mat4(inverse(transpose(mat3(M))));
    vec4 n=normalize(V*G*vec4(normal,0));

    float nl=clamp(dot(n,lightDir),0,1);

    i_color=vec4(color.rgb*nl,color.a);
    texCord = aTexCord;
}
