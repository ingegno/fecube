// Licence: Creative Commons, Attribution
// Created: 04-2014 by bmcage http://www.thingiverse.com/bmcage

// An LED lamp holder for easter

//diameter of the horizontal circle in mm
diameter = 100;  //[10:100]
//vertical scale factor to make it an egge (choose number from 1 to 2)
eggscale = 1.2;
//single shell thickness, take your nozzle diameter as minimum
th_shell = 0.4;
//base cylinder diameter in mm.
base_diam = 90; //[5:50]
//base extra height under egg
base_extra_height=2; // [0:20]
//The part to generate. Print both for rigidity, or increase shell thickness if only one!
part="both"; // [inner,outer,both]
//pattern to imprint on the egg
pattern = "circle"; //[triangle,circle,custom]
//size of the pattern as a scale, use something from 0.1 to 10
patternscale = 30; //
//if custom as pattern, the polygon to use as pattern (default here is simple square)
custom_polygon = [[[-1,1],[1,1],[1,-1],[-1,-1]],[[0,1,2,3]] ]; //[draw_polygon:100x100]
//how to put the pattern on the egg: random, a cylinder at the equator, a spiral from bottom to top, a double spiral, or onlyt at the top of the egg
repeattype = "topproject"; //[random, cylinder,spiral,doublespiral,topproject]
patternrepeat = 45;  //[1:100]
//random seed used to generate the pattern
random_seed = 10;  //[0:3200]
//rotate pattern itself around or not
rotate_pattern="true";  //[true,false]
//spiral complete circles from bottom to top
spiral_circles = 4; //[1:10]
//double helix extra offset
dh_angle=45; //[0:180]
//cuttoff below this height
h_cuttoff = 20; //[0:50]
//text to write on equator
text = "My LED Cube";
//fraction of the circumference to use for the text (value between 0.1 and 0.9)
textcircum = 0.9;
//show dxf
showdxf = "False";  //[True,False]
//scale the pattern
dxfscale  =0.06;
//dxf file to load
dxf_file= "/home/benny/Documents/kinderen/saya/toothless_v4.dxf";
dxfrepeattype = "cylinder"; //[cylinder,topproject]
dxfpatternrepeat = 6;  //[0:100]
//extra angle over the equator
dxfcilangle = 38; //[-90:90]


use <utils/build_plate.scad>;
use <MCAD/fonts.scad>;

//for display only, doesn't contribute to final object
build_plate_selector = 0; //[0:Replicator 2,1: Replicator,2:Thingomatic,3:Manual]

//when Build Plate Selector is set to "manual" this controls the build plate x dimension
build_plate_manual_x = 100; //[100:400]

//when Build Plate Selector is set to "manual" this controls the build plate y dimension
build_plate_manual_y = 100; //[100:400]

build_plate(build_plate_selector,build_plate_manual_x,build_plate_manual_y); 

//code begins, dummy module to indicate this
module test(){
  echo("test");
}

// sin(alpha) = R_C/R_S, cos(alpha) = sqrt(1- (R_C/R_S)**2)
// cutoff sphere is R_S*(1-cos(alpha)
sinalpha = base_diam/2 / (diameter/2);
cosalpha = sqrt(1-pow(sinalpha,2));
rcuttoff = diameter/2*(1-cosalpha);

module easterlamp(diam, transdist)
{
translate([0,0,transdist]) 
 	{
	 difference() 
		{
 		 scale([1,1,eggscale]) sphere(r = diam/2, $fn=60);
	 	 union(){
 		 scale([1,1,eggscale]) sphere(r = diam/2-th_shell*eggscale, $fn=60);
    	 translate([0,0,-eggscale*diam]) cylinder(r=base_diam/2, h=eggscale*diam);
		 }
		}
	}
}

module filledfoot()
{
cylinder(r=base_diam/2, h=base_extra_height+eggscale*rcuttoff+2, $fn=40);
}

module foot()
{
difference()
	{
 	 filledfoot();
 	 translate([0,0,-0.05])cylinder(r=base_diam/2-2*th_shell*eggscale, h=base_extra_height+eggscale*rcuttoff+2.1, $fn=40);
	}
}


module singlepattern()
{
//translate([0,0,eggscale*diameter/2+base_extra_height-0.1])
	{scale([patternscale,patternscale,1])
		{
		 if (pattern == "triangle")
		 { translate([0,0,1*eggscale*diameter/4]) linear_extrude(height = eggscale*diameter/4, convexity = 10)
           polygon(points=[[-1,0],[0,1],[1,0]]);
		 }
		 if (pattern == "circle")
		 { translate([0,0,1*eggscale*diameter/4]) cylinder(r=1, h=eggscale*diameter/4, $fn=10);
		 }
		 if (pattern =="custom")
		 {translate([0,0,1*eggscale*diameter/4]) linear_extrude(height = eggscale*diameter/4, convexity = 10)
			 polygon(points = custom_polygon[0], paths = custom_polygon[1]);
		 }
	   }
	}
}

module dxfpattern()
{
rotate([0,0,90])
scale([dxfscale,dxfscale,1])
translate([0,0,1*eggscale*diameter/4])
linear_extrude(height = eggscale*diameter/4)
   import (file = dxf_file);
}

module rotsinglepattern(rotangle)
{
 if (rotate_pattern=="true")
	{rotate([0,0,rotangle]) singlepattern();
	} else {
	 singlepattern();
	}
}

module manydxfpatterns()
{

if (showdxf == "True")
{
union()
 {
 if (dxfrepeattype == "cylinder")
  {
  for (i=[1:dxfpatternrepeat])
	{
	 translate([0,0,eggscale*diameter/2+base_extra_height-0.1])
		rotate([0,90-dxfcilangle,i*360/dxfpatternrepeat]) 
		{
		 dxfpattern();
	 	}
	}
  }
 if (dxfrepeattype == "topproject")
  {
	{
	 translate([0,0,eggscale*diameter/2+base_extra_height-0.1])
		{
		 dxfpattern();
	 	}
	}
  }
 }
}
}

module manypatterns()
{
random_numbers=rands(0,360,2*patternrepeat,random_seed);
union(){
 if (repeattype == "random")
  {
  for (i=[1:patternrepeat])
	{
	 translate([0,0,eggscale*diameter/2+base_extra_height-0.1])
		rotate([0,10+random_numbers[i-1]/360*160,random_numbers[i]]) 
		{
		 rotsinglepattern(random_numbers[i]);
	 	}
	}
  }
 if (repeattype == "cylinder")
  {
  for (i=[1:patternrepeat])
	{
	 translate([0,0,eggscale*diameter/2+base_extra_height-0.1])
		rotate([0,90,i*360/patternrepeat]) 
		{
		 rotsinglepattern(random_numbers[i]);
	 	}
	}
  }
 if (repeattype == "topproject")
  {
  //for (i=[1:patternrepeat])
	{
	 translate([0,0,eggscale*diameter/2+base_extra_height-0.1])
		//rotate([0,10+random_numbers[i-1]/360*160,random_numbers[i]]) 
		{
		 rotsinglepattern(random_numbers[0]);
	 	}
	}
  }
 if (repeattype == "spiral" || repeattype == "doublespiral")
  {
  for (i=[1:patternrepeat])
	{
	 translate([0,0,eggscale*diameter/2+base_extra_height-0.1])
		rotate([0,10+i*160/patternrepeat, i*360/patternrepeat*spiral_circles]) 
		{
		 rotsinglepattern(random_numbers[i]);
	 	}
	}
  if (repeattype == "doublespiral")
   {
   for (i=[1:patternrepeat])
	 {translate([0,0,eggscale*diameter/2+base_extra_height-0.1]) 
	  //difference()
     { 
		 rotate([0,10+i*160/patternrepeat, -i*360/patternrepeat*spiral_circles+dh_angle]) 
		 {
		  rotsinglepattern(random_numbers[i]);
	 	 }
	  //cube([diameter/2,diameter/2,diameter/2], center=true);
     }
	 }
   }
  }
 }
}


//process the text, we have beta_1 for the symbol, use beta_2 for border!
thisFont=8bit_polyfont();
x_shift=thisFont[0][0];
y_shift=thisFont[0][1];
theseIndicies=search(text,thisFont[2],1,1);
wordlength = (len(theseIndicies));

factorygap = 3;
scale_x = PI * diameter * textcircum/wordlength / x_shift;
scale_y = (diameter*eggscale/5) / y_shift;
//thicknessword = text_thickness * nozzlediam;

// Create the Text
module alltext() {
    for( j=[0:(len(theseIndicies)-1)] ) 
        {
			translate([0,0,eggscale*diameter/2+base_extra_height-0.1])
			rotate([90,0,j*360 * textcircum/wordlength])
        	translate([0,0,2.8*eggscale*diameter/8]) scale([scale_x,scale_y,1]){
          linear_extrude(height=1.2*eggscale*diameter/8) 
            polygon(points=thisFont[2][theseIndicies[j]][6][0],paths=thisFont[2][theseIndicies[j]][6][1]);
        }
      }
}

centeregg = eggscale*diameter/2+base_extra_height-0.1;

module fullobject()
{
if (showdxf == "True")
{
  dxfpattern();
}
if (part =="both")
	{
	 easterlamp(diameter-2*th_shell*eggscale+0.05, centeregg);
	}

if (part =="inner")
	{difference() {
   	 easterlamp(diameter-2*th_shell*eggscale-0.05, centeregg);
		 foot();
	 }
	}

if (part == "outer" || part == "both")
	{
 	 foot();
	 difference()
	 {
		color("Blue",0.5) easterlamp(diameter, centeregg);
		manypatterns();
		manydxfpatterns();
      alltext();
	 }
	}
}


//module easterlamp()
//{
if (h_cuttoff>0)
{
translate([0,0,-h_cuttoff+0.01])
 difference()
	{
	 fullobject();
	 translate([-diameter/2,-diameter/2,-0.01]) cube([diameter, diameter,h_cuttoff]);
	}
} else {
 fullobject();
}
//}
//alltext();
//easterlamp();
//manypatterns();
