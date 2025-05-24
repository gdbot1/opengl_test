#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>

#include "vao.h"
#include "circle.h"
#include "texture.h"

using namespace std;

int createShaderProgram(const char* vert, const char* frag); 
char* getShaderData(const string& path); 
void checkShaderLog(unsigned int shader);

int main () {
    if (!glfwInit()) {
        cout << "FATAL ERROR: glfw init" << endl;
        return -1;
    }

    glfwDefaultWindowHints();
    
    GLFWwindow* window = glfwCreateWindow(500, 500, "OpenGL C++", nullptr, nullptr);

    if (!window) {
        cout << "FATAL ERROR: window creating" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        cout << "FATAL ERROR: glad not inited" << endl;
        return -1;
    }
    
    const char* vertData = getShaderData("../shaders/test.vert");
    const char* fragData = getShaderData("../shaders/test.frag");

    cout << vertData << endl;

    cout << fragData << endl;

    int program = createShaderProgram(vertData, fragData);

    glUseProgram(program);
    
    float theta = 0;

    cout << "load texture" << endl;

    Texture texture("../textures/01.png");

    cout << "texture loaded" << endl;

    int sampler = 0;

    texture.bindSampler(sampler);

    int tex_uniform = glGetUniformLocation(program, "tex");

    glUniform1i(tex_uniform, sampler);

    //vertex vbo
    vector<float> vertices = {
	-1, 0,
	0, 1,
	1, 0
    };
    
    auto vertex_vbo = make_shared<VBO>(vertices, 2);

    //color vbo
    vector<float> colors = {
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
    };
    
    auto color_vbo = make_shared<VBO>(colors, 3);

    //color vbo
    vector<float> texCords = {
	0, 1,
	0.5f, 0,
	1, 1
    };
    
    auto texCord_vbo = make_shared<VBO>(texCords, 2);

    vector<shared_ptr<VBO>> vbos = {vertex_vbo, color_vbo, texCord_vbo};

    //vao
    VAO vao(vbos, vertex_vbo->getLength());

    Circle circle(0.5f, -0.5f, 0.5f, 128, 1, 1, 1);
    
    while (!glfwWindowShouldClose(window)) {
	theta++;

        glClear(GL_COLOR_BUFFER_BIT);

	vao.draw();
	circle.draw();

	glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    delete[] vertData;
    delete[] fragData;

    cout << "hello world 1.3" << endl;

    return 0;
}

int createShaderProgram(const char* vert, const char* frag) {
    unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
    
    glShaderSource(vertShader, 1, &vert, nullptr);
    glCompileShader(vertShader);

    checkShaderLog(vertShader);

    unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(fragShader, 1, &frag, nullptr);
    glCompileShader(fragShader);

    checkShaderLog(fragShader);

    unsigned int program = glCreateProgram();

    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    return program;
}

void checkShaderLog(unsigned int shader) {
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        // Получение лога ошибки
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

char* getShaderData(const string& path) {
    ifstream file(path, ios::binary | ios::ate);//открыть в бинарном режиме + курсор в конце (ate = at end)
    
    if (!file.is_open()) {
	cout << "FATAL ERROR: shader file can't be opened" << endl;
	return nullptr;
    }

    streamsize file_size = file.tellg();//получить текущую позицию (так-как файл был открыт с конца, то позиция будет равна длине файла)
    file.seekg(0, ios::beg);//установка курсора в начале. 0 - это позиция относительно начала файла (begin)

    char* buffer = new char[file_size + 2];//для \0 и ещё 1 символа, который удаляется при смещении
    if (!file.read(buffer, file_size)) {
	cout << "FATAL ERROR: file can't be readen" << endl;
	
	delete[] buffer;//удаление баффера
	return nullptr;
    }
    
    buffer[file_size] = '\0';

    return buffer;
}