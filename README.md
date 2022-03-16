# Stacks and Queues
A puzzle game based on the mechanics of the abstract data structures Stacks and Queues.

### Current Game: version 1.0.2 ###

#### Concepts ####

Stack: A stack or LIFO (last in, first out) is an abstract data type that serves as a collection of elements, with two principal operations: push adds an element to the collection; pop removes the last element that was added. This game uses another operation of a stack: peek, which shows the last element that was added without removing it.

Queue: In a queue or a FIFO data structure, the first element added to the queue will be the first one to be removed. Enqueue is used to add an element to the collection and dequeue is used to remove. Peek or front is used to show the first element to be added without removing it.

#### Description ####

Each level starts with a line of balls entering the screen from the right hand side in a specific starting order. They always follow a main yellow line that spans across the screen from one tube (the right hand side input tube from which the balls enter the screen) to another (an exit tube that is always directly opposite to the input tube). There are detours from this main yellow path that can lead to other structures like stacks. The goal of the player is to rearrange that starting order with the use of the onscreen structures. The vertical structures are stacks and the horizontal ones are queues.

When a ball encounters a stack by coming close to the point where the stack touches the yellow path, it is automatically pushed into the stack and stored. Stacks have a capacity greater than the number of balls onscreen so the player won't have to worry about running out of space. The player can peek at the top ball of the stack or pop it out and have it resume it's journey on the yellow path by clicking on the stack with the right or left mouse buttons respectively.

A ball is pushed into a queue when the ball touches it's right end. The queue can be peeked at/fronted by clicking on the right mouse button and it can be dequeued with the left mouse button. Queues have an inexhaustible capacity like stacks.
If the player satisfies the order displayed on the purple bar at the bottom of the screen, the level is won; if not, the player loses.

#### Controls ####

Gameplay keys: 
<br>Q - Selects and highlights green, the ball on the left+.
<br>E - Selects and highlights green,  the ball on the right+.
<br>W - Makes the selected ball move up *.
<br>A - Makes the selected ball move left *.
<br>S - Makes the selected ball move down *.

"+" = according to original order.
<br>"*" = when a path is available. Balls are not allowed to move outside the path, they take the next available turn. This can be overridden by another key press, balls only store one turn direction at a time.

Mouse buttons:
<br>Left mouse - Pops the stack/ Dequeues the queue.
<br>Right mouse - Peek at the stack/ Fronts the queue.

Other:
<br>Esc - Exits the level without saving.
<br>P - Pauses the level.
<br>Enter - Resumes the level if paused. Starts the game if MainMenu screen fails to load and backup Menu is shown.

### Development ###

#### Motivation ####

To make a fun and entertaining puzzle game. Originally intended to provide a more significant educational experience but we have found that it can only currently serve as exposure to these data structures based on user feedback.

#### Technical ####

This game was written mainly in C++ and uses SFML, a multimedia API. Bugs and issues are reported on this repository's issues page. Icons lock.png and questionmark.png are royalty free clipart. 

#### Features implemented ####

1. Gameplay: 
<br>a) Basic AI of the numbered balls. They are able to detect and navigate the yellow path from one tube to another without player input regardless of the path they are sent to. They can check if player input for direction change is valid, stores up to one request for direction change and takes the next valid turn.
<br>b) Player controls: keyboard and mouse.
<br>c) Level status bar to show the correct order to win the game. Lets the player know if he won, lost or there was an error with the game.
<br>d) Stacks can be used to store and reverse the order of the balls pushed into it. Peek and pop functions included.
<br>e) (NEW) Queues can be used to store the balls pused into it. Front and dequeue functions included.
2. Main menu design and functionality.
3. Game can be paused and resumed, as well as exited and restarted.
4. (NEW) Level Select screen and unlock levels by winning previous levels.
5. (NEW) Help page for player.
6. (NEW) 3 Levels of increasing difficulty.

#### Planned features for NUS Orbital 2016 Sprint 3 ####

1. Queues, we had not been able to implement queues in the previous sprint, but the foundation for the integration of a Queue class and objects have been setup in the other class methods. ✅
2. 3 Levels of increasing difficulty. ✅
3. Help page for player. ✅
4. Music and sound effects. To make the game more engaging.

### Download ###
Disclaimer: This game is best suited for screens that can accomodate 1200x800 game windows.

Direct Download available for Mac OSX El Capitan (not yet tested on other versions): Click on "Stacks and Queues 1.0.app.zip" on the repository's <> Code page then the Download button.

#### Install from source ####

Dependencies : SFML

OSX Xcode: Follow installaton procedure for sfml on Xcode: 
http://www.sfml-dev.org/tutorials/2.0/start-osx.php Set up a .xcodeproj with sfml and add the files from this repository's Stacks and Queues folder to the project. Add Resource files from this repository to the Resource folder. Compile and Build.

Windows Visual Studio: Follow installation procedure for sfml on Visual Studio: http://www.sfml-dev.org/tutorials/2.3/start-vc.php. Set up new project and add files from this repository's Stacks and Queues VS folder. Add Resource folder to project. Compile and Run.

### Demos ###
Version 1.0.2: https://www.youtube.com/watch?v=k6PHwyAVn8Q&ab_channel=ShwethaRavi
<br>Version 0.1: https://www.youtube.com/watch?v=JgGBw237Mik&ab_channel=ShwethaRavi

<style>
    .table {
        width: 70%;
        text-align: center;
    }
    .table th {
        background: grey;
        word-wrap: break-word;
        text-align: center;
    }
    .table tr:nth-child(1) { background: red; }
    .table tr:nth-child(2) { background: orange; }
    .table tr:nth-child(3) { background: green; }
</style>

<div class="table">
### Development ###

|Remarks Color|Meaning                                   |FIELD3|FIELD4                                                                                                        |
|-------------|------------------------------------------|------|--------------------------------------------------------------------------------------------------------------|
|             |Progress made                             |      |                                                                                                              |
|             |Minor task complete                       |      |                                                                                                              |
|             |Milestone reached                         |      |                                                                                                              |
|             |Minor setback                             |      |                                                                                                              |
|             |Major setback                             |      |                                                                                                              |
|             |                                          |      |                                                                                                              |
|Date         |Task                                      |Hours |Remarks                                                                                                       |
|10/05/2016   |Liftoff                                   |6.00  |Project Ideation                                                                                              |
|             |                                          |      |Was overseas                                                                                                  |
|17/05/2016   |Mission Control 1                         |6.00  |Bootstrap tutorial. Java and C++ tutorials during break                                                       |
|24/05/2016   |Mission Control 2                         |6.00  |Game Development class and environment setup                                                                  |
|25/05/2016   |Experimenting with game development       |6.00  |Made small two player game to learn: Game loops, Frames, Controls, etc                                        |
|27/05/2016   |More tutorials, using custom header files |5.00  |                                                                                                              |
|29/05/2016   |Issue #1: Drawing inTube                  |1.00  |Opened and worked on it.                                                                                      |
|             |Sprint Total:                             |30.00 |                                                                                                              |
|29/05/2016   |Issue #4: Drawing a path for the balls... |1.00  |Opened and worked on it.                                                                                      |
|31/05/2016   |Issue #1: Drawing inTube                  |0.50  |Completed and Closed.                                                                                         |
|02/06/2016   |Issue #3: Drawing outTube                 |0.50  |Opened, completed and closed.                                                                                 |
|03/06/2016   |Issue #4: Drawing a path for the balls... |1.00  |Completed and closed.                                                                                         |
|04/06/2016   |Issue #7: Balls detect yellow line...     |3.00  |Opened issue. Worked on "Moving the balls attempt 1" branch.                                                  |
|05/06/2016   |Issue #7: Balls detect yellow line...     |4.00  |Worked on "Moving the balls attempt 1" branch. Balls detect pixel color in front of them, quite slow.         |
|07/06/2016   |Issue #7: Balls detect yellow line...     |3.00  |Worked on "Moving the balls attempt 1" branch. Optimisation                                                   |
|08/06/2016   |Issue #7: Balls detect yellow line...     |2.00  |Closed "Moving the balls attempt 1", very buggy. Worked on "Moving the balls attempt 2" branch.               |
|10/06/2016   |Issue #7: Balls detect yellow line...     |8.00  |Worked on "Moving the balls attempt 2" branch.                                                                |
|15/06/2016   |Issue #7: Balls detect yellow line...     |3.00  |Worked on "Moving the balls attempt 2" branch. Store path coordinates and junction detection.                 |
|17/06/2016   |Issue #7: Balls detect yellow line...     |5.00  |Merged "Moving the balls attempt 2" branch.                                                                   |
|18/06/2016   |Issue #13: Level::draw()... bug           |2.00  |Reported, fixed bug and closed issue.                                                                         |
|18/06/2016   |Issue #15: Pushing into Stacks            |4.00  |Set up code to store stack location and balls detect them.                                                    |
|20/06/2016   |Issue #15: Pushing into Stacks            |4.00  |Time consuming bug, balls don't detect stacks. Overhauled code, shifted relevant functions to Level class.    |
|22/06/2016   |Issue #15: Pushing into Stacks            |6.00  |Merged "Pushing into stacks" branch.                                                                          |
|22/06/2016   |Issue #17: Change ball selection          |0.50  |Opened and Closed. Changed player controls.                                                                   |
|22/06/2016   |Issue #19: Select Stack                   |1.00  |Worked on "Select and pop stack" branch                                                                       |
|23/06/2016   |Issue #19: Select Stack                   |1.50  |Worked on "Select and pop stack" branch. Detects mouse click on stack at Level class and Stack class.         |
|24/06/2016   |Issue #19: Select Stack                   |6.00  |Worked on "Select and pop stack" branch                                                                       |
|25/06/2016   |Issue #19: Select Stack                   |3.00  |Worked on "Select and pop stack" branch. Stack can be selected by left mouse button                           |
|26/06/2016   |"Select and pop stack" branch             |2.00  |Worked on "Select and pop stack" branch. Implementing pop function                                            |
|28/06/2016   |"Select and pop stack" branch             |6.00  |Merged "Select and pop stack" branch.                                                                         |
|28/06/2016   |Issue #8: Making level info vectors...    |1.50  |Opened 08/06/2016. Closed it. Shifted level info initialisation into main program, changed all necessary code.|
|28/06/2016   |Issue #25: Set and check level complete...|0.50  |Opened and Closed. Level checks for win condition.                                                            |
|28/06/2016   |Issue #24: Use right mouse button         |1.50  |Opened and Closed. Right mouse button used to peek at top ball in stack.                                      |
|28/06/2016   |Issue #22: outTube requirement bar        |0.50  |Opened 24/06/2016. Closed it. Player can see win condition and level status. Level 1 can be played.           |
|28/06/2016   |Issue #26: Dynamically generate...        |0.50  |Opened and Closed. Resource access full path not required.                                                    |
|             |Sprint Total:                             |71.50 |                                                                                                              |
|29/06/2016   |Issue #20 Create Queue class              |1.00  |Opened 22/06/2016 and created basic queue class. Will close when it works with all game functions.            |
|29/06/2016   |Issue #20 Create Queue class              |1.00  |Attempted to add queues to Level::draw(). Bug encountered when generating yellow path to queues.              |
|29/06/2016   |Issue #20 Create Queue class              |4.00  |Opened and worked on "stack and queue yellow path".                                                           |
|02/07/2016   |Issue #27 resourcePath and Visual Studio  |1.00  |Opened 28/06/2016. Created a new folder with modified game files for windows visual studio.                   |
|07/07/2016   |Issue #27 resourcePath and Visual Studio  |1.00  |Made all necessary modifications for this version.                                                            |
|08/07/2016   |Issue #20 Create Queue class              |2.00  |Closed "stack and queue yellow path". Worked on bug.                                                          |
|13/07/2016   |Issue #20 Create Queue class              |7.00  |Opened and worked on "queues" branch                                                                          |
|13/07/2016   |Issue #20 Create Queue class              |2.00  |Fixed bug, queue class is completed and integrated with the game. Merged "queues" branch and closed issue.    |
|21/07/2016   |Issue #31 Next Level System               |3.00  |Opened 15/07/2016. Worked on "next-level branch". Created level 2 and unlock level system.                    |
|21/07/2016   |Issue #31 Next Level System               |2.00  |Worked on "next-level" branch. Level Select system, encountered arrow key double count bug in level 2.        |
|22/07/2016   |Issue #31 Next Level System               |0.50  |Merged "next-level" branch, level selection system complete, but bug in level 2 remains.                      |
|23/07/2016   |Issue #18 Q and E keys                    |1.00  |Opened 22/06/2016. Fixed double count bug. Closed issue.                                                      |
|23/07/2016   |Issue #30 Add "Help and Controls" page    |1.00  |Opened 13/07/2016. Closed after creating and adding help page.                                                |
|23/07/2016   |Issue #34 One file for menu system        |2.50  |Opened, completed and closed. Two files (.cpp and .hpp) control all menu pages instead of 6                   |
|23/07/2016   |Issue #11 Pathcoords Vector               |2.00  |Tried to implement the proposed changes but found that the current system works better. Closed issue          |
|24/07/2016   |Issue #35 Level 3                         |3.00  |Opened, completed and closed. Level 3 integrated!                                                             |
|24/07/2016   |Issue #12 Public and private functions    |1.00  |Privatised certain functions and attributes, added relevant comments describing them for better practice.     |
|24/07/2016   |"SQv1 .app bundle for mac OSX" branch     |0.50  |Compiled an app bundle for the game on OSX for version 1.                                                     |
|24/07/2016   |SQ version 1.0.1                          |1.00  |Redid the help page and released the mac OSX app bundle for version 1.0.1                                     |
|             |Sprint Total:                             |30.50 |                                                                                                              |
|             |Grand Total:                              |132.00|                                                                                                              |
</div>
