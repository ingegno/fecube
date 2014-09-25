Manual sketches
===============
You can find the sketches from the manual on the [sketches overview page.](manual/sketches.md)


Ingegno Fe Cube
===============

The Ingegno Fe Cube is a RGB LED cube consisting of 9 LEDS, so like the Iron metal a [Cubic crystal system](http://en.wikipedia.org/wiki/Cubic_crystal_system)

A Fe Led Cube is driven with an Arduino. It can be used as an educational package into Arduino and making skills like lasercutting and 3D printing. This repository contains 

1. Data for a Scribus manual in English and Dutch (Italian planned)
2. Accompaning Arduino sketches to learn how the Cube can be programmed
3. The final complete sketch to load on a Fe cube and interact with it

There are many LED cubes available, and many manuals to create one exist. Nevertheless, in our view there was still a gap to be filled. A LED cube is ideal to impress visitors with, but we want to make it clear that this is a project within the grasp of beginners. The construction is not hard, and the programming can be kept simple (at least the parts the user would like to change). Hence a manual to go from no knowledge to a working Fe LED Cube.

Specific in the Arduino implementation is that it is shot based, so not a pattern table as is common. A shot that can load a pattern is present though for simple use. Next there is an event system to interact with the environment. In the Basic version this is a push button. In the Interactive version a distance sensor is added.

Prototypes
==========

The cube is a work in progress. Current protypes:

Prototype 3: Basic version
--------------------------
A lasercut frame, with plexiglass top. 3D printed optional cover. A pushbutton to interact with the cube: switch on/off and selecting an effect

![](https://raw.github.com/ingegno/fecube/master/manual/pic/prototype03_a.JPG "Third prototype: basic version")
![](https://raw.github.com/ingegno/fecube/master/manual/pic/prototype03_b.JPG "Third prototype: basic version - no cover")
![](https://raw.github.com/ingegno/fecube/master/manual/pic/prototype03_c.JPG "Third prototype: basic version - different effect")

Prototype 02
------------
A soldering board used to hold the components. In the future this must be hidden at the backside, now visible.

![](https://raw.github.com/ingegno/fecube/master/manual/pic/prototype02_a.JPG "Second prototype")

Prototype 01
------------
Based on conductive ink. Working, but pins come loose too easily

![](https://raw.github.com/ingegno/fecube/master/manual/pic/prototype01.JPG "Firstprototype")

The Manual
==========
The manual is aimed for use in Arduino courses. It starts with the basis: 

1. How to make a LED function with Arduino
2. Extend to handle a RGB LED
3. Create effects with the LED in a frame based manner
4. Extend to a FE Cube on a breadboard
5. Construct the FE Cube
6. Extend the code to generate effects on the FE Cube

Cool stuff the Cube can do
==========================
Some of the cool stuff you can do with the cube

1. The obvious use: use it as a light in the dark!
2. Double click to use it as dice roll. Currently 3 D6 dices are rolled
3. Show the theory of color mixing: two or more colors are blinked faster and faster. What color will result?
4. More to come ....

This course was created for use in an [Ingegno](http://ingegno.be) workshop. If you use it, send us a thumbs up if you liked it!
