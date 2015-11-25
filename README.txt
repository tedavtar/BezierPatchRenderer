Name: Ted Avtar
No partner

Login: cs184-ak

Platform runs on: OS X

Location of source code: /example_00/wtf.cpp

VIDEO:
Here is a video of my project in action. I used QuickTime player’s screen recording…
https://youtu.be/MUM0y4y18Wg

(Use the start of this video as instructions on how to run if necessary—watch it at 720p in “theater mode”)



How to run:
1) Go to the as3 directory (not example_00)
2) do “./test teapot.bez .01 -a” or “./test teapot.bez .1”
3) if there’s a problem, run make clean then “make -f test.make” and try again
   if you want to modify wtf.cpp and rerun with changes, do this remake.

Functionality and usage:
I implemented all the required features. A single directional light goes down the z-axis.
The only noteworthy things to specify are how exactly to pan/rotate/zoom.
The following works on my MacBook:
1) The arrow keys specify rotation. Just hit them to find out their effects!
2) Shift + “+” results in zooming in.  Basically however you normally type the “+” key, do the same and this will zoom the object.  Misusing is just hit the “-“ key.
3) And as instructed, holding shift and pressing the arrow key will translate object in that key direction.

Images:
Check the image folder in this directory—that is, as3
These same images can also be found at http://inst.cs.berkeley.edu/~cs184-ak/ and click Assignment3

image—01: How “./test teapot.bez .1” starts off as. Uniform tessellation
image-02: Result of a translation and some rotations.
image-03: Result of pressing “w”.  Wireframe mode.
image-04: Press “w” again to toggle out of wireframe. Then press “s” to toggle smooth shading.
image-05: How “./test teapot.bez .01 -a” starts off as. Adaptive tessellation
image-06: Same image except zoomed in + wireframe.
image-07: Uniform tessellation arch.  Zoomed in.  Step size .1
image—08: Uniform tessellation arch.  Zoomed out.  Step size .25. Note that this is significantly sharper than the previous image which had lower step size.

Credit:
I have commented where I took code snippets—from an openGL forum concerning keyboard functions and rotations.  Furthermore, I started my code with skeleton openGl code from this website: http://www.glprogramming.com/red/chapter05.html.  Namely, example 5-1.
This is very similar to example00 code we were provided, except more concise and well—I had issues with directional lighting that using this fixed.

All functional code is mine alone.  However, I made heavy use of the code provided in the last slide of the pertinent lecture.


 
