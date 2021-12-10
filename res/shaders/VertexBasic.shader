#version 410 core

layout(location = 0) in vec3 position;

// uniform vec4 perspective;
// uniform mat4 view;
// uniform mat3 rotmat;

out vec4 v_Color;

// mat4 getPerspective()
// {
// 	float tanHalfFov = tan(perspective.x / 2.0f);
// 	float t1 = 1.0 / (perspective.y * tanHalfFov);
// 	float t2 = 1.0 / tanHalfFov;
// 	float t3 = -(perspective.w + perspective.z) / (perspective.w - perspective.z);
// 	float t4 = -(2.0f * perspective.w * perspective.z) / (perspective.w - perspective.z);
// 	return mat4(
// 		t1,				0.0,			0.0,			0.0,
// 		0.0,			t2,				0.0,			0.0,
// 		0.0,			0.0,			t3,				-1.0,
// 		0.0,			0.0,			t4,				0.0
// 	);
// }

void main()
{
	// vec3 pos = position * rotmat;
	// mat4 proj = getPerspective();
	gl_Position = vec4(position, 1.0f);
	float val = (gl_VertexID % 12) / 3 * 0.25f;
	v_Color = vec4(val, val, val, 1.0f);
}
