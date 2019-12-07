#version 450 core

//we define our relevant states as colors

#define conductor	ivec4(32, 32, 32, 255)
#define electron_tail ivec4(0, 32, 45, 255)
#define electron_head ivec4(45, 32, 0, 255)

//and this for testing (high contrast)
#define test_red ivec4(255, 32, 0, 255)


uniform layout(rgba8) image3D current;
uniform layout(rgba8) image3D next;

bool compare(ivec4 a, ivec4 b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z && a.a == b.a);
}

void main()
{

	vec3 offsets[8];

	int my_index = gl_VertexID;

	// integer division/mod to get index
	ivec3 sample_location = ivec3(my_index%512, (my_index/512)%512, my_index/(256*512));


// == conductor

	ivec4 data[19];

	//the location of voxel being considered
	data[0] = ivec4(imageLoad(current,sample_location)*vec4(256));

	





	//we consider everything but the corners
	if(compare(data[0], conductor))
	{
		//do I have electron neighbors?
		imageStore(next,sample_location, test_red);

	}


	if(compare(data[0], electron_tail))
	{
		imageStore(next,sample_location, conductor);
	}


	if(compare(data[0], electron_head))
	{
		imageStore(next,sample_location, electron_tail);
	}








	//LEAVE UNINVOLVED CELLS UNTOUCHED, DON'T REWRITE REDUNDANT DATA

	//we handle data now as ivec4s, to make checking easier/more reliable

}
