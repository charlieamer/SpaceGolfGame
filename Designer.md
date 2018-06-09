# Space golf design guidelines
Rules of the game are the same as of those in golf. You have a ball and the aim of the game is to put the ball in hole. However, the trick here is that golf is played in space, and your ball is attracted to planets and hole. When ball hits a planet, it is slowed down a bit. If ball goes very fast it will bounce off the planet, and it will stick to the planet otherwise. After ball sticks to the planet player is finished with that turn.
This game is supposed to be a mobile game, although for testing purposes it can be played on PC.
This game should run in portrait mode.
If you believe some of the stuff could be done better, feel free to correct it, with my approval.
Game is made in C++, not unity, or some other popular game engine.
- Graphics library: bgfx
- UI library: CEGUI (has editor called CEED)
- Level editor: GLEED2D

# General info

## Rules of golf
- Aim is to finish with lowest score.
- Every level has a value called "par". If it takes player exactly that amount of turns to finish level, he gets 0 points.
    - Example: Level has par of 4, player finishes in 4 turns, player gets 0 points.
- If he finishes in more turns then "par", he will get ("his score" - "par") points.
    - Example: Level has par of 4, player finishes in 6 turns, player gets 2 points.
- If he finishes in less turns then "par", he will get ("his score" - "par") points.
    - Example: Level has par of 4, player finishes in 1 turn (a.k.a. "hole in one"), player gets -3 points.
- Scores may be negative (which is a good thing for player)

## Level info
- Each course will have 9 levels
    - Each level will be ranked from easiest to hardest
- Game will contain 2 courses (which means 18 levels in total)
- Each level can contain 1 or more holes (regular golf has only 1 hole, but we can make it fancy)
- Every level has its bounds

# Design requests

## General look
- Not too cartoony
    - Example of what is NOT good for me: https://media.indiedb.com/images/games/1/21/20407/ingame_mockup_03.jpg
    - Example of what IS good for me: http://fredrikdesigns.com/wp-content/uploads/2016/01/game_screen-1024x768.png
- Cool UI
    - Example: https://ricardojorgeportfolio.files.wordpress.com/2014/06/ui_game_screen_003.jpg
- I already have a deal with this guy for his font to be used for this game: https://www.dafont.com/arcade-classic-pizz.font
    - If you don't like it, you can use different font.
- You can design stuff like panels, buttons, etc, and I will put them in correct positions with correct font.

## Main menu
- "Course select" button
- "About" button
- "Exit" button

## About menu
- Will contain all the people who have devoted their time to game
- You'll have to account for 1-2 persons

## Course select menu
- Will contain list of all courses available to play
    - Every element of list will contain a "slideshow", that will toggle screenshots of all levels every second.
- "Back" button

## Level select menu
- Will contain list of all levels inside selected course
    - Every element of list will contain a preview image of the level.
    - It also has to contain previous score for that level (1-2 digits, may be negative number)

## Gameplay
- 20 different planets WITHOUT GLOW (may be small "planetoids", like moons)
    - When ball hits planet it will slow down a bit
- 3 different stars (they have to be big like sun)
- Ball
- Trajectory guidence (where ball will go after player releases finger)
- Level bounds (suggestion: asteroid field)
    - When ball hits level bounds it will simply bounce off without slowing down
- Victory animation (suggestion: fade out to another screen)
    - "Next level" button
    - "Back to level select" button
    - "Final score for that level" text
- UI
    - Current number of turns
    - Par number for that level
