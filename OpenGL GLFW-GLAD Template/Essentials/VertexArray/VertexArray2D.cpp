#include "VertexArray2D.h"

VertexArray2D::VertexArray2D()
{
	vertex = false;
	color = false;
	texture = false;
	normal = false;
}


void VertexArray2D::enableVertex(bool _Enabled)
{
	vertex = _Enabled;
}

void VertexArray2D::enableColor(bool _Enabled)
{
	color = _Enabled;
}

void VertexArray2D::enableTexture(bool _Enabled)
{
	texture = _Enabled;
}

void VertexArray2D::enableNormal(bool _Enabled)
{
	normal = _Enabled;
}

void VertexArray2D::addVertex(Vertex2D _Vertex)
{
	//Position
	vertices.push_back(_Vertex.position.x);
	vertices.push_back(_Vertex.position.y);
	
	//Color
	vertices.push_back(_Vertex.color.x); //R
	vertices.push_back(_Vertex.color.y); //G
	vertices.push_back(_Vertex.color.z); //B
	vertices.push_back(_Vertex.color.w); //A

	//Texture
	vertices.push_back(_Vertex.texture.x);
	vertices.push_back(_Vertex.texture.y);

	//Normal
	vertices.push_back(_Vertex.normal.x);
	vertices.push_back(_Vertex.normal.y);
	vertices.push_back(_Vertex.normal.z);
}

void VertexArray2D::draw(GLenum _Mode)
{
	if (vertex)
		glEnableClientState(GL_VERTEX_ARRAY);
	if (color)
		glEnableClientState(GL_COLOR_ARRAY);
	if (texture)
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	if (normal)
		glEnableClientState(GL_NORMAL_ARRAY);

	//This wont work(?)
	if (vertex)
		glVertexPointer(2, GL_FLOAT, 10 * sizeof(GLfloat), vertices.data());
	if (color)
		glColorPointer(4, GL_FLOAT, 10 * sizeof(GLfloat), vertices.data() + 2);
	if (texture)
		glTexCoordPointer(2, GL_FLOAT, 10 * sizeof(GLfloat), vertices.data() + 6);
	if (normal)
		glNormalPointer(GL_FLOAT, 10 * sizeof(GLfloat), vertices.data() + 8);


	if (!vertex)
		glDisableClientState(GL_VERTEX_ARRAY);
	if (!color)
		glDisableClientState(GL_COLOR_ARRAY);
	if (!texture)
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	if (!normal)
		glDisableClientState(GL_NORMAL_ARRAY);

	glDrawArrays(_Mode, 0, (int)vertices.size() / 10);
}
