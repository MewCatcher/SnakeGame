Snake Game with AIs
===================

General
-------------------
  I wrote this game was for practising "OpenGL" & "AI" programming.
  Well, thoughts are easy, but coding is a bit hard for newbie. XD

Build
-------------------
### Linux
  I wrote all of this on openSUSE, thus Linux users are able to build it easily.
    make
  Just that easy! But you will fail without libGL, libGLU, libglut and libfreetype's devel vers.
  Note: if you installed both freetype and freetype2, you may meet some collision error.
    mv /usr/include/freetype2/freetype/ /usr/include/freetype2/freetype_bak/
    ln -s /usr/include/freetype2/freetype/ /usr/include/freetype/
  That's harmless, in my opnion. :)

### Win32
  After I wrote all codes over, I will adjust my sources, then you will see a tutorial.

### MacOS
  I will try to borrow a MacBook and finish this job. XD

Rule
-------------------
  Compete with AI, you should eat more and live longer than others.

Copyright
-------------------
  MewCatcher all rights reserved.
  All the sources are under LGPL. :)


