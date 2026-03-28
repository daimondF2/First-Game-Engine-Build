// Game Enigne.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define GLFW_INCLUDE_NONE 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>



void framebuffer_size_callback(GLFWwindow* window, int width, int height) //for user resize registers callback func of the window everytime window is resized
{ // framebuffer size function takes a GLFWwindow as its first argument and two integers indicating the new window dimensions. Whenever the window changes in size, GLFW calls this function and fills in the proper arguments for you to process.
    glViewport(0, 0, width, height);

}


void processInput(GLFWwindow* window) //handles inputs
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //gets key identify if escape pressed if true close window
        glfwSetWindowShouldClose(window, true);
}
int main()
{
    if (!glfwInit()) {
        std::cout << "Failed initialize glfw" << std::endl;
        return -1;
    }

    // Tell GLFW we want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //for Mac OS X

    //creating window
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL); //glfwcreatewindow(length width name objects)
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    //GLAD manages function pointers for OpenGL so we want to initialize GLAD before we call any OpenGL function:
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //tells OpenGL the size of the rendering window so OpenGL knows how we want to display the data and coordinates with respect to the window.
    glViewport(0, 0, 800, 600); //The first two parameters of glViewport set the location of the lower left corner of the window. 
    //The third and fourth parameter set the width and height of the rendering window in pixels, which we set equal to GLFW's window size.

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //for resize

    while (!glfwWindowShouldClose(window)) //tells the window to keep drawing imagesa and not single image
    {   
        //input
        processInput(window); //call this checking if pressed

        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //sets screen color
        glClear(GL_COLOR_BUFFER_BIT);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}








// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
