/*
 *
 */

#include "md2.h"

// desc: given 3 points, calculates the normal to the points
void CalculateNormal(float *p1, float *p2, float *p3)
{
	float a[3], b[3], result[3];
	float length;

	a[0] = p1[0] - p2[0];
	a[1] = p1[1] - p2[1];
	a[2] = p1[2] - p2[2];

	b[0] = p1[0] - p3[0];
	b[1] = p1[1] - p3[1];
	b[2] = p1[2] - p3[2];

	result[0] = a[1] * b[2] - b[1] * a[2];
	result[1] = b[0] * a[2] - a[0] * b[2];
	result[2] = a[0] * b[1] - b[0] * a[1];

	// calculate the length of the normal
	length = (float) sqrt(result[0] * result[0] + result[1] * result[1] + result[2] * result[2]);

	// normalize and specify the normal
	glNormal3f(result[0] / length, result[1] / length, result[2] / length);
}
vector_t operator+(vector_t a, vector_t b)
{
	vector_t c;

	c.point[0] = a.point[0] + b.point[0];
	c.point[1] = a.point[1] + b.point[1];
	c.point[2] = a.point[2] + b.point[2];

	return c;
}
vector_t operator-(vector_t a, vector_t b)
{
	vector_t c;

	c.point[0] = a.point[0] - b.point[0];
	c.point[1] = a.point[1] - b.point[1];
	c.point[2] = a.point[2] - b.point[2];

	return c;
}
vector_t operator*(float f, vector_t b)
{
	vector_t c;

	c.point[0] = f * b.point[0];
	c.point[1] = f * b.point[1];
	c.point[2] = f * b.point[2];

	return c;
}
vector_t operator/(vector_t a, vector_t b)
{
	vector_t c;

	c.point[0] = a.point[0] / b.point[0];
	c.point[1] = a.point[1] / b.point[1];
	c.point[2] = a.point[2] / b.point[2];

	return c;
}

ModelMD2::ModelMD2()
{
	numVertices = 0;        // vertices
	numTriangles = 0;        // triangles
	numFrames = 0;        // frames
	numST = 0;        // texture coordinates
	frameSize = 0;        // needed?
	currentFrame = 0;        // current keyframe
	nextFrame = 1;        // next keyframe
	interpol = 0.0;        // interpolation percent
	triIndex = nullptr;        // triangle indices
	st = nullptr;        // texture coordinate indices
	vertexList = nullptr;        // vertices
	modelTex = nullptr;        // skin/texture
	modelState = MODEL_IDLE;
//	Load(modelFile, skinFile);
}
ModelMD2::~ModelMD2()
{
	Unload();
}
int ModelMD2::Load(char *modelFile, char *skinFile)
{
	FILE *f;
	int fileLen;
	char *buffer;

	modelHeader_t *modelHeader;        // model header

	stIndex_t *stPtr;        // texture data
	frame_t *frame;        // frame data
	vector_t *vertexListPtr;        // index variable
	mesh_t *bufIndexPtr;        // index variables
	int i, j;        // index variables

	// open the model file
	f = fopen(modelFile, "rb");
	if(f == nullptr)
	{
		LOG("modelFile %s", modelFile);
		exit(1);
	}

	// find length of file
	fseek(f, 0, SEEK_END);
	fileLen = ftell(f);
	fseek(f, 0, SEEK_SET);

	// read entire file into buffer
	buffer = new char[fileLen + 1];
	fread(buffer, sizeof(char), fileLen, f);

	// extract model file header from buffer
	modelHeader = (modelHeader_t*) buffer;

	vertexList = new vector_t[modelHeader->numXYZ * modelHeader->numFrames];

	numVertices = modelHeader->numXYZ;
	numFrames = modelHeader->numFrames;
	frameSize = modelHeader->framesize;

	for(j = 0; j < numFrames; j++)
	{
		frame = (frame_t*) &buffer[modelHeader->offsetFrames + frameSize * j];

		vertexListPtr = (vector_t*) &vertexList[numVertices * j];
		for(i = 0; i < numVertices; i++)
		{
			vertexListPtr[i].point[0] = frame->scale[0] * frame->fp[i].v[0] + frame->translate[0];
			vertexListPtr[i].point[1] = frame->scale[1] * frame->fp[i].v[1] + frame->translate[1];
			vertexListPtr[i].point[2] = frame->scale[2] * frame->fp[i].v[2] + frame->translate[2];
		}
	}

	/**************************************************************/

	modelTex = new Texture();        // = LoadTexture(skinFile);
	modelTex->load_texture(skinFile);

	numST = modelHeader->numST;
	st = new texCoord_t[numST];

	stPtr = (stIndex_t*) &buffer[modelHeader->offsetST];
	for(i = 0; i < numST; i++)
	{
		st[i].s = (float) stPtr[i].s / (float) modelTex->width();
		st[i].t = (float) stPtr[i].t / (float) modelTex->height();
	}

	numTriangles = modelHeader->numTris;
	triIndex = new mesh_t[numTriangles];

	// point to triangle indexes in buffer
	bufIndexPtr = (mesh_t*) &buffer[modelHeader->offsetTris];

	// create a mesh (triangle) list
	for(j = 0; j < numFrames; j++)
	{
		// for all triangles in each frame
		for(i = 0; i < numTriangles; i++)
		{
			triIndex[i].meshIndex[0] = bufIndexPtr[i].meshIndex[0];
			triIndex[i].meshIndex[1] = bufIndexPtr[i].meshIndex[1];
			triIndex[i].meshIndex[2] = bufIndexPtr[i].meshIndex[2];
			triIndex[i].stIndex[0] = bufIndexPtr[i].stIndex[0];
			triIndex[i].stIndex[1] = bufIndexPtr[i].stIndex[1];
			triIndex[i].stIndex[2] = bufIndexPtr[i].stIndex[2];
		}
	}

	fclose(f);
	delete buffer;

	currentFrame = 0;
	nextFrame = 1;
	interpol = 0.0;

	return true;
}
//int MD2Model::LoadModel(char *modelFile)
//{
//	FILE *filePtr;        // file pointer
//	int fileLen;        // length of model file
//	char *buffer;        // file buffer
//
//	modelHeader_t *modelHeader;        // model header
//
////     stIndex_t *stPtr;                       // texture data
//	frame_t *frame;        // frame data
//	vector_t *vertexListPtr;        // index variable
//	mesh_t *triIndex, *bufIndexPtr;        // index variables
//	int i, j;        // index variables
//
//	// open the model file
//	filePtr = fopen(modelFile, "rb");
//	if(filePtr == nullptr)
//	{
//		LOG();
//		exit(1);
//	}
//
//	// find length of file
//	fseek(filePtr, 0, SEEK_END);
//	fileLen = ftell(filePtr);
//	fseek(filePtr, 0, SEEK_SET);
//
//	// read entire file into buffer
//	buffer = new char[fileLen + 1];
//	fread(buffer, sizeof(char), fileLen, filePtr);
//
//	// extract model file header from buffer
//	modelHeader = (modelHeader_t*) buffer;
//
//	// allocate vertex list
//	vertexList = new vector_t[modelHeader->numXYZ * modelHeader->numFrames];
//
//	numVertices = modelHeader->numXYZ;
//	numFrames = modelHeader->numFrames;
//	frameSize = modelHeader->framesize;
//
//	for(j = 0; j < numFrames; j++)
//	{
//		frame = (frame_t*) &buffer[modelHeader->offsetFrames + frameSize * j];
//		vertexListPtr = (vector_t*) &vertexList[numVertices * j];
//
//		for(i = 0; i < numVertices; i++)
//		{
//			vertexListPtr[i].point[0] = frame->scale[0] * frame->fp[i].v[0] + frame->translate[0];
//			vertexListPtr[i].point[1] = frame->scale[1] * frame->fp[i].v[1] + frame->translate[1];
//			vertexListPtr[i].point[2] = frame->scale[2] * frame->fp[i].v[2] + frame->translate[2];
//		}
//	}
//
//	numST = modelHeader->numST;
//	st = new texCoord_t[numST];
//
////     stPtr = (stIndex_t*)&buffer[modelHeader->offsetST];
//	for(i = 0; i < numST; i++)
//	{
//		st[i].s = 0.0;
//		st[i].t = 0.0;
//	}
//
//	numTriangles = modelHeader->numTris;
//	triIndex = new mesh_t[numTriangles];
//
//	// point to triangle indexes in buffer
//	bufIndexPtr = (mesh_t*) &buffer[modelHeader->offsetTris];
//
//	// create a mesh (triangle) list
//	for(j = 0; j < numFrames; j++)
//	{
//		// for all triangles in each frame
//		for(i = 0; i < numTriangles; i++)
//		{
//			triIndex[i].meshIndex[0] = bufIndexPtr[i].meshIndex[0];
//			triIndex[i].meshIndex[1] = bufIndexPtr[i].meshIndex[1];
//			triIndex[i].meshIndex[2] = bufIndexPtr[i].meshIndex[2];
//			triIndex[i].stIndex[0] = bufIndexPtr[i].stIndex[0];
//			triIndex[i].stIndex[1] = bufIndexPtr[i].stIndex[1];
//			triIndex[i].stIndex[2] = bufIndexPtr[i].stIndex[2];
//		}
//	}
//
//	fclose(filePtr);
//	delete buffer;
//
//	modelTex = nullptr;
//	currentFrame = 0;
//	nextFrame = 1;
//	interpol = 0.0;
//
//	return 0;
//}
// desc: animates the model between the keyframes startFrame and endFrame
int ModelMD2::render_frames(int startFrame, int endFrame, float percent)
{
	vector_t *vList;        // current frame vertices
	vector_t *nextVList;        // next frame vertices
	int i;        // index counter
	float x1, y1, z1;        // current frame point values
	float x2, y2, z2;        // next frame point values

	vector_t vertex[3];

	if(currentFrame < startFrame)
		currentFrame = startFrame;

	if(startFrame < 0 || endFrame < 0)
		return -1;

	if(numFrames <= startFrame || numFrames <= endFrame)
		return -1;

	if(interpol >= 1.0)
	{
		interpol = 0.0f;
		currentFrame++;
		if(currentFrame >= endFrame)
			currentFrame = startFrame;

		nextFrame = currentFrame + 1;

		if(nextFrame >= endFrame)
			nextFrame = startFrame;
	}

	vList = &vertexList[numVertices * currentFrame];
	nextVList = &vertexList[numVertices * nextFrame];

	glColor4f(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, modelTex->texID());
	glBegin(GL_TRIANGLES);
	for(i = 0; i < numTriangles; i++)
	{
		// get first points of each frame
		x1 = vList[triIndex[i].meshIndex[0]].point[0];
		y1 = vList[triIndex[i].meshIndex[0]].point[1];
		z1 = vList[triIndex[i].meshIndex[0]].point[2];
		x2 = nextVList[triIndex[i].meshIndex[0]].point[0];
		y2 = nextVList[triIndex[i].meshIndex[0]].point[1];
		z2 = nextVList[triIndex[i].meshIndex[0]].point[2];

		// store first interpolated vertex of triangle
		vertex[0].point[0] = x1 + interpol * (x2 - x1);
		vertex[0].point[1] = y1 + interpol * (y2 - y1);
		vertex[0].point[2] = z1 + interpol * (z2 - z1);

		// get second points of each frame
		x1 = vList[triIndex[i].meshIndex[2]].point[0];
		y1 = vList[triIndex[i].meshIndex[2]].point[1];
		z1 = vList[triIndex[i].meshIndex[2]].point[2];
		x2 = nextVList[triIndex[i].meshIndex[2]].point[0];
		y2 = nextVList[triIndex[i].meshIndex[2]].point[1];
		z2 = nextVList[triIndex[i].meshIndex[2]].point[2];

		// store second interpolated vertex of triangle
		vertex[2].point[0] = x1 + interpol * (x2 - x1);
		vertex[2].point[1] = y1 + interpol * (y2 - y1);
		vertex[2].point[2] = z1 + interpol * (z2 - z1);

		// get third points of each frame
		x1 = vList[triIndex[i].meshIndex[1]].point[0];
		y1 = vList[triIndex[i].meshIndex[1]].point[1];
		z1 = vList[triIndex[i].meshIndex[1]].point[2];
		x2 = nextVList[triIndex[i].meshIndex[1]].point[0];
		y2 = nextVList[triIndex[i].meshIndex[1]].point[1];
		z2 = nextVList[triIndex[i].meshIndex[1]].point[2];

		// store third interpolated vertex of triangle
		vertex[1].point[0] = x1 + interpol * (x2 - x1);
		vertex[1].point[1] = y1 + interpol * (y2 - y1);
		vertex[1].point[2] = z1 + interpol * (z2 - z1);

		// calculate the normal of the triangle
		CalculateNormal(vertex[0].point, vertex[2].point, vertex[1].point);

		// render properly textured triangle
		glTexCoord2f(st[triIndex[i].stIndex[0]].s,
				st[triIndex[i].stIndex[0]].t);
		glVertex3fv(vertex[0].point);

		glTexCoord2f(st[triIndex[i].stIndex[2]].s,
				st[triIndex[i].stIndex[2]].t);
		glVertex3fv(vertex[2].point);

		glTexCoord2f(st[triIndex[i].stIndex[1]].s,
				st[triIndex[i].stIndex[1]].t);
		glVertex3fv(vertex[1].point);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

	interpol += percent;        // increase percentage of interpolation between frames
	return 0;
}
// desc: renders a single key frame
int ModelMD2::render_single_frame(int keyFrame)
{
	vector_t *vList;
	int i;

	// create a pointer to the frame we want to show
	vList = &vertexList[numVertices * keyFrame];

	if(modelTex != nullptr)
		// set the texture
		glBindTexture(GL_TEXTURE_2D, modelTex->texID());

	// display the textured model with proper lighting normals
	glBegin(GL_TRIANGLES);
	for(i = 0; i < numTriangles; i++)
	{
		CalculateNormal(vList[triIndex[i].meshIndex[0]].point,
				vList[triIndex[i].meshIndex[2]].point,
				vList[triIndex[i].meshIndex[1]].point);

		if(modelTex != nullptr)
		{
			glTexCoord2f(st[triIndex[i].stIndex[0]].s, st[triIndex[i].stIndex[0]].t);
			glVertex3fv(vList[triIndex[i].meshIndex[0]].point);

			glTexCoord2f(st[triIndex[i].stIndex[2]].s, st[triIndex[i].stIndex[2]].t);
			glVertex3fv(vList[triIndex[i].meshIndex[2]].point);

			glTexCoord2f(st[triIndex[i].stIndex[1]].s, st[triIndex[i].stIndex[1]].t);
			glVertex3fv(vList[triIndex[i].meshIndex[1]].point);
		}
	}
	glEnd();
	return 0;
}
void ModelMD2::Unload()
{
	if(triIndex != nullptr)
		delete[] triIndex;
	if(vertexList != nullptr)
		delete[] vertexList;
	if(st != nullptr)
		delete[] st;

	if(modelTex != nullptr)
		delete modelTex;
}
void ModelMD2::SetState(modelState_t state)
{
	modelState = state;
}
modelState_t ModelMD2::GetState()
{
	return modelState;
}

