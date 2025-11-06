
#include <stdio.h>
#include <math.h>
// #include <time.h>
// #include <string.h>
#include <raylib.h>

// constants
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define GRAVITATIONAL_ACC 1e-2

typedef struct
{
    float x;
    float y;
    float dx; // change in x component
    float dy;
    float vx;
    float vy;
    float radius;
    Color color;
    float reboundCoefficient;
} Ball;

void drawBall(Ball b)
{
    DrawCircle(b.x, b.y, b.radius, b.color);
}



int main()
{

    /**
     * TODO
     * 1. initial velocity = 0 -> fall according to gravity downwards
     * ..option to initialize x component?
     * 2. bounce (spring force?)
     * 3. slowly lose energy due to friction
     * 4. stop
     *
     */
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bouncy Ball");
    SetTargetFPS(130);

    float centerX = SCREEN_WIDTH / 2.0;
    float centerY = SCREEN_HEIGHT / 2.0;
    float ballRadius = 30;
    float boundaryRadius = 200;

    Ball bouncy = (Ball){centerX, centerY, 0, 0, 0, 0, ballRadius, PURPLE};

    // bouncy.reboundCoefficient = 0.8; // v_ref = v_inc * coeff 

    // bouncy.dx = 1.0;
    // bouncy.dy = 1.0;
    bouncy.dx = 0.0;
    bouncy.dy = 0.0;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        bouncy.x += bouncy.dx; // important for gradual increments
        bouncy.y += bouncy.dy;
        bouncy.dy += GRAVITATIONAL_ACC;

        float diffX = bouncy.x - centerX; // points difference
        float diffY = bouncy.y - centerY;
        float squaredDiffX = (bouncy.x - centerX) * (bouncy.x - centerX);
        float squaredDiffY = (bouncy.y - centerY) * (bouncy.y - centerY);


        drawBall(bouncy);
        DrawCircleLines(centerX, centerY, boundaryRadius, YELLOW); // center changes -> position changes

        if (sqrtf(squaredDiffX + squaredDiffY) + bouncy.radius >= boundaryRadius)
        {

            bouncy.dx *= -1;
            bouncy.dy *= -1 ;
        }


        EndDrawing();
    }

    CloseWindow();

    return 0;
}