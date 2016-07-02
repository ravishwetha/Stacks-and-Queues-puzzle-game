# Stacks and Queues
A puzzle game based on the mechanics of the abstract data structures Stacks and Queues.

### The Game: version 0.1 ###

Each level starts with a line of balls entering the screen from the right hand side in a specific starting order. They always follow a main yellow line that spans across the screen from one tube (the right hand side input tube from which the balls enter the screen) to another (an exit tube that is always directly opposite to the input tube). There are detours from this main yellow path that can lead to other structures like stacks. The goal of the player is to rearrange that starting order with the use of the onscreen structures. The vertical structures are stacks (currently orange rectangles) and queues are meant to be horizontal structures (Coming Soon). 

When a ball encouters a stack by coming close to the point where the stack touches the yellow path, it is automatically pushed into the stack and stored. Stacks have a capacity greater than the number of balls onscreen so the player won't have to worry about running out of space. The player can peek at the top ball of the stack or pop it out and have it resume it's journey on the yellow path by clicking on the stack with the right or left mouse buttons respectively. If the player satisfies the order displayed on the purple bar at the bottom of the screen, the level is won; if not, the player loses.

#### Controls ####
