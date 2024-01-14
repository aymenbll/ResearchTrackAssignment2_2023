# Robot Control System

## Overview

This repository contains code for controlling a robot using ROS (Robot Operating System). The system includes an action client for reaching a goal, feedback handling, and odometry data processing.

## Code Explanation

### Pseudocode

```plaintext
Initialize ROS node "aclient"
Create an action client for the "reaching_goal" action server
Wait for the action server to start
Create subscribers for feedback ("sub_fb") and odometry ("sub_pos_vel")
Create a publisher for a custom message ("pub_pos_vel")
Define callback function CallBack1 to handle action feedback
    Extract feedback information and display it
Define callback function CallBack2 to handle odometry data
    Extract information from the odometry message
    Create a custom message and publish it
Main Loop:
    while ROS is running
        Display menu options:
            1. Set a new target
            2. Cancel the operation
            3. Get robot coordinates and state
        Take user input for choice
        If choice is 1:
            Prompt user for target coordinates (x, y)
            Create a goal message and send it to the action server
        If choice is 2:
            Display cancellation message
            Cancel the current action goal
            Exit the loop
        If choice is 3:
            Display current robot position (X, Y) and state
        If choice is invalid, display an error message
        Spin once to process callbacks and update ROS events
    End Main Loop
Shutdown the ROS node

