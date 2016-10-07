/**
  * @file globals.h
  * @author Andrew Hoover
  * @date 9/25/2016
  * @brief Global variables.
  *
  * Holds global variables. These are used to communicate from the toolbar
  * input in the MainWindow functions to the instance of GLWidget created
  * by Qt for the OpenGL display.
  *
  * There might be a better way to communicate the information without relying
  * on globals. Something to look into in the future.
  */

#ifndef GLOBALS_H
#define GLOBALS_H

#endif // GLOBALS_H

// If false, the scene is paused, don't update the environment.
bool CONTINUE = false;
// If true, reset the environment to the given preset.
bool RESTART = false;
// Set the starting location of the particles to a given preset value.
int PRESET = 1;
// Gravitation constant of the universe.
float GRAVITY_FORCE = 0.1;
