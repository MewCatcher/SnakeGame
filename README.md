Snake Game with AIs
===================

General
-------------------
  My writing this game was for practising "OpenGL" & "AI" programming.<br/>
  Well, thoughts are easy, but coding is a bit hard for newbie. XD<br/>

Build
-------------------
### Linux
  I wrote all codes on openSUSE, thus Linux users are able to build it easily.<br/>

		make

  Just that easy! But you will fail without libGL, libGLU, libglut and libfreetype's devel vers.<br/>
  So, REMEMBER to prepare the libs above!<br/><br/>

  Additionally, Freetype used a Truetype font by path, so you have to do:

        cd build
        ./SnakeGame

  Or, just double-click the "./build/SnakeGame" to run.<br/><br/>

  Note: if you installed both freetype and freetype2,
  you may meet some collision error: CANNOT FIND <ftheader.h>...<br/>

		mv /usr/include/freetype2/freetype/ /usr/include/freetype2/freetype_bak/
		ln -s /usr/include/freetype2/freetype/ /usr/include/freetype/

  That's harmless, in my opnion. :)<br/>

### Win32
  After I wrote all codes over, I will adjust my sources, then you will see a tutorial.<br/>

### MacOS
  I will try to borrow a MacBook and finish this job. XD<br/>

Game Rule
-------------------
  Compete with AI, you should eat more and live longer than other AIs.<br/>
