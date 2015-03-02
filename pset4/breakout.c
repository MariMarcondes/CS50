//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle size
#define PAD_HEIGHT 15
#define PAD_WIDTH 80

// briks size
#define BR_HEIGHT 24
#define BR_WIDTH 36


// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // ball velocity
    double velocityx = 5 * drand48();
    double velocityy = 5 *drand48();


    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        add(window, paddle);
        add(window, ball);
        add(window, label);

                waitForClick();

        while (true) {
            GEvent event = getNextEvent(MOUSE_EVENT);
            if (event != NULL) {
                if(getEventType(event) == MOUSE_MOVED) {
                    double x = getX(event) - getWidth(paddle) / 2;
                    setLocation(paddle, x, 522);
                }
            } 
            
            move(ball, velocityx, 0);

            GObject object = detectCollision(window, ball);            
            if (object == NULL) {
            if(getX(ball) + getWidth(ball) >= getWidth(window)) {
                velocityx = -velocityx;
            } else if (getX(ball) <= 0) {
                velocityx = -velocityx;
            }
            pause(2);
            
            move(ball, 0, velocityy);
                        
            if(getY(ball) + getHeight(ball) >= getHeight(window)) {
                lives--;
                removeGWindow(window, ball);
                waitForClick();
                if (lives > 0) {
                ball = initBall(window);
                add(window, ball);} else {
                closeGWindow(window);
                return false;
             }
            } else if (getY(ball) <= 0) {
                velocityy = -velocityy;                
            }         
            pause(2);       
            } else if(object != NULL) {
                if (strcmp(getType(object), "GRect") == 0) {
                    if(object == paddle) {
                        if(velocityy >= 0) {
                        setLocation(ball, getX(ball), 518);
                        velocityy = -velocityy;
                        } else {
                            velocityy = + velocityy;}
                    }   else if(object != paddle) {
                        removeGWindow(window, object);
                        velocityy = -velocityy;
                        points++;
                        updateScoreboard(window, label, points);
                    }
              }
            }
            
}
}

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int brickrow = 8;
    int brickcol = 100;
    char* color[] = {"9933FF", "9966FF", "9999FF", "99CCFF", "99FFFF"};

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            GRect brick = newGRect(brickrow, brickcol, BR_WIDTH, BR_HEIGHT);
            setFilled(brick, true);
            setColor(brick, color[i]);
            brickrow += 38;
            add(window, brick); 
        }
        brickcol += 30;
        brickrow = 8;   
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(190, 280, 20, 20);
    setFilled(ball, true);
    setColor(ball, "FF0033");   
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(160, 522, PAD_WIDTH, PAD_HEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "FFFF00");   
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-20");
    setColor(label, "#C0C0C0");
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
