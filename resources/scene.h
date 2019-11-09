#include "common.h"
#include "sliceobj.h"

class Scene
{
public:
  void init();
  void draw();

private:

  std::vector<glm::vec3>    points;
  std::vector<glm::vec3>   normals;
  std::vector<glm::vec4>    colors;
  std::vector<glm::vec3> texcoords;

  sliceobj s;

};

void Scene::init()
{//general GL stuff

  points.clear();
  normals.clear();
  colors.clear();
  texcoords.clear();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);
  // glEnable(GL_TEXTURE_3D); //giving an invalid enum warning, I guess it's just core spec now


  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


  glClearColor(0.8f, 0.6f, 0.068f, 1.0f);

  //instantiate the objects
  s.init(points, normals, colors, texcoords);



  //then take the arrays and send them to the GPU

}

void Scene::draw()
{
  //each object calls their own draw functions
  s.draw();
}
