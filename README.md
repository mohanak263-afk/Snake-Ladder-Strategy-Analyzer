# Snake & Ladder Strategy Analyzer

A Snake & Ladder game and strategy analysis tool that uses Breadth-First Search (BFS) to compute the minimum number of moves required to win and reconstruct the optimal winning path on a standard board configuration.

## Features

* Minimum Moves to Win using BFS
* Optimal Path Reconstruction
* Standard Snake & Ladder Board Simulation
* Extra Turn on Rolling a 6
* Roll History Tracking
* Player Win Statistics Storage
* Graph-Based Game Modeling

## Technologies Used

* Python
* Data Structures & Algorithms
* Breadth-First Search (BFS)
* Graph Theory
* SQLite

## Problem Solved

The project models the Snake & Ladder board as a graph where each square represents a node and dice outcomes create edges between nodes. BFS is used to determine the shortest path to the destination while accounting for snakes, ladders, and extra turns earned by rolling a 6. The application also stores player win statistics and displays roll history during gameplay.
