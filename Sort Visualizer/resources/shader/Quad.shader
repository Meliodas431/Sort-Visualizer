#shader vertex
#version 460 core

layout(location = 0) in vec2 m_Position;
layout(location = 1) in vec2 m_TexCoords;
layout(location = 2) in float m_TexID;
layout(location = 3) in vec4 m_Color;

out VertexData {
	vec4 Color;
	vec2 TexCoords;
	float TexID;
} Output;

uniform mat4 m_MVP;

void main()
{
   gl_Position      = m_MVP * vec4(m_Position, 0.0, 1.0);
   Output.Color     = m_Color;
   Output.TexCoords = m_TexCoords;
   Output.TexID     = m_TexID;
};

#shader fragment
#version 460 core

in VertexData {
	vec4 Color;
	vec2 TexCoords;
	float TexID;
} Input;

uniform sampler2D u_text[2];

void main()
{
    int index = int(Input.TexID);
	float sampled;
	if (index == 0)
		sampled = texture(u_text[index], Input.TexCoords).a;
    if (index == 1)
		sampled = texture(u_text[1], Input.TexCoords).a;

	gl_FragColor = Input.Color * sampled;
};