# Short-Circuit-Pinball-J.E.

Welcome to our tribute of "Short Circuit Pinball" made with Box2D.

### Short Circuit v.1.0

###We have not included the next original features:
- 3D animations.
- Magnetism mechanic of the top circle.
- Pinball "mini-shake".
- Led movement control.
- Black box sound, blue lights, ball lost sound.

###We have adapted some mechanics of the game to make it playable (it has some bugs that made the game loop infinite)
- Blue button mechanism (gives you an extra ball if you enter a ball into it).
- Black box mechanism (it gives extra score when you cross it.
- Score bonifications and multipliers.


##CONTROLS
- INTRO: launch the ball
- LEFT / "A": move left and up levers.
- RIGHT / "D": move right lever.
- F1: activate the Debug Mode to see all the chains, bodies and sensors implemented.
      You can click the ball and hold the mouse button to move it arround the map.
- SPACEBAR: restart the game after the Game Over.

##CORE GAME AND MECHANICS

###OBJECTIVE
You have to reach the maximum score by hitting and interacting with all the elements 
that are distributed around the pinball (leds, buttons, panels...).
Each of them gives you a certain amount of score.

###LOSE CONDITION
You lose the game if you lose the initial 5 balls you have.
After that, you can restart the game by pressing the correct control.

###CORE GAME & MECHANICS
When you start a live, the game gives you 20 seconds of "security time". It means that if you lose the ball,
the game will give you another ball to continue the round (so you don't lose 1 live).

- If you active all the leds of a group, they will be restarted.
- You can collide with the ball that's inside the ramp to reach the top diana.
- The red turbine gives you points every time you cross it.
- You can make the ball pass through the black box to get some extra score.
- If the ball enters into the blue button, a 40 seconds timer will start. The game will launch a new ball 
  to interact with during this period. If you don't lose the ball during these seconds, you will be 
  rewarded with an extra ball (adding more fun to the gameplay!).
  If you lose the ball during this period of time, the button will eject the ball and you won't get the extra ball.


##THAT'S ALL FOLKS! HOPE YOU ENJOY IT!


Authors: 

- Elliot Jimenez: https://github.com/elliotjb
- Jordi Oña: https://github.com/Jordior97

Original Game Link: http://www.minijuegos.com/juego/short-circuit-pinball

Repository Link: https://github.com/elliotjb/Short-Circuit-Pinball-J.E..git



