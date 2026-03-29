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
// DONT TOUCH ABOVE THIS IS JUST FOR THE WINDOW
//GLSL has a vector datatype that contains 1 to 4 floats based on its postfix digit.
//Since each vertex has a 3D coordinate we create a vec3 input variable with the name aPos.
// We also specifically set the location of the input variable via layout(location = 0)


const char* vertexShaderSource = "#version 330 core\n" //basic vertex shader
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";      

const char* fragmentShaderSource = "#version 330 core\n" //fragment shader puts color on triangle
"out vec4 FragColor;\n"
"void main() {\n"
"FragColor = vec4(1.0, 0.5, 0.2, 1.0); // orange\n"
"}\0";

int main()
{
    //glfw setup
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
    
    //glad start
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
    
    //ABOVE IS STANDARD
    //compile shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); //provide the type of shader we want to create as an argument to glCreateShader. Since we're creating a vertex shader we pass in GL_VERTEX_SHADER.
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    //check for error
    int  success;
    char infoLog[512];//check if compilation was successful with glGetShaderiv. 
    //If compilation failed, we should retrieve the error message with glGetShaderInfoLog and print the error messag
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //NEW CODE AND FUNC
    //compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //check for error
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //shader program links the shaders
    unsigned int shaderProgram = glCreateProgram(); //creates func and returns ID ref to new created prog obj
    glAttachShader(shaderProgram, vertexShader); //attaching and linking shaders together
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //check errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Shader link error: " << infoLog << std::endl;
    }
    //deleting shaders because we linked and dont need them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    

    //defining a triangle vertices
    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };
    //vertex buffer (first occurance of an openGl object) -unique id correspoding to the buffer
    unsigned int VBO;
    glGenBuffers(1, &VBO); // generates ID
    unsigned int VAO; //vertex array object - opengl requires as it knows what to do with vertex inputs
    glGenVertexArrays(1, &VAO);
    //binds the buffers
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // array buffer allows bind several buffers at once as long as they are different used for vertex buffer obj
    
    //any buffer calls we make (on the GL_ARRAY_BUFFER target) will be used to configure the currently bound buffer, 
    //which is VBO. Then we can make a call to the glBufferData function that copies the previously defined vertex data into the buffer's memory:
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //glBufferData is a function specifically targeted to copy user-defined data into the currently bound buffer.
    //telling OPENGL how to read vertexesd                                                  Stride tells us the space between consecutive vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//(which vertex(location), size of attribute, data type, data normalised y/n, stride, void (offset where pos data begins in buffer))
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) //tells the window to keep drawing imagesa and not single image
    {   
        //input
        processInput(window); //call this checking if pressed

        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //sets screen color
        glClear(GL_COLOR_BUFFER_BIT);
        //DRAW TRIANGLE
        glUseProgram(shaderProgram);// using shaders
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);


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
