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
  bool show_low_severity          = true;
  bool show_notification_severity = false;

  if(severity == GL_DEBUG_SEVERITY_HIGH && show_high_severity)
    fprintf( stderr, "        GL CALLBACK: %s type = 0x%x, severity = GL_DEBUG_SEVERITY_HIGH, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, message );

  if(severity == GL_DEBUG_SEVERITY_MEDIUM && show_medium_severity)
    fprintf( stderr, "        GL CALLBACK: %s type = 0x%x, severity = GL_DEBUG_SEVERITY_MEDIUM, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, message );

  if(severity == GL_DEBUG_SEVERITY_LOW && show_low_severity)
    fprintf( stderr, "        GL CALLBACK: %s type = 0x%x, severity = GL_DEBUG_SEVERITY_LOW, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, message );

  if(severity == GL_DEBUG_SEVERITY_NOTIFICATION && show_notification_severity)
    fprintf( stderr, "        GL CALLBACK: %s type = 0x%x, severity = GL_DEBUG_SEVERITY_NOTIFICATION, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, message );
}

//----------------------------------------------------------------------------
//the geometry
Scene scene;

//other globals (glow_balls)
float t = 0.0;
float tilt = 0.0;
float yoffset = 0.0;

glm::vec3 location = glm::vec3(0.5,0.5,-4);
glm::vec2 rotation = glm::vec2(0,0);


//----------------------------------------------------------------------------

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // display functions
  scene.draw();

  // glFlush();
  glutSwapBuffers();
  glutPostRedisplay();
}

//----------------------------------------------------------------------------


float scale = 1.0f;

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {

    case 033:
      exit(EXIT_SUCCESS);
      break;


    case '=':   //+
      scale *= 0.99;
      glUniform1fv(glGetUniformLocation(scene.get_shader(), "scale"), 1, &scale);
      cout << scale << endl;
      break;

    case '-':   //-
      scale /= 0.99;
      glUniform1fv(glGetUniformLocation(scene.get_shader(), "scale"), 1, &scale);
      cout << scale << endl;
      break;



    case 'f':
      glutFullScreenToggle(); //specific to freeglut
      break;


//movement
    // case 'w':
    //   location += glm::vec3(0,0,0.05);
    //   break;
    //
    // case 's':
    //   location -= glm::vec3(0,0,0.05);
    //   break;
    //
    // case 'a':
    //   location -= glm::vec3(0.05,0,0);
    //   break;
    //
    // case 'd':
    //   location += glm::vec3(0.05,0,0);
    //   break;

    case 'e':
      // location += glm::vec3(0,0.05,0);
      yoffset += 0.05;
      break;

    case 'q':
      // location -= glm::vec3(0,0.05,0);
      yoffset -= 0.05;
      break;


//rotation
    case 't':
      // rotation += glm::vec2(0,0.05);
      tilt += 0.05;
      break;

    case 'y':
      // rotation -= glm::vec2(0,0.05);
      tilt -= 0.05;
      break;

    // case 'g':
    //   rotation += glm::vec2(0.05,0);
    //   break;
    //
    // case 'h':
    //   rotation -= glm::vec2(0.05,0);
    //   break;











    case ',':
      glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      break;

    case '.':
      glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      break;








    case 'z':
      t+=0.01;
      break;

    case 'x':
      yoffset = 2.0f;
      tilt = -0.4f;
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

  t+=0.0001;
  glUniform1fv(glGetUniformLocation(scene.get_shader(), "t"), 1, &t);


  location = glm::vec3(0.5,0.5,0.5) + glm::vec3(5*cos(t), yoffset, 5*sin(t));
  rotation = glm::vec2(0,0) + glm::vec2(t+JonDefault::twopi/4,tilt);




  glUniform3fv(glGetUniformLocation(scene.get_shader(), "location"), 1, glm::value_ptr(location));
  glUniform2fv(glGetUniformLocation(scene.get_shader(), "rotation"), 1, glm::value_ptr(rotation));

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


  printf("\033[H\033[J"); //clear screen


  glutInit(&argc, argv);
  // glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  //doesn't look as good
  glutInitDisplayMode(GLUT_MULTISAMPLE | GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

  glutInitContextVersion( 4, 5 );
	glutInitContextProfile( GLUT_CORE_PROFILE );

  glutInitWindowSize(720,480);
  glutCreateWindow("Window");
  glutFullScreen();

  glewInit();

  //DEBUG
  glEnable              ( GL_DEBUG_OUTPUT );
  glDebugMessageCallback( MessageCallback, 0 );

  cout << endl << endl << " GL_DEBUG_OUTPUT ENABLED " << endl;


  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc( mouse );
  glutIdleFunc( idle );
  glutTimerFunc(1000.0/60.0, timer, 0);

  scene.init();

//ENTER MAIN LOOP
  glutMainLoop();

  return(EXIT_SUCCESS);

}
