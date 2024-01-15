# Assignment 2 - RT1 ROS Nodes

## Overview
This repository contains the solution for the second assignment of the RT1 course. The assignment involved the creation of ROS nodes in C++ to perform specific tasks related to robot navigation and information retrieval.


### Node (Action Client) explanation
- Allows a user to input a target position for a robot to navigate to.
- Supports canceling the operation and reassigning a new target destination.
- Implemented using an action client.
- Publishes the robot's position and velocity as a custom message.
- Utilizes values from the `/odom` topic.


## Node PseudoCode


```cpp
Initialize ROS node
Initialize action client for PlanningAction

Define callback function for action feedback:
  Extract and display feedback information

Define callback function for /odom topic:
  Extract information, create custom message, and publish it

Main loop:
  Wait for the action server to start

  Set up subscribers and publisher

  While ROS is ok:
    Display user menu
    Read user choice

    If choice is 1:
      Read target coordinates (x, y)
      Send goal to action server

    Else if choice is 2:
      Display cancellation message
      Cancel the current goal
      Exit the loop

    Else if choice is 3:
      Display current robot position and state

    Else:
      Display an error message

    Process callbacks

Exit the program


