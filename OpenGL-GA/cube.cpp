#include <vector>
#include <cmath>
#include <SDL.h>

// Define the Point class to represent a point in 3D space
class Point {
public:
    double x, y, z;

    Point() : x(0), y(0), z(0) {}

    Point(double x, double y, double z = 0) : x(x), y(y), z(z) {}

    double operator[](int i) const {
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }

    double& operator[](int i) {
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }
};

typedef std::vector<double> Vector;
typedef std::vector<Vector> Matrix;

// Function to perform matrix multiplication
Matrix dot(const Matrix& a, const Matrix& b) {
    Matrix result(a.size(), Vector(b[0].size(), 0));
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < b[0].size(); j++) {
            for (size_t k = 0; k < b.size(); k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

// Function to transform a point using a matrix
Point transform(const Matrix& matrix, const Point& point) {
    Matrix p = { {point.x}, {point.y}, {point.z} };
    Matrix r = dot(matrix, p);
    return Point(r[0][0], r[1][0], r[2][0]);
}

// Function to translate a point
Point translate(const Point& shift, const Point& point) {
    return Point(point.x + shift.x, point.y + shift.y, point.z + shift.z);
}

// Function to project a 3D point onto a 2D plane (simple orthographic projection)
Point project(const Point& point) {
    // For orthographic projection, we can ignore the z-coordinate
    return Point(point.x, point.y);
}

// Function to connect two points by drawing a line between them
void connect(SDL_Renderer* renderer, const std::vector<Point>& points, int i, int j) {
    Point a = project(points[i]);
    Point b = project(points[j]);
    SDL_RenderDrawLine(renderer, static_cast<int>(a.x), static_cast<int>(a.y), static_cast<int>(b.x), static_cast<int>(b.y));
}

// Function to get the rotation matrix based on angles
Matrix getRotationMatrix(double angleX, double angleY, double angleZ) {
    Matrix rotationX = {
        {1, 0, 0},
        {0, cos(angleX), -sin(angleX)},
        {0, sin(angleX), cos(angleX)}
    };

    Matrix rotationY = {
        {cos(angleY), 0, sin(angleY)},
        {0, 1, 0},
        {-sin(angleY), 0, cos(angleY)}
    };

    Matrix rotationZ = {
        {cos(angleZ), -sin(angleZ), 0},
        {sin(angleZ), cos(angleZ), 0},
        {0, 0, 1}
    };

    // Combined rotation matrix
    return dot(rotationZ, dot(rotationY, rotationX));
}

//int main(int argc, char* argv[]) {
//    // Initialize SDL
//    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
//        printf("Error initializing SDL: %s\n", SDL_GetError());
//        return -1;
//    }
//
//    const int WIDTH = 800;
//    const int HEIGHT = 600;
//
//    // Create an SDL window
//    SDL_Window* window = SDL_CreateWindow(
//        "Rendering 3D Cube",
//        SDL_WINDOWPOS_CENTERED,
//        SDL_WINDOWPOS_CENTERED,
//        WIDTH,
//        HEIGHT,
//        SDL_WINDOW_SHOWN
//    );
//
//    if (!window) {
//        printf("Error creating window: %s\n", SDL_GetError());
//        SDL_Quit();
//        return -1;
//    }
//
//    // Create an SDL renderer
//    SDL_Renderer* renderer = SDL_CreateRenderer(
//        window,
//        -1,
//        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
//    );
//
//    if (!renderer) {
//        printf("Error creating renderer: %s\n", SDL_GetError());
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return -1;
//    }
//
//    // Define the cube vertices
//    std::vector<Point> points = {
//        Point(-1,  1,  1),
//        Point(1,  1,  1),
//        Point(1, -1,  1),
//        Point(-1, -1,  1),
//        Point(-1,  1, -1),
//        Point(1,  1, -1),
//        Point(1, -1, -1),
//        Point(-1, -1, -1)
//    };
//
//    // Scaling factor
//    const double scale = 100;
//
//    // Screen center
//    Point screenCenter(WIDTH / 2.0, HEIGHT / 2.0, 0);
//
//    bool running = true;
//    SDL_Event event;
//
//    double angleX = 0.0;
//    double angleY = 0.0;
//    double angleZ = 0.0;
//
//    while (running) {
//        // Event handling
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT) {
//                running = false;
//            }
//        }
//
//        // Clear the screen
//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//        SDL_RenderClear(renderer);
//
//        // Update rotation angles
//        angleX += 0.01;
//        angleY += 0.01;
//        angleZ += 0.01;
//
//        // Get the rotation matrix
//        Matrix rotationMatrix = getRotationMatrix(angleX, angleY, angleZ);
//
//        // Apply transformations to the cube points
//        std::vector<Point> transformedPoints;
//        for (const Point& p : points) {
//            // Rotate the point
//            Point rotatedPoint = transform(rotationMatrix, p);
//
//            // Scale the point
//            rotatedPoint.x *= scale;
//            rotatedPoint.y *= scale;
//            rotatedPoint.z *= scale;
//
//            // Translate the point to the center of the screen
//            rotatedPoint = translate(screenCenter, rotatedPoint);
//
//            transformedPoints.push_back(rotatedPoint);
//        }
//
//        // Set drawing color to black
//        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//
//        // Draw cube edges
//        // Front face
//        connect(renderer, transformedPoints, 0, 1);
//        connect(renderer, transformedPoints, 1, 2);
//        connect(renderer, transformedPoints, 2, 3);
//        connect(renderer, transformedPoints, 3, 0);
//
//        // Back face
//        connect(renderer, transformedPoints, 4, 5);
//        connect(renderer, transformedPoints, 5, 6);
//        connect(renderer, transformedPoints, 6, 7);
//        connect(renderer, transformedPoints, 7, 4);
//
//        // Connecting edges
//        connect(renderer, transformedPoints, 0, 4);
//        connect(renderer, transformedPoints, 1, 5);
//        connect(renderer, transformedPoints, 2, 6);
//        connect(renderer, transformedPoints, 3, 7);
//
//        // Present the rendered frame
//        SDL_RenderPresent(renderer);
//
//        // Delay for a short period to control frame rate
//        SDL_Delay(16); // Approximately 60 FPS
//    }
//
//    // Clean up
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}
