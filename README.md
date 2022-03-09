# Puzzle-Games
This is a collection of 6 different puzzle/logic games. A few are well known, popular logic games and the rest are my own design. 
### Table of Contents
---
### Games
  1. [Minesweeper](#minesweeper)
  2. [Battleship](#battleship)
  3. [Fill the Squares](#fillTheSquares)
  4. [Block Slide](#blockSlide)
  5. [Block Fill](#blockFill)
  6. [Coordination](#coordination)
 
 <br />
  
## 1. Minesweeper <a name="minesweeper"/>
---
  Just the standard classic game of Minesweeper, where you are trying to uncover every tile in a grid that isn't a bomb.
  
  <br />

### General Rules
---
  - The game starts when you click on any tile. That tile will never be a bomb.

    An example of what a region may look like after you click a tile to start (in this case, the red X was the tile):

    ![](/Pictures/minesweeperStartExample.png)

  - Tiles will either be blank, a bomb, or have a number on them.
  - Tiles with a number on them tell you how many bombs are around it, and blank tiles have none.
  - To win the game, you must carefully deduce which tiles are bombs in order to find every safe tile. A completed game may look like this, for example:

    <img src="/Pictures/minesweeperWinExample.png" width="400">

<br />

### Controls
---
  - Left clicking will reveal the selected tile, as shown below: 

      Before revealing         |  After revealing
    :-------------------------:|:-------------------------:
    ![](/Pictures/minesweeperRevealBefore.png)  |  ![](/Pictures/minesweeperRevealAfter.png)

  - Right clicking will flag the selected tile as a bomb. Here's an example:

      Before flagging         |  After flagging
    :-------------------------:|:-------------------------:
    ![](/Pictures/minesweeperFlagBefore.png)  |  ![](/Pictures/minesweeperFlagAfter.png)
    
  - Middle clicking is a nifty tool that will reveal all tiles around a numbered square if all its bombs are flagged. Sound a little confusing? These pictures might help:

     Before middle clicking the "2"       |  After middle clicking the "2"
    :-------------------------:|:-------------------------:
    ![](/Pictures/minesweeperShiftClickBefore.png)  |  ![](/Pictures/minesweeperShiftClickAfter.png)
     
<br />

## 2. Battleship <a name="battleship"/>
---
  I'm sure you've heard of the classic game of Battleship, where you and an opponent are trying to find each other's ships on a board. This is like that, but a much different     twist on it. In this version, you are trying to find ships on a board with a limited amount of clicks. However, clicking a tile instead reveals the number of ship spaces that   are intersecting with it. This allows the game to be more deductive and less about random guessing.
  
   <br />
   
### General Rules
---
  - The tiles of ships are lettered for convenience.
  - Every click reduces your click counter. If it hits 0, you lose!
  - Clicking a tile will tell you how many ship tiles intersect with it, if it's not a ship.
  - If you reveal part of a ship, that tile turns light pink.
  - Revealing all of a ship will turn all of the ship red, and reduce the ships counter.
  
  ---
  
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
  
  These controls are illustrated by the pictures above.
  
<br />
  
## 3. Fill the Squares <a name="fillTheSquares"/>
---
## 4. Block Slide <a name="blockSlide"/>
## 5. Block Fill <a name="blockFill"/>
## 6. Coordination <a name="coordination"/>
