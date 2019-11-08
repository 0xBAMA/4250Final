#include "common.h"

class sliceobj
{

  // std::vector<glm::vec3>   points;
  // std::vector<glm::vec3>  normals;
  // std::vector<glm::vec4>   colors;


public:
  void init(std::vector<glm::vec3> points, std::vector<glm::vec3> normals, std::vector<glm::vec4> colors);
  void draw();

private:

  // sliceobj s;

};


void sliceobj::init(std::vector<glm::vec3> points, std::vector<glm::vec3> normals, std::vector<glm::vec4> colors)
{ cout << endl << endl;
  cout << "initializing sliceobj starting at: " << endl;
  cout << "points: "  << points.size()  << endl;
  cout << "normals: " << normals.size() << endl;
  cout << "colors: "  << colors.size()  << endl;
  cout << endl << endl;
}

void sliceobj::draw()
{
  
}
