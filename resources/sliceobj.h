#include "common.h"

class sliceobj
{
public:
  void init(std::vector<glm::vec3> points, std::vector<glm::vec3> normals, std::vector<glm::vec4> colors, std::vector<glm::vec3> texcoords);

  void draw();

private:

  // sliceobj s;

};


void sliceobj::init(std::vector<glm::vec3> points, std::vector<glm::vec3> normals, std::vector<glm::vec4> colors, std::vector<glm::vec3> texcoords)
{ cout << endl << endl;
  cout << "initializing sliceobj starting at: " << endl;
  cout << "points: "  << points.size()  << endl;
  cout << "normals: " << normals.size() << endl;
  cout << "colors: "  << colors.size()  << endl;
  cout << endl << endl;

  //then add the points with .push_back()


}

void sliceobj::draw()
{

}
