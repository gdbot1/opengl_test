#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int createShaderProgram(const char* vert, const char* frag); 
char* getShaderData(const string& path); 

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

    int program = createShaderProgram(vertData, fragData);

    glUseProgram(program);

    glClearColor(0, 0, 0, 1);
    
    float theta = 0;
    
    while (!glfwWindowShouldClose(window)) {
	theta++;

        glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	glRotatef(theta, 0, 0, 1);
        
	glBegin(GL_TRIANGLES);
	
	glColor3f(1, 0, 0);
	glVertex2f(-1, 0);
	
	glColor3f(0, 1, 0);
	glVertex2f(0, 1);
	
	glColor3f(0, 0, 1);
	glVertex2f(1, 0);

	glEnd();	

	glPopMatrix();

        glfwSwapBuffers(window);   
	glfwPollEvents();     
    }

    glfwTerminate();

    cout << "Hello world" << endl;
    return 0;
}

int createShaderProgram(const char* vert, const char* frag) {
    unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
    
    glShaderSource(vertShader, 1, &vert, nullptr);
    glCompileShader(vertShader);

    unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(fragShader, 1, &frag, nullptr);
    glCompileShader(fragShader);

    unsigned int program = glCreateProgram();

    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    return program;
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