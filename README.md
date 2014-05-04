Fe Cube
=======

The Fe Cube is a RGB LED cube consisting of 9 LEDS, so like the Iron metal a [Cubic crystal system](http://en.wikipedia.org/wiki/Cubic_crystal_system)

A Fe Led Cube can be driven with an Arduino. This repository contains 

1. a manual in latex in English and Dutch (Italian planned)
2. Accompaning Arduino sketches


Specific in the Arduino implementation is that it is shot based, so not a pattern table as is common. A shot that can load a pattern is present though for simple use.

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
The manual is aimed for use in Arduino courrses. It starts with the basis: 

1. How to make a LED function with Arduino
2. Extend to handle a RGB LED
3. Create effects with the LED in a frame based manner
4. Extend to a FE Cube on a breadboard
5. Construct the FE Cube
6. Extend the code to generate effects on the FE Cube


This course was created for use in an [Ingegno](http://ingegno.be) workshop. 
