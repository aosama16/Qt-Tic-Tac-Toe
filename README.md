![banner](https://user-images.githubusercontent.com/44305804/84823159-300eb880-b01e-11ea-9f2c-db8b899586a1.png)

A Qt project using C++ implementing a GUI game of Tic Tac Toe.

## Simple Class Diagram
![Class Diagram](https://user-images.githubusercontent.com/44305804/84825913-78c87080-b022-11ea-91d0-285812c4d3b5.jpg)

## System Components
- **TitleScreen** [Entry point]: This class is responsible for the GUI of the title screen, its main functionality is to gather game options set by the user, then starting a game by creating a Tic Tac Toe controller with the user options.

- **TTTController** [Controller]: This class is the controller for a Tic Tac Toe game, it takes in game options as input, and controls the view (TicTacToeGame) and the model (Board) according to the game logic specified in this class, it is also responsible for calling the AI agent to play its turn if specified by the game options.

- **Board** [Model]: This class is responsible for representing the underlying model of the game, it is a 2D matrix representation of the GUI that is machine readable, and can be used when running any sort of algorithms on the board.

- **TicTacToeGame** [View]: This class is responsible for the GUI of a game, it is responsible for building the cells of a board, which can be of variable size, and a navigation button to take the user back to the title screen, and a button for resetting the game and playing a new one.

- **AIAgent** [Interface]: This Interface describes the behaviour of any implemented AI agents.

- **MiniMaxAgent** [Implements AIAgent]: This class handles all the logic of picking a cell based on the [MiniMax Algorithm](#MiniMax-Algorithm).

- **NoAgent** [Implements AIAgent]: This class is an empty class that does not play, it specifies the null object behaviour, so it represents the lack of an AI agent, which is useful to avoid using if conditions in code when checking on the existence of an AI agent. 

## Design

### System Flow
The program starts collecting game options using the TitleScreen class, when the user clicks on "Start game", this class creates a TTTController that will handle a Tic Tac Toe game, it will create a model (Board) and a view (TicTacToeGame) and specify the type of AI agent (MiniMax or NoAgent), when a user clicks on a cell the controller tells the view to update the appearance of the cell clicked by setting the player mark (X or O), and it tells the board to update its underlying representation of the board, then it calls the evaluateBoard function from the board class to see if we reached a final state (Someone won or a Tie), if it is a final state, it declares the state via a QMessageBox.

### Design Patterns
These are the design pattern used in this project.

#### MVC
MVC is short for Model View Controller, the main idea behind it is seperation of concerns, instead of having a view and a model that are highly coupled and dependent, the view is concerned only with updating the UI elements and knows nothing about the model and vice-versa.<br>
It also encourages reusability as the model or the view can be easily replaced or used again in another project.<br>
The Tic Tac Toe game uses this design by defining the three main components.
- **Model**: The board class.
- **View**: The TicTacToeGame class.
- **Controller**: The TTTController class.

#### Null object
No Agent is a class that defines a behaviour of a Null agent, it avoids using conditional statement to check whether an agent exists or not, and just uses polymorphism to call the agent, if it is defined to be non existant by the game options, then this empty class will do nothing.

so this code
```
// This check is done at every play call.
if(AiIsChosen)
  AiAgent->play();
```
becomes
```
// If the NoAgent is specified then nothing will happen.
AiAgent->play();
```

#### Observer pattern
Any Qt project will most definitely use this design pattern, as it is the main idea behind Qt's main mechanic, the Signal and Slot system.

## MiniMax Algorithm
This algorithm simulates all possible plays taking turns simulating an AI turn then a Player turn until a final state is reached, then it scores the final state by giving a negative value if the Player wins and a positive value if it wins, then backtracks picking the minimum score if it is the player turn and the max score if it's the AI turn.

Here is an image representing how the Minimix algorithm decides on a position given a board. [Image Credits](https://nestedsoftware.com/2019/06/15/tic-tac-toe-with-the-minimax-algorithm-5988.123625.html)
![minimaxTree](https://nestedsoftware.com/assets/images/2019-06-15-tic-tac-toe-with-the-minimax-algorithm-5988.123625/eo3qr44bp1w96a92t8s2.png)

Two optimization techniques were used in the MiniMax algorithm:
- **Alpha Beta Pruning**<br>
The core idea according to [Wikipedia](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning):<br>
The algorithm maintains two values, alpha and beta, which represent the minimum score that the maximizing player is assured of and the maximum score that the minimizing player is assured of respectively. Initially, alpha is negative infinity and beta is positive infinity, i.e. both players start with their worst possible score. Whenever the maximum score that the minimizing player (i.e. the "beta" player) is assured of becomes less than the minimum score that the maximizing player (i.e., the "alpha" player) is assured of (i.e. beta < alpha), the maximizing player need not consider further descendants of this node, as they will never be reached in the actual play.

- **Depth Cutoff**<br>
Instead of expanding the whole tree until the board has reached a final state, it has a depth limit when expanding the search tree, this means that AI takes a decision without seeing the game till the end. Tic Tac Toe is a simple game and unfortunately it does not need to have a large depth to still be unbeatable, lowering the depth will make the algorithm much faster especially with boards larger than 3x3.

## Testing
In this repository, there is a testing sub project in ./TicTacToeTest/, this unit testing project is based on the Google test unit testing library version 1.10.0

To run theses unit test, change the GOOGLETEST_DIR variable in the TicTacToeTest.pro file to the location of your Google test repository.
```
// TicTacToeTest.pro, line 1
// Change the path to your Google test repository
GOOGLETEST_DIR = ../../Tools/googletest-release-1.10.0
```

### Unit test for the board class:
- Board Class
  - Invalid Access to cells.
  - Valid Access to cells.
  - Evaluating No Winner.
  - Evaluating O wins.
  - Evaluating X wins.
  - Evaluating a Tie.
  - Resetting the board.
- MiniMax Agent
  - The player is the starting the player, and the Ai is one move from winning.
  - The Ai is the starting the player, and the Ai is one move from winning.
  - The player is the starting the player, and the Ai blocks the player from winning.
  - The Ai is the starting the player, and the Ai blocks the player from winning.

## Tools
- Qt 5.12.1
- Qt Creator 4.8.1
- QMake version 3.1
- GNU Make 4.2.1
- GCC version 7.3.0
- Google Test 1.10.0

## Features
- Dynamic board size, Choose any board size to play.
- Play vs a MiniMax AI agent with alpha beta pruning, or play a game with two players taking turns playing.
- Specify whether the AI start first or you start first.
- Specify the Minimax depth cutoff to control difficulty of the MiniMax Agent.<br>
Increasing the depth will affect performance.

## ScreenShots
![screen-1](https://user-images.githubusercontent.com/44305804/84827211-69e2bd80-b024-11ea-82b8-622a51874e23.png)
![screen-2](https://user-images.githubusercontent.com/44305804/84827216-6b13ea80-b024-11ea-99d8-7dca45051e64.png)
