# Puzzle-Games
This is a collection of 6 different puzzle/logic games. A few are well known, popular logic games and the rest are my own design/inspirations. I made this because I really enjoy solving puzzles and using logic, so I figured this would be a great project to try my hand at. It was very fun, and I learned a lot about event-driven programming from this.

### Table of Contents
---

- [Installation](#installation)

### Games

  1. [Minesweeper](#minesweeper)
  2. [Battleship](#battleship)
  3. [Fill the Squares](#fillTheSquares)
  4. [Block Slide](#blockSlide)
  5. [Block Fill](#blockFill)
  6. [Coordination](#coordination)
 
 <br />
 
## Installation  <a name="installation"/>
  - <b> This project is currently only compatible with Windows. </b>
  
  1. Download the files from the most recent release.
  2. Open the .zip archive and extract all the files to a folder of your choosing.
  3. Open the folder and run "PuzzleGames.exe" whenever you wish to play!

 <br />
 
## Games 

<br />
  
## 1. Minesweeper <a name="minesweeper"/>

  Just the standard classic game of Minesweeper, where you are trying to uncover every tile in a grid that isn't a bomb.
  
  <br />

### General Rules
---
  - The game starts when you click on any tile. That tile will never be a bomb.
  
  An example of what a region may look like after you click a tile to start (in this case, the red X was the tile):

  ![](/Pictures/minesweeperStartExample.png)

  - Tiles will either be blank, a bomb, or have a number on them.
  - Tiles with a number on them tell you how many bombs are around it, and blank tiles have none.
  - To win the game, you must carefully deduce which tiles are bombs in order to find every safe tile. 

<br />

### Controls
---
  - Left clicking will reveal the selected tile.
  - Right clicking will flag the selected tile as a bomb.
  - Middle clicking is a nifty tool that will reveal all tiles around a numbered square if all its bombs are flagged. Sound a little confusing? These pictures might help:

 Before middle clicking the "2"       |  After middle clicking the "2"
:-------------------------:|:-------------------------:
![](/Pictures/minesweeperShiftClickBefore.png)  |  ![](/Pictures/minesweeperShiftClickAfter.png)
     
<br />

## 2. Battleship <a name="battleship"/>

  I'm sure you've heard of the classic game of Battleship, where you and an opponent are trying to find each other's ships on a board. This is like that, but a much different     twist on it. In this version, you are trying to find ships on a board with a limited amount of clicks. However, clicking a tile instead reveals the number of ship spaces that   are intersecting with it. This allows the game to be more deductive and less about random guessing.
  
   <br />
   
### General Rules
---
  - The tiles of ships are lettered for convenience.
  - Every click reduces your click counter. If it hits 0, you lose!
  - Clicking a tile will tell you how many ship tiles intersect with it, if it's not a ship.
  - If you reveal part of a ship, that tile turns light pink.
  - Revealing all of a ship will turn all of the ship red, and reduce the ships counter.
  
  These rules can be seen in this picture:
  
  <img src="/Pictures/battleshipTileRevealExample.png" width="400">
    
  - You can see how the ships are lettered A ,B, C, ... , etc.  
  - 3 ships were found, and you can see how they turned completely red. The pink letters E, H, and L are parts of ships that aren't fully uncovered yet.
  - If you count all the ship pieces intersecting with the "11" tile, it is indeed 11.
  
  ---
  
  - Squares can also be darkened if you know they can't have a ship. A successful win might look like this, for example:
  
  <img src="/Pictures/battleshipWinExample.png" width="400">
   
  <br />
  <br />
   
### Controls
---
  - Left clicking a tile will reveal it as a ship, or display how many ship tiles intersect with it.
  - Right clicking will mark/unmark an unrevealed square as a darker color if you know it can't be a ship. This is helpful as the game progresses.
  
<br />
  
## 3. Fill the Squares <a name="fillTheSquares"/>

  In this game, you are trying to fill every square on a grid by moving your mouse around it. You start at a square and go right, up, left, or down. The tricky thing here is that you can't go over any square twice — it has to be one   fluid motion through the whole set of squares. 
  
   <br />
  
### General Rules
---
  - You can start the square filling by clicking any light gray square. 
  - Once you start moving, you can only go up, left, down, or up from your current square. Darker squares are barriers.
  - You can go backwards by just going back the way you came.
  
  These rules are illustrated by the gif below:
  
  ![](/Pictures/fillSquaresFillGif.gif)
    
  ---
  - Resetting the game with the "Reset game" button will give you a new random layout. 
  - You win once you fill every required square blue in one motion.
  
  <br />

### Controls
---
  - Left clicking a light gray square will start the square filling action.
  - Moving the mouse up, down, left, or right from the current position will advance the square filling.
  - Right clicking <b> any </b> tile will cancel the current fill action.

<br />

## 4. Block Slide <a name="blockSlide"/>

  Ever pushed boulders in old Pokémon games or ice blocks in Zelda games? This game was inspired by those types of puzzles. With this game, you have blue blocks on a grid that     can slide around based on user input. Your goal here is to place blue blocks on every red "X" on the board by sliding them around and using barriers. 
  
  <br />

### General Rules
---
  - The arrows at the top will navigate between different handmade puzzles. Currently, there are 10. 
  - You can select any block to highlight all possible moves in light blue.
  - Clicking a light blue square will slide the currently selected block to its position. 
  - Barriers and other sliding blocks will stop any block. This is essential to win. 
  - Once every red X square has a block on it, you win! 

  These rules are shown here:
  
  <img src="/Pictures/blockSlideBasicExampleGif.gif" width="250">

<br />

### Controls
---
  - Left click will select a blue tile. 
  - Left clicking a highlighted light blue tile will move the currently selected block to it.
  - Left clicking the arrows above the game will navigate forward or backward through the various puzzles.
  - Right clicking any tile or pressing the "Reset game" button will both reset the current puzzle.

<br />

## 5. Block Fill <a name="blockFill"/>

  I think Tetris is a pretty cool game, so I thought of a puzzle game with Tetris shaped pieces. In this game, you have a play area with several blocks. Your goal is to move all of them into the designated area and fill it completely. You can even rotate blocks as well, making this fairly difficult.

<br />

### General Rules
---
  - Blocks in the play area can all be selected for moving. 
  - Once you have selected a shape for moving, it will snap to any tile your mouse moves onto. 
  - While dragging a shape, it can be rotated 90 degrees at a time.
  - Shapes cannot overlap other shapes or black barrier tiles.
  - To win, you must fill in the highlighted area with shapes.

<br />

### Controls
---
  - Left clicking on part of a shape will start the dragging motion.
  - Left clicking while dragging on a valid spot will place the shape and allow you to select a different one.
  - Right clicking while dragging will rotate the shape to the right by 90 degrees.

These rules are shown here:
  
  Moving a shape around    |  Rotating a shape         | Overlapping
:-------------------------:|:-------------------------:|:-------------------------:
![](/Pictures/blockFillMoveExample.gif)  |  ![](/Pictures/blockFillRotateExample.gif)  |  ![](/Pictures/blockFillOverlapExample.gif)

<br />

## 6. Coordination <a name="coordination"/>

  I'm not really sure the idea for this one came from. I just thought it would be interesting if you could move several things at once, and that's exactly what you do in this game. Like the block sliding game, there are several X tiles that you have to place blocks on. However, the way you move blocks is completely different in this, and it makes for a very difficult set of puzzles. 

<br />

### General Rules
---
  - You can click and move ANY of the pink squares.
  - Moving one pink square will move all of them at once.
  - Barriers and even other pink squares at times will block movement! This is essential to solving the puzzles.
  - All tiles with a blue "X" must be covered at the same time for you to win. 

To see what movement looks like, just check out these gifs below:
  
  Moving squares around   |  Movement with a barrier      
:-------------------------:|:-------------------------:
![](/Pictures/coordinationMoveExample.gif)  |  ![](/Pictures/coordinationBarrierExample.gif) 
  
<br />

### Controls
---
  - Left clicking any pink square will start a dragging operation with it (like the Block Fill game.)
  - Left clicking again while dragging will place all pink tiles at once.
  - Clicking the arrows above the game will change hte current puzzle.
  - Clicking "Reset game" will reset the position of all pink squares.

<br />
