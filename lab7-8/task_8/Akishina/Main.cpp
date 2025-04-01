#include <Windows.h>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>
#include "Shader.h"
#include "Figure.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

GLfloat lightVertices[] = {
	-0.1f, 0.f, 0.f,
	0.1f, 0.f, 0.f,
	0.f, 0.1f, 0.f,
	0.f, -0.1f, 0.f,
	0.f, 0.f, 0.1f,
	0.f, 0.f, -0.1f,
	0.07071f, 0.07071f, 0.f,
	-0.07071f, -0.07071f, 0.f,
	-0.07071f, 0.07071f, 0.f,
	0.07071f, -0.07071f, 0.f,
	0.07071f, 0.f, 0.07071f,
	-0.07071f, 0.f, -0.07071f,
	-0.07071f, 0.f, 0.07071f,
	0.07071f, 0.f, -0.07071f,
	0.f, 0.07071f, 0.07071f,
	0.f, -0.07071f, -0.07071f,
	0.f, -0.07071f, 0.07071f,
	0.f, 0.07071f, -0.07071f,
	0.05774f, 0.05774f, 0.05774f,
	-0.05774f, -0.05774f, -0.05774f,
	-0.05774f, -0.05774f, 0.05774f,
	0.05774f, 0.05774f, -0.05774f,
	-0.05774f, 0.05774f, 0.05774f,
	0.05774f, -0.05774f, -0.05774f,
	0.05774f, -0.05774f, 0.05774f,
	-0.05774f, 0.05774f, -0.05774f
};
GLuint lightVertexArray;
GLuint lightVertexBuffer;
mat4 lightM;
mat4 lightMD;


void makeLight() {
	glGenVertexArrays(1, &lightVertexArray);
	glBindVertexArray(lightVertexArray);
	glGenBuffers(1, &lightVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, lightVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	lightM = glm::translate(glm::vec3(0, 0, 5));
}

vector<model> models;
mat4 T;
vec3 S, P, u;

float dist;
float fovy, aspect;
float fovy_work, aspect_work;
float near_view, far_view;
float n, f;
float l, r, t, b;
double lastX, lastY;
enum projType { Ortho, Frustum, Perspective } pType;
vec3 diff(0.5, 0.5, 0.5);
vec3 spec(1, 1, 1);
bool isFilling;
bool mouseFlag = true;
bool leftMouseButtonPressed = false;

void initWorkPars() {
	n = near_view;
	f = far_view;
	fovy_work = fovy;
	aspect_work = aspect;
	float Vy = 2 * near_view * glm::tan(fovy / 2);
	float Vx = aspect * Vy;
	l = -Vx / 2;
	r = -l;
	b = -Vy / 2;
	t = -b;
	dist = glm::length(P - S);
	T = glm::lookAt(S, P, u);
}

void readFromFile(const char* fileName) {
	ifstream in(fileName);
	if (in.is_open()) {
		models.clear();
		mat4 M = mat4(1.f);
		mat4 initM;
		vector<mat4> transforms;
		vector<mesh> figure;
		float thickness = 2;
		glm::vec3 ambient = glm::vec3(0, 0, 0);
		glm::vec3 diffuse = glm::vec3(0, 0, 0);
		glm::vec3 specular = glm::vec3(0, 0, 0);
		float shininess = 1;
		string str;
		getline(in, str);
		while (in) {
			if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
				stringstream s(str);
				string cmd;
				s >> cmd;
				if (cmd == "camera") {
					float x, y, z;
					s >> x >> y >> z;
					S = glm::vec3(x, y, z);
					s >> x >> y >> z;
					P = glm::vec3(x, y, z);
					s >> x >> y >> z;
					u = glm::vec3(x, y, z);
				}
				else if (cmd == "screen") {
					s >> fovy_work >> aspect >> near_view >> far_view;
					fovy = glm::radians(fovy_work);
				}
				else if (cmd == "color") { // цвет линии
					float r, g, b;
					s >> r >> g >> b; // считываем три составл€ющие цвета
					ambient = glm::vec3(r, g, b) / 255.f;
					diffuse = ambient;
					specular = ambient;
				}
				else if (cmd == "ambient") { // способность излучать окружающий свет
					float r, g, b;
					s >> r >> g >> b; // считываем три составл€ющие цвета
					ambient = glm::vec3(r, g, b);
				}
				else if (cmd == "diffuse") { // способность излучать рассе€нный свет
					float r, g, b;
					s >> r >> g >> b; // считываем три составл€ющие цвета
					diffuse = glm::vec3(r, g, b);
				}
				else if (cmd == "specular") { // // способность излучать блики
					float r, g, b;
					s >> r >> g >> b; // считываем три составл€ющие цвета
					specular = glm::vec3(r, g, b);
				}
				else if (cmd == "shininess") { // степень гл€нцевости
					s >> shininess;
				}
				else if (cmd == "thickness") {
					s >> thickness;
				}
				else if (cmd == "mesh") {
					vector<vertex> vertices;
					vector<GLuint> indices;
					int n, k;
					s >> n >> k;
					string str1;
					while (n > 0) {
						getline(in, str1);
						if ((str1.find_first_not_of(" \t\r\n") != string::npos) && (str1[0] != '#')) {
							float x, y, z;
							float nx, ny, nz;
							stringstream s1(str1);
							s1 >> x >> y >> z;
							s1 >> nx >> ny >> nz;
							vertices.push_back({ {x,y,z}, {nx,ny,nz} });
							--n;
						}
					}
					while (k > 0) {
						std::getline(in, str1);
						if ((str1.find_first_not_of(" \t\r\n") != std::string::npos) && (str1[0] != '#')) {
							GLuint x;
							std::stringstream s1(str1);
							for (int i = 0; i < 3; i++) {
								s1 >> x;
								indices.push_back(x);
							}
							--k;
						}
					}
					figure.push_back(mesh(vertices, indices, { ambient, diffuse, specular, shininess }));
				}
				else if (cmd == "model") {
					float mVcx, mVcy, mVcz, mVx, mVy, mVz;
					s >> mVcx >> mVcy >> mVcz >> mVx >> mVy >> mVz;
					float S = mVx / mVy < 1 ? 2.f / mVy : 2.f / mVx;
					initM = glm::scale(glm::vec3(S)) * glm::translate(glm::vec3(-mVcx, -mVcy, -mVcz));
					figure.clear();
				}
				else if (cmd == "figure") {
					models.push_back(model(figure, M * initM));
				}
				else if (cmd == "translate") {
					float Tx, Ty, Tz;
					s >> Tx >> Ty >> Tz;
					M = glm::translate(vec3(Tx, Ty, Tz)) * M;
				}
				else if (cmd == "scale") {
					float S;
					s >> S;
					M = glm::scale(vec3(S, S, S)) * M;
				}
				else if (cmd == "rotate") {
					float theta;
					float nx, ny, nz;
					s >> theta >> nx >> ny >> nz;
					M = rotate(glm::radians(-theta), vec3(nx, ny, nz)) * M;
				}
				else if (cmd == "pushTransform") {
					transforms.push_back(M);
				}
				else if (cmd == "popTransform") {
					M = transforms.back();
					transforms.pop_back();
				}
			}
			getline(in, str);
		}
		initWorkPars();
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

mat4 rotateP(float theta, vec3 n, vec3 P) {
	return translate(P) * rotate(theta, n) * translate(-P);
}

void cursorPos_callback(GLFWwindow* window, double xpos, double ypos) {
	glm::vec3 n = glm::vec3(lastY - ypos, lastX - xpos, 0);
	glm::mat4 M = glm::rotate(glm::length(n) * 0.002f, n);
	glm::vec3 P = M * glm::vec4(0, 0, -1, 1);
	T = glm::lookAt(glm::vec3(0), P, u) * T;
	lastX = xpos;
	lastY = ypos;
}

// обработчик позиции курсора при включенном курсоре
void cursorPosSave_callback(GLFWwindow* window, double xpos, double ypos) {
	if (leftMouseButtonPressed) {
		glm::vec3 n = glm::vec3(lastY - ypos, lastX - xpos, 0);
		glm::mat4 M = rotateP(0.1, n, glm::vec3(0, 0, -dist));
		glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0);
		glm::vec3 S_new = glm::vec3(M * glm::vec4(0, 0, 0, 1));
		glm::vec3 P = M * glm::vec4(0, 0, -1, 1);
		T = lookAt(S_new, P, u_new) * T;
	}
	lastX = xpos;
	lastY = ypos;
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	dist += yoffset;
}

// обработчик нажати€ кнопки мыши
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			leftMouseButtonPressed = true;
		}
		else if (action == GLFW_RELEASE) {
			leftMouseButtonPressed = false;
		}
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action != GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			diff = vec3(0.5f, 0.5f, 0.5f);
			spec = vec3(1.f, 1.f, 1.f);
			initWorkPars();
			break;
		case GLFW_KEY_1:
			pType = Ortho;
			break;
		case GLFW_KEY_2:
			pType = Perspective;
			break;
		case GLFW_KEY_3:
			pType = Frustum;
			break;
		case GLFW_KEY_4:
			if (mode == GLFW_MOD_SHIFT)
				lightMD = glm::translate(vec3(0.f, 0.f, -0.3f)) * lightMD;
			else lightMD = glm::translate(vec3(0.f, 0.f, 0.3f)) * lightMD;
			break;
		case GLFW_KEY_5:
			if (mode == GLFW_MOD_SHIFT)
				lightMD = glm::translate(vec3(-0.3f, 0.f, 0.f)) * lightMD;
			else lightMD = glm::translate(vec3(0.3f, 0.f, 0.f)) * lightMD;
			break;
		case GLFW_KEY_6:
			if (mode == GLFW_MOD_SHIFT)
				lightMD = glm::translate(vec3(0.f, -0.3f, 0.f)) * lightMD;
			else lightMD = glm::translate(vec3(0.f, 0.3f, 0.f)) * lightMD;
			break;
		case GLFW_KEY_7:
			if (mode == GLFW_MOD_SHIFT) {
				diff *= 1 / 1.1f;
				spec *= 1 / 1.1f;
			}
			else {
				diff *= 1.1f;
				spec *= 1.1f;
			}
			break;
		case GLFW_KEY_0:
			isFilling = !isFilling;
			if (isFilling)
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case GLFW_KEY_W:
			if (mode == GLFW_MOD_SHIFT)
				T = glm::lookAt(vec3(0.f, 0.f, -0.1f), vec3(0.f, 0.f, -0.2f), vec3(0.f, 0.1f, 0.f)) * T;
			else
				T = glm::lookAt(vec3(0.f, 0.f, -1.0f), vec3(0.f, 0.f, -2.0f), vec3(0.f, 1.0f, 0.f)) * T;
			break;
		case GLFW_KEY_S:
			if (mode == GLFW_MOD_SHIFT)
				T = glm::lookAt(vec3(0.f, 0.f, 0.1f), vec3(0.f, 0.f, 0.f), vec3(0.f, 0.1f, 0.f)) * T;
			else
				T = glm::lookAt(vec3(0.f, 0.f, 1.0f), vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f)) * T;
			break;
		case GLFW_KEY_A:
			if (mode == GLFW_MOD_SHIFT)
				T = glm::lookAt(vec3(-0.1f, 0.f, 0.f), vec3(-0.1f, 0.f, -0.1f), vec3(0.f, 0.1f, 0.f)) * T;
			else
				T = glm::lookAt(vec3(-1.0f, 0.f, 0.f), vec3(-1.0f, 0.f, -1.0f), vec3(0.f, 1.0f, 0.f)) * T;
			break;
		case GLFW_KEY_D:
			if (mode == GLFW_MOD_SHIFT)
				T = glm::lookAt(vec3(0.1f, 0.f, 0.f), vec3(0.1f, 0.f, -0.1f), vec3(0.f, 0.1f, 0.f)) * T;
			else
				T = glm::lookAt(vec3(1.0f, 0.f, 0.f), vec3(1.0f, 0.f, -1.0f), vec3(0.f, 1.0f, 0.f)) * T;
			break;
		case GLFW_KEY_R:
			mat4 rotation = rotate(0.1f, glm::vec3(0.f, 0.f, 1.f));
			vec3 u_new = mat3(vec3(rotation[0]), vec3(rotation[1]), vec3(rotation[2])) * vec3(0.f, 1.f, 0.f);
			T = glm::lookAt(vec3(0.f, 0.f, 0.f), vec3(0.f, 0.f, -1.f), u_new) * T;
			break;
		case GLFW_KEY_T:
			if (mode == GLFW_MOD_SHIFT) {
				mat4 M = rotateP(0.1f, vec3(1.f, 0.f, 0.f), vec3(0.f, 0.f, -dist));
				vec3 u_new = mat3(vec3(M[0]), vec3(M[1]), vec3(M[2])) * vec3(0.f, 1.f, 0.f);
				vec3 S_new = glm::normalize(M * vec4(0.f, 0.f, 0.f, 1.f));
				T = glm::lookAt(S_new, vec3(0.f, 0.f, -dist), u_new) * T;
			}
			else {
				mat4 M = glm::rotate(0.1f, vec3(1.f, 0.f, 0.f));
				vec3 u_new = mat3(vec3(M[0]), vec3(M[1]), vec3(M[2])) * vec3(0.f, 1.f, 0.f);
				vec3 P_new = normalize(M * vec4(0.f, 0.f, -1.f, 1.f));
				T = glm::lookAt(vec3(0.f, 0.f, 0.f), P_new, u_new) * T;
			}
			break;
		case GLFW_KEY_I:
			if (mode == GLFW_MOD_SHIFT)
				t--;
			else
				t++;
			break;
		case GLFW_KEY_J:
			if (mode == GLFW_MOD_SHIFT)
				l--;
			else
				l++;
			break;
		case GLFW_KEY_Y: {
			mat4 rotation = glm::rotate(-0.1f, vec3(0.f, 0.f, 1.f));
			vec3 u_new = mat3(vec3(rotation[0]), vec3(rotation[1]), vec3(rotation[2])) * vec3(0.f, 1.f, 0.f);
			T = glm::lookAt(vec3(0.f, 0.f, 0.f), vec3(0.f, 0.f, -1.f), u_new) * T;
			break;
		}
		case GLFW_KEY_G:
			if (mode == GLFW_MOD_SHIFT) {
				mat4 M = rotateP(-0.1f, vec3(1.f, 0.f, 0.f), vec3(0.f, 0.f, -dist));
				vec3 u_new = mat3(vec3(M[0]), vec3(M[1]), vec3(M[2])) * vec3(0.f, 1.f, 0.f);
				vec3 S_new = vec3(M * vec4(0.f, 0.f, 0.f, 1.f));
				T = glm::lookAt(S_new, vec3(0.f, 0.f, -dist), u_new) * T;
			}
			else {
				mat4 M = glm::rotate(-0.1f, vec3(1.f, 0.f, 0.f));
				vec3 u_new = mat3(vec3(M[0]), vec3(M[1]), vec3(M[2])) * vec3(0.f, 1.f, 0.f);
				vec3 P_new = vec3(M * vec4(0.f, 0.f, -1.f, 1.f));
				T = glm::lookAt(vec3(0.f, 0.f, 0.f), P_new, u_new) * T;
			}
			break;
		case GLFW_KEY_F:
			if (mode == GLFW_MOD_SHIFT) {
				mat4 M = rotateP(0.1f, vec3(0.f, 1.f, 0.f), vec3(0.f, 0.f, -dist));
				vec3 u_new = mat3(vec3(M[0]), vec3(M[1]), vec3(M[2])) * vec3(0.f, 1.f, 0.f);
				vec3 S_new = vec3(M * glm::vec4(0.f, 0.f, 0.f, 1.f));
				T = glm::lookAt(S_new, glm::vec3(0.f, 0.f, -dist), u_new) * T;
			}
			else {
				mat4 M = rotate(0.1f, vec3(0.f, 1.f, 0.f));
				vec3 u_new = mat3(vec3(M[0]), vec3(M[1]), vec3(M[2])) * vec3(0.f, 1.f, 0.f);
				vec3 P_new = vec3(M * vec4(0.f, 0.f, -1.f, 1.f));
				T = glm::lookAt(glm::vec3(0.f, 0.f, 0.f), P_new, u_new) * T;
			}
			break;
		case GLFW_KEY_H:
			if (mode == GLFW_MOD_SHIFT) {
				mat4 M = rotateP(-0.1f, vec3(0.f, 1.f, 0.f), vec3(0.f, 0.f, -dist));
				vec3 u_new = mat3(vec3(M[0]), vec3(M[1]), vec3(M[2])) * vec3(0.f, 1.f, 0.f);
				vec3 S_new = vec3(M * vec4(0.f, 0.f, 0.f, 1.f));
				T = glm::lookAt(S_new, vec3(0.f, 0.f, -dist), u_new) * T;
			}
			else {
				mat4 M = glm::rotate(-0.1f, vec3(0.f, 1.f, 0.f));
				vec3 u_new = mat3(vec3(M[0]), vec3(M[1]), vec3(M[1])) * vec3(0.f, 1.f, 0.f);
				vec3 P_new = vec3(M * vec4(0.f, 0.f, -1.f, 1.f));
				T = glm::lookAt(vec3(0.f, 0.f, 0.f), P_new, u_new) * T;
			}
			break;
		case GLFW_KEY_K:
			if (mode == GLFW_MOD_SHIFT)
				b--;
			else
				b++;
			break;
		case GLFW_KEY_L:
			if (mode == GLFW_MOD_SHIFT)
				r--;
			else
				r++;
			break;
		case GLFW_KEY_U:
			if (mode == GLFW_MOD_SHIFT) {
				if (n > 0.3f)
					n -= 0.2f;
			}
			else
				if (n < f - 0.3f)
					n += 0.2f;
			break;
		case GLFW_KEY_O:
			if (mode == GLFW_MOD_SHIFT) {
				if (f > n + 0.3f)
					f -= 0.2f;
			}
			else
				f += 0.2f;
			break;
		case GLFW_KEY_B:
			if (mode == GLFW_MOD_SHIFT) {
				if (dist > 0.3f)
					dist -= 0.1f;
			}
			else
				dist += 0.1f;
			break;
		case GLFW_KEY_Z:
			if (mode == GLFW_MOD_SHIFT) {
				if (fovy_work > 0.4f)
					fovy_work -= 0.1f;
			}
			else
				if (fovy_work < 2.9f)
					fovy_work += 0.1f;
			break;
		case GLFW_KEY_X:
			if (mode == GLFW_MOD_SHIFT) {
				if (aspect_work > 0.06f)
					aspect_work -= 0.05f;
			}
			else
				aspect_work += 0.05f;
			break;
		case GLFW_KEY_F3: {
			OPENFILENAME openFileDialog;
			char fileName[260];
			ZeroMemory(&openFileDialog, sizeof(openFileDialog));
			openFileDialog.lStructSize = sizeof(openFileDialog);
			openFileDialog.hwndOwner = NULL;
			openFileDialog.lpstrFile = fileName;
			openFileDialog.lpstrFile[0] = '\0';
			openFileDialog.nMaxFile = sizeof(fileName);
			openFileDialog.lpstrFilter = "Text files (*.txt)\0*.txt\0All files 2007\0*.*\0";
			openFileDialog.nFilterIndex = 1;
			openFileDialog.lpstrFileTitle = NULL;
			openFileDialog.nMaxFileTitle = 0;
			openFileDialog.lpstrInitialDir = NULL;
			openFileDialog.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

			if (GetOpenFileName(&openFileDialog))
				readFromFile(fileName);
			break;
		}
		case GLFW_KEY_F5:
			if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				glfwSetCursorPosCallback(window, cursorPosSave_callback);
				mouseFlag = false;
			}
			else {
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				glfwSetCursorPosCallback(window, cursorPos_callback);
				mouseFlag = true;
			}
			break;
		default:
			break;
		}
	}
}



GLFWwindow* initWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Akishina_lab8", NULL, NULL);
	glfwMakeContextCurrent(window);
	return window;
}

void setHandlers(GLFWwindow* window) {
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursorPos_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
}


int main() {
	GLFWwindow* window = initWindow();
	if (window == NULL) { // если ссылка на окно не создана
		std::cout << "¬ызов glfwCreateWindow закончилс€ неудачей." << std::endl;
		glfwTerminate(); // завершить работу GLFW
		return -1; // завершить программу
	}
	setHandlers(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Ќе удалось загрузить GLAD" << std::endl;
		glfwTerminate(); // завершить работу GLFW
		return -1; // завершить программу
	}

	glViewport(0, 0, 800, 600);

	shader vertexShader("Vertex.glsl", GL_VERTEX_SHADER);
	shader fragmentShader("Fragment.glsl", GL_FRAGMENT_SHADER);
	program shaderProgram(vertexShader, fragmentShader);
	shaderProgram.useUniform("pathColor");
	shaderProgram.useUniform("clipView");
	shaderProgram.useUniform("modelView");
	shaderProgram.useUniform("modelInv");
	shaderProgram.useUniform("light1Pos");
	shaderProgram.useUniform("light2Pos");
	shaderProgram.useUniform("viewPos");
	shaderProgram.useUniform("light1.ambient");
	shaderProgram.useUniform("light1.diffuse");
	shaderProgram.useUniform("light1.specular");
	shaderProgram.useUniform("light2.ambient");
	shaderProgram.useUniform("light2.diffuse");
	shaderProgram.useUniform("light2.specular");
	shaderProgram.useUniform("material.ambient");
	shaderProgram.useUniform("material.diffuse");
	shaderProgram.useUniform("material.specular");
	shaderProgram.useUniform("material.shininess");
	vertexShader.clear();
	fragmentShader.clear();

	vertexShader = shader("LightVertex.glsl", GL_VERTEX_SHADER);
	fragmentShader = shader("LightFragment.glsl", GL_FRAGMENT_SHADER);
	program lightShaderProgram(vertexShader, fragmentShader);
	lightShaderProgram.useUniform("clipView");
	lightShaderProgram.useUniform("pathColor");
	vertexShader.clear();
	fragmentShader.clear();

	lightMD = glm::translate(glm::vec3(7, 5, -4));
	makeLight();
	readFromFile("triangle.txt");

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.use();
		mat4 proj;
		switch (pType) {
		case Ortho:
			proj = glm::ortho(l, r, b, t, n, f);
			break;
		case Frustum:
			proj = glm::frustum(l, r, b, t, n, f);
			break;
		case Perspective:
			proj = glm::perspective(fovy_work, aspect_work, n, f);
			break;
		}
		mat4 C = proj * T;
		shaderProgram.setUniform("light1.ambient", vec3(0.2f, 0.2f, 0.2f));
		shaderProgram.setUniform("light1.diffuse", vec3(0.5f, 0.5f, 0.5f));
		shaderProgram.setUniform("light1.specular", vec3(1.f, 1.f, 1.f));
		shaderProgram.setUniform("light1Pos", vec3(lightM * vec4(0, 0, 0, 1)));

		shaderProgram.setUniform("light2.ambient", vec3(0.2f, 0.2f, 0.2f));
		shaderProgram.setUniform("light2.diffuse", diff);
		shaderProgram.setUniform("light2.specular", spec);
		shaderProgram.setUniform("light2Pos", vec3(lightMD * vec4(0, 0, 0, 1)));
		shaderProgram.setUniform("viewPos", vec3(glm::inverse(T) * vec4(0, 0, 0, 1)));

		for (int k = 0; k < models.size(); k++) {
			vector<mesh> figure = models[k].figure;
			mat4 TM = C * models[k].modelM;
			shaderProgram.setUniform("clipView", TM);
			shaderProgram.setUniform("modelView", models[k].modelM);
			shaderProgram.setUniform("modelInv", glm::transpose(glm::inverse(models[k].modelM)));
			for (int i = 0; i < figure.size(); i++) {
				shaderProgram.setUniform("material.ambient", figure[i].material.ambient);
				shaderProgram.setUniform("material.diffuse", figure[i].material.diffuse);
				shaderProgram.setUniform("material.specular", figure[i].material.specular);
				shaderProgram.setUniform("material.shininess", figure[i].material.shininess);
				glBindVertexArray(figure[i].vertexArray);
				glDrawElements(GL_TRIANGLES, figure[i].indices.size(), GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);
			}
		}
		lightShaderProgram.use();

		vec3 color = vec3(0.2f, 0.2f, 1.f) + diff + spec;
		mat4 move = rotate((float)glfwGetTime() * radians(10.0f), vec3(0.0f, 1.0f, 1.0f));
		mat4 lightM1 = move * lightM;
		lightShaderProgram.setUniform("clipView", C * lightM1);
		lightShaderProgram.setUniform("pathColor", color);
		glBindVertexArray(lightVertexArray);
		glDrawArrays(GL_LINES, 0, 26);
		glBindVertexArray(0);

		lightShaderProgram.setUniform("clipView", C * lightMD);
		lightShaderProgram.setUniform("pathColor", color);
		glBindVertexArray(lightVertexArray);
		glDrawArrays(GL_LINES, 0, 26);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
