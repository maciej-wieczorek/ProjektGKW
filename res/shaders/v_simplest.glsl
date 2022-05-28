#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Atrybuty
layout (location = 0) in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location = 1) in vec4 color; //kolor zwi¹zany z wierzcho³kiem
layout (location = 2) in vec4 normal; //wektor normalny w przestrzeni modelu

//Zmienne interpolowane
out vec4 ic;
out vec4 l;
out vec4 n;
out vec4 v;

void main(void) {
    vec4 lp = vec4(0, 0, -6, 1); //pozcyja œwiat³a, przestrzeñ œwiata
    l = normalize(V * lp - V*M*vertex); //wektor do œwiat³a w przestrzeni oka
    v = normalize(vec4(0, 0, 0, 1) - V * M * vertex); //wektor do obserwatora w przestrzeni oka
    n = normalize(V * M * -normal); //wektor normalny w przestrzeni oka
    
    ic = color;
    
    gl_Position=P*V*M*vertex;
}
