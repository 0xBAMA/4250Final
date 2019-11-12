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


  float increment = 0.001;









//THIS NEEDS TO BE BROKEN UP INTO A SWITCH STATEMENT, TO DO THAT ROUND ROBIN SCHEME

  int count = 0;

  for(float xplus =-0.5f, xminus = 0.5f, zplus = -0.5f, zminus = 0.5f;
    xplus <=0.5f,xminus >= -0.5f, zplus <= 0.5f, zminus >= -0.5f;
    xplus+=increment,xminus-=increment,zplus+=increment,zminus-=increment)
  {

    switch(count%4)
    {
      case 0:
        points.push_back(glm::vec3(xplus,0.5,0.5));
        points.push_back(glm::vec3(xplus,-0.5,0.5));
        points.push_back(glm::vec3(xplus,0.5,-0.5));

        points.push_back(glm::vec3(xplus,-0.5,-0.5));
        points.push_back(glm::vec3(xplus,0.5,-0.5));
        points.push_back(glm::vec3(xplus,-0.5,0.5));


        texcoords.push_back(glm::vec3(xplus,0.5,0.5));
        texcoords.push_back(glm::vec3(xplus,-0.5,0.5));
        texcoords.push_back(glm::vec3(xplus,0.5,-0.5));

        texcoords.push_back(glm::vec3(xplus,-0.5,-0.5));
        texcoords.push_back(glm::vec3(xplus,0.5,-0.5));
        texcoords.push_back(glm::vec3(xplus,-0.5,0.5));


        colors.push_back(glm::vec4(xplus,xplus,xplus,1.0));
        colors.push_back(glm::vec4(xplus,xplus,xplus,1.0));
        colors.push_back(glm::vec4(xplus,xplus,xplus,1.0));

        colors.push_back(glm::vec4(xplus,xplus,xplus,1.0));
        colors.push_back(glm::vec4(xplus,xplus,xplus,1.0));
        colors.push_back(glm::vec4(xplus,xplus,xplus,1.0));

        normals.push_back(glm::vec3(1,0,0));
        normals.push_back(glm::vec3(1,0,0));
        normals.push_back(glm::vec3(1,0,0));

        normals.push_back(glm::vec3(1,0,0));
        normals.push_back(glm::vec3(1,0,0));
        normals.push_back(glm::vec3(1,0,0));
        break;

    //----------------
      case 1:
        points.push_back(glm::vec3(xminus,0.5,0.5));
        points.push_back(glm::vec3(xminus,0.5,-0.5));
        points.push_back(glm::vec3(xminus,-0.5,0.5));

        points.push_back(glm::vec3(xminus,-0.5,-0.5));
        points.push_back(glm::vec3(xminus,-0.5,0.5));
        points.push_back(glm::vec3(xminus,0.5,-0.5));


        texcoords.push_back(glm::vec3(xminus,0.5,0.5));
        texcoords.push_back(glm::vec3(xminus,0.5,-0.5));
        texcoords.push_back(glm::vec3(xminus,-0.5,0.5));

        texcoords.push_back(glm::vec3(xminus,-0.5,-0.5));
        texcoords.push_back(glm::vec3(xminus,-0.5,0.5));
        texcoords.push_back(glm::vec3(xminus,0.5,-0.5));


        colors.push_back(glm::vec4(xminus,xminus,xminus,1.0));
        colors.push_back(glm::vec4(xminus,xminus,xminus,1.0));
        colors.push_back(glm::vec4(xminus,xminus,xminus,1.0));

        colors.push_back(glm::vec4(xminus,xminus,xminus,1.0));
        colors.push_back(glm::vec4(xminus,xminus,xminus,1.0));
        colors.push_back(glm::vec4(xminus,xminus,xminus,1.0));

        normals.push_back(glm::vec3(-1,0,0));
        normals.push_back(glm::vec3(-1,0,0));
        normals.push_back(glm::vec3(-1,0,0));

        normals.push_back(glm::vec3(-1,0,0));
        normals.push_back(glm::vec3(-1,0,0));
        normals.push_back(glm::vec3(-1,0,0));
        break;

    //----------------

      case 2:
        points.push_back(glm::vec3(0.5,0.5,zplus));
        points.push_back(glm::vec3(-0.5,0.5,zplus));
        points.push_back(glm::vec3(0.5,-0.5,zplus));

        points.push_back(glm::vec3(-0.5,-0.5,zplus));
        points.push_back(glm::vec3(0.5,-0.5,zplus));
        points.push_back(glm::vec3(-0.5,0.5,zplus));


        texcoords.push_back(glm::vec3(0.5,0.5,zplus));
        texcoords.push_back(glm::vec3(-0.5,0.5,zplus));
        texcoords.push_back(glm::vec3(0.5,-0.5,zplus));

        texcoords.push_back(glm::vec3(-0.5,-0.5,zplus));
        texcoords.push_back(glm::vec3(0.5,-0.5,zplus));
        texcoords.push_back(glm::vec3(-0.5,0.5,zplus));


        colors.push_back(glm::vec4(zplus,zplus,zplus,1.0));
        colors.push_back(glm::vec4(zplus,zplus,zplus,1.0));
        colors.push_back(glm::vec4(zplus,zplus,zplus,1.0));

        colors.push_back(glm::vec4(zplus,zplus,zplus,1.0));
        colors.push_back(glm::vec4(zplus,zplus,zplus,1.0));
        colors.push_back(glm::vec4(zplus,zplus,zplus,1.0));

        normals.push_back(glm::vec3(0,0,1));
        normals.push_back(glm::vec3(0,0,1));
        normals.push_back(glm::vec3(0,0,1));

        normals.push_back(glm::vec3(0,0,1));
        normals.push_back(glm::vec3(0,0,1));
        normals.push_back(glm::vec3(0,0,1));
        break;

    //----------------

      case 3:
        points.push_back(glm::vec3(0.5,0.5,zminus));
        points.push_back(glm::vec3(0.5,-0.5,zminus));
        points.push_back(glm::vec3(-0.5,0.5,zminus));

        points.push_back(glm::vec3(-0.5,-0.5,zminus));
        points.push_back(glm::vec3(-0.5,0.5,zminus));
        points.push_back(glm::vec3(0.5,-0.5,zminus));


        texcoords.push_back(glm::vec3(0.5,0.5,zminus));
        texcoords.push_back(glm::vec3(0.5,-0.5,zminus));
        texcoords.push_back(glm::vec3(-0.5,0.5,zminus));

        texcoords.push_back(glm::vec3(-0.5,-0.5,zminus));
        texcoords.push_back(glm::vec3(-0.5,0.5,zminus));
        texcoords.push_back(glm::vec3(0.5,-0.5,zminus));


        colors.push_back(glm::vec4(zminus,zminus,zminus,1.0));
        colors.push_back(glm::vec4(zminus,zminus,zminus,1.0));
        colors.push_back(glm::vec4(zminus,zminus,zminus,1.0));

        colors.push_back(glm::vec4(zminus,zminus,zminus,1.0));
        colors.push_back(glm::vec4(zminus,zminus,zminus,1.0));
        colors.push_back(glm::vec4(zminus,zminus,zminus,1.0));

        normals.push_back(glm::vec3(0,0,-1));
        normals.push_back(glm::vec3(0,0,-1));
        normals.push_back(glm::vec3(0,0,-1));

        normals.push_back(glm::vec3(0,0,-1));
        normals.push_back(glm::vec3(0,0,-1));
        normals.push_back(glm::vec3(0,0,-1));
        break;
      }
    count++;
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
