#include <GLFW/glfw3.h>
#include <stdlib.h>

void plotPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Bresenham's Line Drawing Algorithm for 0 < m < 1.0
void drawLineBresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    // Determine the direction of increment (for both x and y)
    int sx = (x1 < x2) ? 1 : -1;  
    int sy = (y1 < y2) ? 1 : -1;  

    int err = dx - dy;  

    while (true) {
        plotPixel(x1, y1);  

        // Check if we've reached the endpoint
        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;  

        // Adjust the error and move x or y
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;  
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;  
        }
    }
}


int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(400, 300, "Bresenham Line Drawing", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(0.0, 400.0, 0.0, 300.0, -1.0, 1.0);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set color to white
    glColor3f(1.0f, 1.0f, 1.0f); 

    // Example line endpoints
    int x1 = 50, y1 = 350;
    int x2 = 350, y2 = 200;

    drawLineBresenham(x1, y1, x2, y2);

    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}