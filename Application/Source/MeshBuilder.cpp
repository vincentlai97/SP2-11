#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include <MyMath.h>

Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	v.pos.Set(-1000, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(1000, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, -1000, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 1000, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, -1000);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, 1000);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 6;
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float lengthX, float lengthY)
{
	Vertex v;

	std::vector<Vertex> vertex_buffer_data;
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.pos.Set((float)lengthX / 2, (float)lengthY / 2, 0);
	v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-(float)lengthX / 2, (float)lengthY / 2, 0);
	v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set((float)lengthX / 2, -(float)lengthY / 2, 0);
	v.texCoord.Set(1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-(float)lengthX / 2, -(float)lengthY / 2, 0);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;
	for (int count = 0; count < 4; count++)
		index_buffer_data.push_back(count);

	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 4;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color, float size)
{
	Vertex v;

	std::vector<Vertex> vertex_buffer_data;
	v.color = color;
	v.pos.Set(size/2, size/2, size/2);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-size/2, size/2, size/2);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-size/2, -size/2, size/2);
	vertex_buffer_data.push_back(v);
	v.pos.Set(size/2, -size/2, size/2);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-size/2, size/2, -size/2);
	vertex_buffer_data.push_back(v);
	v.pos.Set(size/2, size/2, -size/2);
	vertex_buffer_data.push_back(v);
	v.pos.Set(size/2, -size/2, -size/2);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-size/2, -size/2, -size/2);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(2);

	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 36;
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateCircle(const std::string &meshName, Color color, float radius, unsigned numSlice)
{
	Vertex v;
	double x, y;

	float degreePerSlice = 360.f/numSlice;

	std::vector<Vertex> vertex_buffer_data;
	v.color = color;
	for (int count = 0; count <= numSlice; count++)
	{
		x = sin(Math::DegreeToRadian(degreePerSlice * count));
		y = cos(Math::DegreeToRadian(degreePerSlice * count));
		v.pos.Set(radius*(float)x, radius*(float)y, 0);
		v.normal = ((float)x, (float)y, 0);
		vertex_buffer_data.push_back(v);
	}

	std::vector<GLuint> index_buffer_data;
	for (int count = 0; count <= vertex_buffer_data.size(); count++)
		index_buffer_data.push_back(count);

	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 37;
	mesh->mode = Mesh::DRAW_LINE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateRing(const std::string &meshName, Color color, float inner, float outer)
{
	Vertex v;
	double x, y;

	std::vector<Vertex> vertex_buffer_data;
	v.color = color;
	v.normal = (0, 0, 1);
	for (int count = 0; count < 37; count++)
	{
		x = sin((float)count / 18 * Math::PI) * outer;
		y = cos((float)count / 18 * Math::PI) * outer;
		v.pos.Set((float)x, (float)y, 0);
		vertex_buffer_data.push_back(v);
		x = sin((float)count / 18 * Math::PI) * inner;
		y = cos((float)count / 18 * Math::PI) * inner;
		v.pos.Set((float)x, (float)y, 0);
		vertex_buffer_data.push_back(v);
	}

	std::vector<GLuint> index_buffer_data;
	for (int count = 0; count < 74; count++)
		index_buffer_data.push_back(count);

	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 74;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

float sphereX(float phi, float theta) { return cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta));}
float sphereY(float phi, float theta) { return sin(Math::DegreeToRadian(phi));}
float sphereZ(float phi, float theta) { return cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));}

Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, float radius, unsigned numStack, unsigned numSlice)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.color = color;
	float degreePerStack = 180.f / numStack;
	float degreePerSlice = 360.f / numSlice;
	for (unsigned stackCount = 0; stackCount <= numStack; stackCount++)
		for (unsigned sliceCount = 0; sliceCount <= numSlice; sliceCount++)
		{
			float phi = -90 + stackCount * degreePerStack;
			float theta = sliceCount * degreePerSlice;
			v.pos.Set(radius*sphereX(phi, theta), radius*sphereY(phi, theta), radius*sphereZ(phi, theta));
			v.normal.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
			vertex_buffer_data.push_back(v);
		}

	std::vector<GLuint> index_buffer_data;
	for (unsigned stackCount = 0; stackCount < numStack; stackCount++)
		for (unsigned sliceCount = 0; sliceCount <= numSlice; sliceCount++)
		{
			index_buffer_data.push_back(stackCount * (numSlice+1) + sliceCount);
			index_buffer_data.push_back((stackCount+1) * (numSlice+1) + sliceCount);
		}

	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string &file_path)
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
	if(!success) return NULL;

	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);

	//Create the mesh and call glBindBuffer, glBufferDataMesh *mesh = new Mesh(meshName);
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	//Use triangle list and remember to set index size
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol)
{
	Vertex ver;

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float height = 1.f / numRow;
	float width = 1.f / numCol;
	int offset = 0;
	for (unsigned countr = 0; countr < numRow; countr++)
	{
		for (unsigned countc = 0; countc < numCol; countc++)
		{
			float u = countc * width;
			float v = 1.f - height - countr * height;
			ver.pos.Set(-0.5, -0.5, 0);
			ver.texCoord.Set(u, v);
			vertex_buffer_data.push_back(ver);
			ver.pos.Set(0.5, -0.5, 0);
			ver.texCoord.Set(u + width, v);
			vertex_buffer_data.push_back(ver);
			ver.pos.Set(0.5, 0.5, 0);
			ver.texCoord.Set(u + width, v + height);
			vertex_buffer_data.push_back(ver);
			ver.pos.Set(-0.5, 0.5, 0);
			ver.texCoord.Set(u, v + height);
			vertex_buffer_data.push_back(ver);

			index_buffer_data.push_back(0 + offset);
			index_buffer_data.push_back(1 + offset);
			index_buffer_data.push_back(2 + offset);
			index_buffer_data.push_back(0 + offset);
			index_buffer_data.push_back(2 + offset);
			index_buffer_data.push_back(3 + offset);
			offset += 4;
		}
	}

	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}
