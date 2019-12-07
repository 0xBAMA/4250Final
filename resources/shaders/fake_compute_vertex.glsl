#version 450 core

uniform layout(rgba8) image3D current;
uniform layout(rgba8) image3D next;

void main()
{

	vec3 offsets[8];

	int my_index = gl_VertexID;

	// integer division/mod to get index
	ivec3 sample_location = ivec3(my_index%512, (my_index/512)%256, my_index/(256*512));


// == conductor

	ivec4 current_data = ivec4(imageLoad(current, sample_location)*vec4(256));



	//we consider everything but the corners
	if(current_data.r <10 && current_data.g <10 && current_data.b <10 && current_data.a > 200)
	{
		//do I have electron neighbors? TBD
		imageStore(next, sample_location, ivec4(255,0,0,255));	//goes to a red test color

	}
	else if(current_data.b >200 && current_data.g >200 && current_data.a > 200) //	cyan is electron tail
	{
		imageStore(next,sample_location, ivec4(0,0,0,255));	//goes back to conductor
	}
	else if(current_data.r >200 && current_data.g >200 && current_data.a > 200)		//yellow is electron head
	{
		imageStore(next,sample_location, ivec4(0,255,255,255));	//goes to electron tail cyan
	}








	//LEAVE UNINVOLVED CELLS UNTOUCHED, DON'T REWRITE REDUNDANT DATA

	//we handle data now as ivec4s, to make checking easier/more reliable

}
