#include "common.h"

//----------------------------------------------------------------------------

class sliceobj
{
public:

  void init(std::vector<glm::vec3> &points, std::vector<glm::vec3> &normals, std::vector<glm::vec4> &colors, std::vector<glm::vec3> &texcoords);

  void draw();

private:

  int start, num; //indexing geometry

};

//----------------------------------------------------------------------------

void sliceobj::init(std::vector<glm::vec3> &points, std::vector<glm::vec3> &normals, std::vector<glm::vec4> &colors, std::vector<glm::vec3> &texcoords)
{
  cout << endl << endl;
  cout << "initializing sliceobj starting at: " << endl;
  cout << "points:    "  << points.size()  << endl;
  cout << "normals:   "  << normals.size() << endl;
  cout << "colors:    "  << colors.size()  << endl;
  cout << "texcoords: "  << texcoords.size() << endl;
  cout << endl << endl;


  start = points.size();


  float increment = 0.005;



  for(float x =-0.5f; x <=0.5f; x+=increment)
  {
    points.push_back(glm::vec3(x,0.5,0.5));
    points.push_back(glm::vec3(x,0.5,-0.5));
    points.push_back(glm::vec3(x,-0.5,0.5));

    points.push_back(glm::vec3(x,-0.5,-0.5));
    points.push_back(glm::vec3(x,-0.5,0.5));
    points.push_back(glm::vec3(x,0.5,-0.5));


    texcoords.push_back(glm::vec3(x,0.5,0.5));
    texcoords.push_back(glm::vec3(x,0.5,-0.5));
    texcoords.push_back(glm::vec3(x,-0.5,0.5));

    texcoords.push_back(glm::vec3(x,-0.5,-0.5));
    texcoords.push_back(glm::vec3(x,-0.5,0.5));
    texcoords.push_back(glm::vec3(x,0.5,-0.5));


    colors.push_back(glm::vec4(x,x,x,1.0));
    colors.push_back(glm::vec4(x,x,x,1.0));
    colors.push_back(glm::vec4(x,x,x,1.0));

    colors.push_back(glm::vec4(x,x,x,1.0));
    colors.push_back(glm::vec4(x,x,x,1.0));
    colors.push_back(glm::vec4(x,x,x,1.0));

    normals.push_back(glm::vec3(1,0,0));
    normals.push_back(glm::vec3(1,0,0));
    normals.push_back(glm::vec3(1,0,0));

    normals.push_back(glm::vec3(1,0,0));
    normals.push_back(glm::vec3(1,0,0));
    normals.push_back(glm::vec3(1,0,0));

  }

  for(float x =0.5f; x >=-0.5f; x-=increment)
  {
    points.push_back(glm::vec3(x,0.5,0.5));
    points.push_back(glm::vec3(x,-0.5,0.5));
    points.push_back(glm::vec3(x,0.5,-0.5));

    points.push_back(glm::vec3(x,-0.5,-0.5));
    points.push_back(glm::vec3(x,0.5,-0.5));
    points.push_back(glm::vec3(x,-0.5,0.5));


    texcoords.push_back(glm::vec3(x,0.5,0.5));
    texcoords.push_back(glm::vec3(x,-0.5,0.5));
    texcoords.push_back(glm::vec3(x,0.5,-0.5));

    texcoords.push_back(glm::vec3(x,-0.5,-0.5));
    texcoords.push_back(glm::vec3(x,0.5,-0.5));
    texcoords.push_back(glm::vec3(x,-0.5,0.5));


    colors.push_back(glm::vec4(x,x,x,1.0));
    colors.push_back(glm::vec4(x,x,x,1.0));
    colors.push_back(glm::vec4(x,x,x,1.0));

    colors.push_back(glm::vec4(x,x,x,1.0));
    colors.push_back(glm::vec4(x,x,x,1.0));
    colors.push_back(glm::vec4(x,x,x,1.0));

    normals.push_back(glm::vec3(-1,0,0));
    normals.push_back(glm::vec3(-1,0,0));
    normals.push_back(glm::vec3(-1,0,0));

    normals.push_back(glm::vec3(-1,0,0));
    normals.push_back(glm::vec3(-1,0,0));
    normals.push_back(glm::vec3(-1,0,0));

  }




  num = points.size() - start;


  cout << endl << endl;
  cout << "initializing sliceobj finished at: " << endl;
  cout << "points:    "  << points.size()  << endl;
  cout << "normals:   "  << normals.size() << endl;
  cout << "colors:    "  << colors.size()  << endl;
  cout << "texcoords: "  << texcoords.size() << endl;
  cout << endl << endl;

}

//----------------------------------------------------------------------------

void sliceobj::draw()
{
  glDrawArrays(GL_TRIANGLES, start, num);
}

//----------------------------------------------------------------------------
