#version 450 core

in vec4 color;
in vec3 normal;
in vec3 texcoord;

out vec4 fcolor;

uniform sampler3D tex;


#define NUM_STEPS 100





uniform vec2 rotation;
uniform vec3 location;



// 
// bool Voraldo::intersect_ray_bbox(vec bbox_min, vec bbox_max, vec ray_org, vec ray_dir, double &tmin, double &tmax, double t0, double t1)
// {/*
//  * Ray-box intersection using IEEE numerical properties to ensure that the
//  * test is both robust and efficient, as described in:
//  *
//  *      Amy Williams, Steve Barrus, R. Keith Morley, and Peter Shirley
//  *      "An Efficient and Robust Ray-Box Intersection Algorithm"
//  *      Journal of graphics tools, 10(1):49-54, 2005
//  *
//  */
// //I pulled this code after three attempts at my own implementation didn't work
//   vec bbox[2];
// 	int sign[3];
//
// 	vec inv_direction = vec(1/ray_dir[0],1/ray_dir[1],1/ray_dir[2]);
//
// 	sign[0] = (inv_direction[0] < 0);
// 	sign[1] = (inv_direction[1] < 0);
// 	sign[2] = (inv_direction[2] < 0);
//
// 	bbox[0] = bbox_min;
// 	bbox[1] = bbox_max;
//
//
// 	//already declared (passed in by reference so that they can be used)
//   tmin = (bbox[sign[0]][0] - ray_org[0]) * inv_direction[0];
//   tmax = (bbox[1-sign[0]][0] - ray_org[0]) * inv_direction[0];
//
//   double tymin = (bbox[sign[1]][1] - ray_org[1]) * inv_direction[1];
//   double tymax = (bbox[1-sign[1]][1] - ray_org[1]) * inv_direction[1];
//
//   if ( (tmin > tymax) || (tymin > tmax) )
//     return false;
//   if (tymin > tmin)
//     tmin = tymin;
//   if (tymax < tmax)
//     tmax = tymax;
//
//   double tzmin = (bbox[sign[2]][2] - ray_org[2]) * inv_direction[2];
//   double tzmax = (bbox[1-sign[2]][2] - ray_org[2]) * inv_direction[2];
//
//   if ( (tmin > tzmax) || (tzmin > tmax) )
//     return false;
//   if (tzmin > tmin)
//     tmin = tzmin;
//   if (tzmax < tmax)
//     tmax = tzmax;
//   return ( (tmin < t1) && (tmax > t0) );
//
// }




bool hit(vec3 start, vec3 direction)
{
  //the bounding box is from 000 to 111
  // vec3 min = vec3(-1,-1,-1);
  vec3 min = vec3(0,0,0);
  vec3 max = vec3(1,1,1);



}



void main()
{
  // the ray origin will be determined by the location of the viewer,
  // specified in the value of location, and for each pixel a displacement
  // will be figured out using the texture coordinate

  // the ray direction will be determined by using the value of direction,
  // potentially displaced by up and right, to do something like perspective
  // projection - another thing to consider is you might scale the contribution
  // of left and right based on the squared distance of the pixel's xy value
  // from the center, i.e. modeling fisheye effects.








  // fcolor = vec4(1,0.3,0,1);
  fcolor = color;


  // fcolor.xyz *= 0.2/gl_FragCoord.z;


}
