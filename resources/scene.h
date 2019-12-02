#include "common.h"
#include "sliceobj.h"




// #define TEX_PATH "resources/textures/models/ambient occlusion visualized.png"
// #define TEX_PATH "resources/textures/models/save.png"              //CASTLE
// #define TEX_PATH "resources/textures/models/heads with black.png"  //MRI data with a contrasting background (only useful in slice view)
// #define TEX_PATH "resources/textures/models/heads.png"             //MRI data with no contrasting background added
// #define TEX_PATH "resources/textures/models/save-copy2.png"        //perlin noise with tube cutout
// #define TEX_PATH "resources/textures/models/save-copy3.png"        //trees with purple centers
// #define TEX_PATH "resources/textures/models/save-copy4.png"        //trees with purple centers, different spacing
// #define TEX_PATH "resources/textures/models/save-copy5.png"        //trees with clouds
// #define TEX_PATH "resources/textures/models/save-copy9.png"        //black, white and gold noise
// #define TEX_PATH "resources/textures/models/save-copy10.png"       // black, gold, white and orange, eroded
// #define TEX_PATH "resources/textures/models/save-copy13.png"       //castle
// #define TEX_PATH "resources/textures/models/save-copy15.png"       //too many trunks
// #define TEX_PATH "resources/textures/models/save-copy16.png"       //fewer but still too many trunks
// #define TEX_PATH "resources/textures/models/save-copy17.png"       //forest looking better
// #define TEX_PATH "resources/textures/models/save-copy18.png"       //forest with flowers
// #define TEX_PATH "resources/textures/models/save-copy19.png"       //red and blue castle ao visualization
// #define TEX_PATH "resources/textures/models/save-copy21.png"       //first instance of my stupid ao bug
// #define TEX_PATH "resources/textures/models/save-copy22.png"       //second instance of the ao bug
// #define TEX_PATH "resources/textures/models/save-copy24.png"       //underwater grid
// #define TEX_PATH "resources/textures/models/save-copy25.png"       //water grid with rose
// #define TEX_PATH "resources/textures/models/save-copy26.png"       //bars and rose
// #define TEX_PATH "resources/textures/models/save-copy27.png"       //icosahedron wierdness
// #define TEX_PATH "resources/textures/models/save1.png"             //star trek equipment
// #define TEX_PATH "resources/textures/models/save-copy23-L.png"   //very dark


//the following were made on 11/25/2019 with V07
// #define TEX_PATH "resources/textures/models/new.png"               //ico
// #define TEX_PATH "resources/textures/models/new2.png"             //ico
// #define TEX_PATH "resources/textures/models/new3.png"             //ico
// #define TEX_PATH "resources/textures/models/new4.png"             //ico
// #define TEX_PATH "resources/textures/models/new5.png"             //ico
// #define TEX_PATH "resources/textures/models/new6.png"             //ico
// #define TEX_PATH "resources/textures/models/new7.png"             //ico
// #define TEX_PATH "resources/textures/models/new8.png"             //ico
// #define TEX_PATH "resources/textures/models/new9.png"             //ico
// #define TEX_PATH "resources/textures/models/new10.png"             //ico
// #define TEX_PATH "resources/textures/models/new11.png"             //ico
// #define TEX_PATH "resources/textures/models/new12.png"             //ico
// #define TEX_PATH "resources/textures/models/chain.png"             //chain
// #define TEX_PATH "resources/textures/models/new13.png"             //ico
// #define TEX_PATH "resources/textures/models/new14.png"             //ico

//GRAPHS - 12/1
// #define TEX_PATH "resources/textures/models/graph0.png"             //graphs
// #define TEX_PATH "resources/textures/models/graph1.png"             //graphs
// #define TEX_PATH "resources/textures/models/graph2.png"             //graphs
// #define TEX_PATH "resources/textures/models/graph3.png"             //graphs
// #define TEX_PATH "resources/textures/models/graph4.png"             //graphs
// #define TEX_PATH "resources/textures/models/graph5.png"             //graphs
// #define TEX_PATH "resources/textures/models/graph6.png"             //graphs
// #define TEX_PATH "resources/textures/models/graph7.png"             //graphs
// #define TEX_PATH "resources/textures/models/graph8.png"             //graphs
// #define TEX_PATH "resources/textures/models/graph9.png"             //graphs
#define TEX_PATH "resources/textures/models/graph10.png"             //graphs






// #define TEX_PATH "resources/textures/models/save-copy20.png"   //can't see through the noise
// #define TEX_PATH "resources/textures/models/save-copy6.png"    //orange and white noise
// #define TEX_PATH "resources/textures/models/save-copy7.png"    //orange and white noise
// #define TEX_PATH "resources/textures/models/save-copy8.png"    //yellow shell in noise
// #define TEX_PATH "resources/textures/models/save-copy11.png"   //octaves but weird
// #define TEX_PATH "resources/textures/models/save-copy12.png"   //same as previous
// #define TEX_PATH "resources/textures/models/bigass.png"        //texture made in gimp with gradients
// #define TEX_PATH "resources/textures/models/palette test.png"
// #define TEX_PATH "resources/textures/models/save-copy14.png"   //pink aura
// #define TEX_PATH "resources/textures/models/save-copy23.png"   //very dark
// #define TEX_PATH "resources/textures/models/save-copy28.png"   //happy birthday text





















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

  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);

  // giving an invalid enum warning, I guess it's just core spec now
  // glEnable(GL_TEXTURE_3D);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // glClearColor(0.8f, 0.5f, 0.068f, 1.0f);
  glClearColor(0.396f,0.396f,0.4f,1.0f);
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
    cout << "  the size of the 3d texture image is " << image_data.size() << " bytes";
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, 512, 256, 256, 0,  GL_RGBA, GL_UNSIGNED_BYTE, &image_data[0]);
    glGenerateMipmap(GL_TEXTURE_3D);

    //GL_MIRRORED_REPEAT is another interesting method, also the clamping ones, GL_REPEAT
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);


    // This one looks the best - other options are GL_LINEAR, GL_NEAREST, then the mipmap ones
      //mag filter  can be either nearest or linear
      //min filter can be use the mipmap ones

    // glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

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

  const GLuint num_bytes_points    = sizeof(glm::vec3) * points.size();
  const GLuint num_bytes_texcoords = sizeof(glm::vec3) * texcoords.size();
  const GLuint num_bytes_normals   = sizeof(glm::vec3) * normals.size();
  const GLuint num_bytes_colors    = sizeof(glm::vec4) * colors.size();

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

  float scale = 1.0f;

  glUniform1fv(glGetUniformLocation(shader, "scale"), 1, &scale);

}

//----------------------------------------------------------------------------
