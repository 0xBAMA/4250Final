#include "resources/scene.h"


//DEBUG STUFF

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{



  bool show_high_severity         = true;
  bool show_medium_severity       = true;
  bool show_low_severity          = false;
  bool show_notification_severity = false;




  if(severity == GL_DEBUG_SEVERITY_HIGH && show_high_severity)
    fprintf( stderr, "        GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );

  if(severity == GL_DEBUG_SEVERITY_MEDIUM && show_medium_severity)
    fprintf( stderr, "        GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );

  if(severity == GL_DEBUG_SEVERITY_LOW && show_low_severity)
    fprintf( stderr, "        GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );

  if(severity == GL_DEBUG_SEVERITY_NOTIFICATION && show_notification_severity)
    fprintf( stderr, "        GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

//----------------------------------------------------------------------------
//the geometry
Scene s;

//other globals (glow_balls)


//----------------------------------------------------------------------------

// void init()
// {
//
//
//
// }

//----------------------------------------------------------------------------

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // display functions
  s.draw();

  // glFlush();
  glutSwapBuffers();
  glutPostRedisplay();
}

//----------------------------------------------------------------------------

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {

    case 033:
      exit(EXIT_SUCCESS);
      break;

    case 'f':
      // glutFullScreen();
      glutFullScreenToggle(); //specific to freeglut
      break;
  }

  glutPostRedisplay();
}

//----------------------------------------------------------------------------

void mouse( int button, int state, int x, int y )
{
  if ( state == GLUT_DOWN )
	{
		switch( button )
		{
		    case GLUT_LEFT_BUTTON:    cout << "left" << endl;   break;
		    case GLUT_MIDDLE_BUTTON:  cout << "middle" << endl; break;
		    case GLUT_RIGHT_BUTTON:   cout << "right" << endl;  break;
		}

    if(button == GLUT_LEFT_BUTTON)
    {

      //clear the screen
      // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //draw with selection colors


      //selection handling code - using input x and y
      y = glutGet( GLUT_WINDOW_HEIGHT ) - y;

      unsigned char pixel[4];
      glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

      cout << "color at click is r:" << (int)pixel[0] << " g:" << (int)pixel[1] << " b:" << (int)pixel[2] << endl;


      //clear the screen
      // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glutPostRedisplay();

    }
  }
}

//----------------------------------------------------------------------------

void timer(int)
{

	glutPostRedisplay();
	glutTimerFunc(1000.0/60.0, timer, 0);
}

//----------------------------------------------------------------------------



void idle( void )
{
	// glutPostRedisplay();
}


//----------------------------------------------------------------------------




int main(int argc, char **argv)
{





  glutInit(&argc, argv);
  // glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  //doesn't look as good
  glutInitDisplayMode(GLUT_MULTISAMPLE | GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

  glutInitContextVersion( 4, 5 );
	glutInitContextProfile( GLUT_CORE_PROFILE );

  glutInitWindowSize(720,480);
  glutCreateWindow("<<<WELCOME>>>");

  glewInit();


  //DEBUG
  glEnable              ( GL_DEBUG_OUTPUT );
  glDebugMessageCallback( MessageCallback, 0 );

  cout << endl << endl << " GL_DEBUG_OUTPUT ENABLED " << endl;


  s.init();


  // init();

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc( mouse );
  glutIdleFunc( idle );
  glutTimerFunc(1000.0/60.0, timer, 0);





//ENTER MAIN LOOP
  glutMainLoop();
  return(EXIT_SUCCESS);
}
