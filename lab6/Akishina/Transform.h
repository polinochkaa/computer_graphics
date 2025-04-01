#pragma once
#include "Matrix.h"
#include <math.h>

mat3 translate(float Tx, float Ty) {
	mat3* res = new mat3(1.f);// создали единичную матрицу
	(*res)[0][2] = Tx;// поменяли
	(*res)[1][2] = Ty;// значения в последнем столбце
	return *res;
}

mat3 scale(float Sx, float Sy) {
	mat3* res = new mat3(1.f);// создали единичную матрицу
	(*res)[0][0] = Sx;// поменяли
	(*res)[1][1] = Sy;// значения в на главной диагонали
	return *res;
}
mat3 scale(float S) {
	return scale(S, S);
}
//матрица поворота относительно начала координат против часовой стрелки 
mat3 rotate(float theta) {
	mat3* res = new  mat3(1.f);// создали единичную матрицу
	(*res)[0][0] = (*res)[1][1] = (float)cos(theta);// заполнили главную диагональ
	(*res)[0][1] = (float)sin(theta);// синус в первой строке (с плюсом)
	(*res)[1][0] = -(*res)[0][1];// синус во второй строке (с минусом)
	return *res;
}
//отраженеи по горизонтали 
mat3 mirrorX() {
	mat3* res = new  mat3(1.f);// создали единичную матрицу
	(*res)[0][0] = 1.f;// заполнили главную диагональ
	(*res)[1][1] = -1.f;// синус в первой строке (с плюсом)
	return *res;

}
//отражение по вертикали 
mat3 mirrorY() {
	mat3* res = new  mat3(1.f);// создали единичную матрицу
	(*res)[0][0] = -1.f;// заполнили главную диагональ
	(*res)[1][1] = 1.f;// синус в первой строке (с плюсом)
	return *res;
}
mat4 translate(float Tx, float Ty, float Tz) {
	mat4* res = new mat4(1.f);// создали единичную матрицу
	(*res)[0][3] = Tx;// поменяли
	(*res)[1][3] = Ty;// значения в последнем столбце
	(*res)[2][3] = Tz;// значения в последнем столбце
	return *res;
}
mat4 scale(float Sx, float Sy, float Sz) {
	mat4* res = new mat4(1.f);// создали единичную матрицу
	(*res)[0][0] = Sx;// поменяли
	(*res)[1][1] = Sy;// значения в на главной диагонали
	(*res)[2][2] = Sy;
	return *res;
}
// самостоятельная реализация 

mat4 rotate(float theta, vec3 n) {
	n = norm(n);
	mat3 matrix1 = mat3(1.0) + (crossM(n) * sin(theta));
	mat3 matrix2 = crossM(n) * (crossM(n) * (1 - cos(theta)));
	mat3 matrixres = matrix1 + matrix2;
	mat4 coutmatrix = mat4(vec4(matrixres[0], 0.f),
		vec4(matrixres[1], 0.f),
		vec4(matrixres[2], 0.f),
		vec4(0.f, 0.f, 0.f, 1.f));
	return coutmatrix;
}

mat4 rotateP(float theta, vec3 n, vec3 P) {
	return translate(P.x, P.y, P.z) *
		(rotate(theta, n) * translate(-P.x, -P.y, -P.z));
}


mat4 lookAt(vec3 S, vec3 P, vec3 u) {
	mat4 T = translate(-S.x, -S.y, -S.z);// создаем матрицу где в 4 столбце стоят эдементы -x, -y, -z , 1
	vec3 ups = (S - P);//координаты вектора от точки р до точки s
	vec3 e3 = ups * (1.f / length(S - P));// находим вектор е3
	vec3 e1 = cross(u, e3) * (1.f / length(cross(u, e3))); // навходим вектор е1
	vec3 e2 = cross(e3, e1) * (1.f / length(cross(e3, e1)));// навходим вектор е2
	mat4 R = mat4(vec4(e1, 0.f),
		vec4(e2, 0.f),
		vec4(e3, 0.f),
		vec4(0.f, 0.f, 0.f, 1.f));
	return R * T;
}

mat4 ortho(float l, float r, float b, float t, float zn, float zf) {
	return mat4(vec4(2.f / (r - l), 0.f, 0.f, -(r + l) / (r - l)),
		vec4(0.f, 2.f / (t - b), 0.f, -(t + b) / (t - b)),
		vec4(0.f, 0.f, -2 / (zf - zn), -(zf + zn) / (zf - zn)),
		vec4(0.f, 0.f, 0.f, 1.f));
}

mat4 frustum(float l, float r, float b, float t, float n, float f) {
	return mat4(vec4(2 * n / (r - l), 0.f, (r + l) / (r - l), 0.f),
		vec4(0.f, 2 * n / (t - b), (t + b) / (t - b), 0.f),
		vec4(0.f, 0.f, -(f + n) / (f - n), -2 * f * n / (f - n)),
		vec4(0.f, 0.f, -1.f, 0.f));
}
mat4 perspective(float fovy, float aspect, float n, float f) {
	return mat4(vec4((1 / aspect) * (1 / tan(fovy / 2)), 0.f, 0.f, 0.f),
		vec4(0.f, 1 / tan(fovy / 2), 0.f, 0.f),
		vec4(0.f, 0.f, -(f + n) / (f - n), -2 * f * n / (f - n)),
		vec4(0.f, 0.f, -1.f, 0.f));
}
mat3 cadrRL(vec2 Vc, vec2 V, vec2 Wc, vec2 W) {
	return translate(Wc.x, Wc.y) *
		(scale(W.x / V.x, -W.y / V.y) * translate(-Vc.x, -Vc.y));
}
