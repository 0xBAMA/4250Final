#include "common.h"
#include "sliceobj.h"

#define TEX_PATH "resources/textures/models/save.png"

// /home/jb/Documents/4250/4250Final/resources/textures/models/save.png

//----------------------------------------------------------------------------

class Scene
{
public:
  void init();
  void draw();

  GLuint get_shader() {return shader;}

private:

  std::vector<glm::vec3>    points;
  std::vector<glm::vec3>   normals;
  std::vector<glm::vec4>    colors;
  std::vector<glm::vec3> texcoords;

  sliceobj s;

  GLuint vao;
  GLuint buffer;
  GLuint texture;
  GLuint shader;

  //attribs
  GLuint points_attrib;
  GLuint texcoords_attrib;
  GLuint normals_attrib;
  GLuint colors_attrib;


  void gpu_setup();

};

//----------------------------------------------------------------------------

void Scene::init()
{//general GL stuff

  points.clear();
  normals.clear();
  colors.clear();
  texcoords.clear();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);

  // giving an invalid enum warning, I guess it's just core spec now
  // glEnable(GL_TEXTURE_3D);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClearColor(0.8f, 0.5f, 0.068f, 1.0f);
  glPointSize(6.0f);

  //instantiate the objects, populate all arrays
  s.init(points, normals, colors, texcoords);

  //then take the populated arrays and send them to the GPU, set up textures, etc
  gpu_setup();
}

//----------------------------------------------------------------------------

void Scene::draw()
{
  //each object calls their own draw functions
  s.draw();
}

//----------------------------------------------------------------------------

void Scene::gpu_setup()
{


  //COMPILE AND USE SHADERS

  Shader s("resources/shaders/sliceshader_vertex.glsl", "resources/shaders/sliceshader_fragment.glsl");
  shader = s.Program;

  glUseProgram(shader);


  //TEXTURES
  glGenTextures(1, &texture); // Generate an ID
  glBindTexture(GL_TEXTURE_3D, texture); // use the specified ID



  unsigned width, height;
  std::vector<unsigned char> image_data;

  unsigned error = lodepng::decode( image_data, width, height, TEX_PATH, LodePNGColorType::LCT_RGBA, 8 );

  if( error == 0 )
  {
    cout << endl << "texture loaded" << endl;
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, 512, 256, 256, 0,  GL_RGBA, GL_UNSIGNED_BYTE, &image_data[0]);
    glGenerateMipmap(GL_TEXTURE_3D);

    //GL_MIRRORED_REPEAT is another interesting method, also the clamping ones
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);





    // This one looks the best - other options are GL_LINEAR, GL_NEAREST, then the mipmap ones
      //mag filter  can be either nearest or linear
      //min filter can be use the mipmap ones
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glActiveTexture(GL_TEXTURE0 + 0); // Texture unit 0
    glBindTexture(GL_TEXTURE_3D, texture);

    //I like referring to uniforms this way, rather than keeping a number in the class
    glUniform1i( glGetUniformLocation(shader, "tex"), 0);  //texture is in texture unit 0



  }
  else
  {
    std::cout << "Failed to load texture" << std::endl;
    if(error) std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
  }

  glGenVertexArrays( 1, &vao );
  glBindVertexArray( vao );

  glGenBuffers( 1, &buffer );
  glBindBuffer( GL_ARRAY_BUFFER, buffer );

  const GLuint num_bytes_points = sizeof(glm::vec3) * points.size();
  const GLuint num_bytes_texcoords = sizeof(glm::vec3) * texcoords.size();
  const GLuint num_bytes_normals = sizeof(glm::vec3) * normals.size();
  const GLuint num_bytes_colors = sizeof(glm::vec4) * colors.size();

  GLint num_bytes = num_bytes_points + num_bytes_texcoords + num_bytes_normals + num_bytes_colors;

  glBufferData(GL_ARRAY_BUFFER, num_bytes, NULL, GL_DYNAMIC_DRAW);

  glBufferSubData(GL_ARRAY_BUFFER, 0, num_bytes_points, &points[0]);
  glBufferSubData(GL_ARRAY_BUFFER, num_bytes_points, num_bytes_texcoords, &texcoords[0]);
  glBufferSubData(GL_ARRAY_BUFFER, num_bytes_points + num_bytes_texcoords, num_bytes_normals, &normals[0]);
  glBufferSubData(GL_ARRAY_BUFFER, num_bytes_points + num_bytes_texcoords + num_bytes_normals, num_bytes_colors, &colors[0]);



  //SET UP VERTEX ARRAYS

  cout << endl << endl << "if any of these attribs are giving errors, it's because they were optimized out of the shader (not everything is implemented yet)" << endl << endl;

  cout << endl << endl << "setting up points attrib" << endl << std::flush;
  points_attrib     = glGetAttribLocation(shader, "vPosition");
  glEnableVertexAttribArray(points_attrib);
  glVertexAttribPointer(points_attrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) (static_cast<const char*>(0) + (0)));

  cout << endl << endl << "setting up texcoords attrib" << endl << std::flush;
  texcoords_attrib  = glGetAttribLocation(shader, "vTexCoord");
  glEnableVertexAttribArray(texcoords_attrib);
  glVertexAttribPointer(texcoords_attrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) (static_cast<const char*>(0) + (num_bytes_points)));

  cout << endl << endl << "setting up normals attrib" << endl << std::flush;
  normals_attrib    = glGetAttribLocation(shader, "vNormal");
  glEnableVertexAttribArray(normals_attrib);
  glVertexAttribPointer(normals_attrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) (static_cast<const char*>(0) + (num_bytes_points + num_bytes_texcoords)));

  cout << endl << endl << "setting up colors attrib" << endl << std::flush;
  colors_attrib     = glGetAttribLocation(shader, "vColor");
  glEnableVertexAttribArray(colors_attrib);
  glVertexAttribPointer(colors_attrib, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*) (static_cast<const char*>(0) + (num_bytes_points + num_bytes_texcoords + num_bytes_normals)));



  //projection
  glm::mat4 proj = JonDefault::proj;

  glUniformMatrix4fv(glGetUniformLocation(shader, "proj"), 1, GL_FALSE, glm::value_ptr(proj));


  //view
  glm::mat4 view = JonDefault::view;

  glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));

}

//----------------------------------------------------------------------------
