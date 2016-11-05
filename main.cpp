
#include <stdio.h>     // - Just for some ASCII messages
#include "gl/glut.h"   // - An interface and windows 
                       //   management library
#include "visuals.h"   // Header file for our OpenGL functions


/////////////// Main Program ///////////////////////////

int main(int argc, char* argv[])
{ 
  // initialize GLUT library state
  glutInit(&argc, argv);
	
  // Set up the display using the GLUT functions to 
  // get rid of the window setup details:
  // - Use true RGB colour mode ( and transparency )
  // - Enable double buffering for faster window update
  // - Allocate a Depth-Buffer in the system memory or 
  //   in the video memory if 3D acceleration available	
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
 
  
  // Define the main window size and initial position 
  // ( upper left corner, boundaries included )
  glutInitWindowSize(1000,700);
  glutInitWindowPosition(100,0);
  
  // Create and label the main window
  glutCreateWindow("Interstellar");
  
  // Configure various properties of the OpenGL rendering context
  Setup();
  
  // Callbacks for the GL and GLUT events:
 
  // The rendering function 
  glutDisplayFunc(Render);
  glutReshapeFunc(Resize);
  glutKeyboardFunc(Keyboard);
  glutIdleFunc(Idle);
  
  glutCreateMenu(MenuSelect);
  glutAddMenuEntry("Interstellar",MODEL1);
  glutAddMenuEntry("Falcon",MODEL2);
  glutAddMenuEntry("Mongoose",MODEL3);
  glutAddMenuEntry("Galactica",MODEL4);

  // attach the menu to the right button
  glutAttachMenu(GLUT_RIGHT_BUTTON);

 
  //Enter main event handling loop
  glutMainLoop();

  //Enter main event handling loop
  glutMainLoop();
  return 0;


}  

