#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

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