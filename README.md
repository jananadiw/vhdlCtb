# vhdlCtb
Dice Game with VHDL (VHDL program for creating bitmap files that can be downloaded to the EDA3000.)

### Dice Game: Rules

#### 1st roll

If the sum is 7 or 11, the win
If the sum is 2, 3, 12, lose
In other cases, the sum is scored and rolled second

#### 2nd roll

If the sum equals the score for the first roll, then win
If the sum is 7,
In other cases, keep rolling second until you win or lose.

### Dice Game Finite State Machine (FSM)

#### Start state (S0): 
If the roll button (RB) is pressed, go to state S1, otherwise go to state S0.

#### Rolling state (S1):
After the dice are rolled, if the sum is 7 or 11, go to state S2; if the sum is 2, 3, or 12, go to state S3. Or record the sum in the score and go to state S4.

#### Win decision state (S2):
After outputting Win (Win), if the new start button (NB) is pressed, go to state S0, otherwise go to state S2.
The judgment state (S3): After outputting the (Lose), if the new start button (NB) is pressed goes to state S0, otherwise goes to state S3.

#### Second start state (S4): 
If the rolling button (RB) is pressed, go to state S5, otherwise go to state S4.

#### Secondary Rolling State (S5): 
After the dice are rolled, if the sum recorded in S1 is the same as the sum of the dice, go to state S2; if the sum is 7, go to state S3; otherwise, go to state S4.

#### End state (S6): End the game.
