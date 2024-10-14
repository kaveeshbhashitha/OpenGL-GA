#include <GLFW/glfw3.h>

void render() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);
    // Set the line color to white for better visibility on dark backgrownd
    glColor3f(1.0f, 1.0f, 1.0f);      

    // Begin drawing a line using OpenGL routines
    glBegin(GL_LINES);
        //start point of the line
        glVertex2i(160, 15);   
        //end point of the line
        glVertex2i(66, 145);          
    glEnd();
    // Flush the OpenGL commands
    glFlush();                        
}

//int main() {
//    // Initialize GLFW
//    if (!glfwInit()) {
//        return -1;
//    }
//
//    // Create a windowed mode window and its OpenGL context
//    GLFWwindow* window = glfwCreateWindow(300, 300, "OpenGL Line Segment with GLFW", NULL, NULL);
//    if (!window) {
//        glfwTerminate();
//        return -1;
//    }
//
//    // Make the window's context current
//    glfwMakeContextCurrent(window);
//
//    // Set up the viewport and the orthographic projection matrix
//    glViewport(0, 0, 300, 300);
//    // Set up an orthogonal projection matrix
//    glOrtho(0.0, 300.0, 0.0, 300.0, -1.0, 1.0); 
//
//    // Main loop
//    while (!glfwWindowShouldClose(window)) {
//        // Call the render function
//        render();         
//        // Swap the front and back buffers
//        glfwSwapBuffers(window);
//        // Poll for and process events
//        glfwPollEvents();           
//    }
//
//    // Clean up and exit
//    glfwTerminate();
//    return 0;
//}
