# Battleship game


### The Classic Battleship Game is a strategy game where players take turns trying to guess the locations of their opponent's ships and sink them. It's only possible to play against the Computer.


## Gameplay
### The game is played on a square 10x10 board, where each player has their own board. The objective is to strategically place your ships on your board and then take turns firing shots at your opponent's board to sink their ships. The first player to sink all of their opponent's ships wins the game.


## The features I've so far implemented:
1. ### Board and Coordinates Logic:
   - Utilized coordinates to represent cells on the board.
   - Implemented the logic to display the game board in the console.
   - Developed a mechanism to show the user's ship placements and the hits on the boards.
     

2. ### Ship Placement Logic:
   - Created functions to handle ship placement based on the rules of the game.
   - Ensured that ships cannot be placed in adjacent cells, either vertically, horizontally.
   - Provided feedback to the user if the placement is invalid or restricted to a specific orientation.


3. ### Firing Logic:
   - Implemented the firing mechanism for the user to target cells on the opponent's board.
   - Visualized the user's shots on the board, highlighting hit and miss cells.
   - Developed the logic to determine if the user hit an opponent's ship and updated the board accordingly.
   - Restricted the user from firing at the same cell multiple times.
   - Designed the computer opponent to randomly select cells to fire at.


4. ### Game Over Logic:
   - Detected if all the ships of either the user or computer have been sunk.
   - Added the game over condition to determine when one player wins.
   - Displayed a message indicating the winner of the game.


# TODO
 - Code Commenting: Add detailed comments throughout the code to improve readability and maintainability.
 - Smart Computer AI: Enhance the computer's firing strategy to make intelligent choices based on previous hits and misses.
 - Marking Surrounding Cells of Sunk Ships: Implement a feature to mark cells surrounding a sunk ship as "hit" to prevent unnecessary shots from both the user and the computer.
 - Console Output Improvements: Address any existing bugs related to console output and ensure smooth and accurate display of game information.
 - Console Game Experience: Refine the game to run seamlessly in a console environment.
 - Bug Fixes: Investigate and resolve game-stopping bugs to ensure a stable gameplay experience.



