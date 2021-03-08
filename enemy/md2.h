/*
 *
 */

#ifndef __MD2_H
#define __MD2_H

#include "h.h"
#include <GL/gl.h>

#include "vector.h"
#include "texture.h"

#define MAX_FRAMES 512

enum modelState_t
{
	MODEL_IDLE,        // idle animation
	MODEL_CROUCH,        // crouch animation
	MODEL_RUN,        // running animation
	MODEL_JUMP,        // jumping animation
	MODEL_FIRE,        // model shooting gun
	MODEL_DYING,			// model dying
	MODEL_DEAD,
};

struct vector_t
{
	float point[3];
} ;

vector_t operator-(vector_t a, vector_t b);
vector_t operator*(float f, vector_t b);
vector_t operator/(vector_t a, vector_t b);
vector_t operator+(vector_t a, vector_t b);

void CalculateNormal(float *p1, float *p2, float *p3);

// texture coordinate
struct texCoord_t
{
	float s;
	float t;
} ;

// texture coordinate index
struct stIndex_t
{
	short s;
	short t;
} ;

// info for a single frame point
struct framePoint_t
{
	unsigned char v[3];
	unsigned char normalIndex;        // not used
} ;

// information for a single frame
struct frame_t
{
	float scale[3];
	float translate[3];
	char name[16];
	framePoint_t fp[1];
} ;

// data for a single triangle
struct mesh_t
{
	unsigned short meshIndex[3];        // vertex indices
	unsigned short stIndex[3];        // texture coordinate indices
};

struct modelHeader_t
{
	int ident;        // identifies as MD2 file "IDP2"
	int version;        // mine is 8
	int skinwidth;        // width of texture
	int skinheight;        // height of texture
	int framesize;        // number of bytes per frame
	int numSkins;        // number of textures
	int numXYZ;        // number of points
	int numST;        // number of texture
	int numTris;        // number of triangles
	int numGLcmds;
	int numFrames;        // total number of frames
	int offsetSkins;        // offset to skin names (64 bytes each)
	int offsetST;        // offset of texture s-t values
	int offsetTris;        // offset of triangle mesh
	int offsetFrames;        // offset of frame data (points)
	int offsetGLcmds;        // type of OpenGL commands to use
	int offsetEnd;        // end of file
};

class ModelMD2
{
private:
	int numFrames;				// number of model frames
	int numVertices;			// number of vertices
	int numTriangles;        	// number of triangles
	int numST;               	// number of skins
	int frameSize;           	// size of each frame in bytes
	mesh_t *triIndex;        	// triangle list
	texCoord_t *st;          	// texture coordinate list
	vector_t *vertexList;        // vertex list
	Texture * modelTex;       	// texture data

//	int LoadModel(char *modelFile);

public:
	int currentFrame;        // current frame # in animation
	int nextFrame;           // next frame # in animation
	modelState_t modelState;
	float interpol;          // percent through current frame

	ModelMD2();
	virtual ~ModelMD2();

	int Load(char *modelFile, char *skinFile);        // load model and skin/texture
	void Unload();

	int render_frames(int startFrame, int endFrame, float percent);
	int render_single_frame(int Frame);
	void SetState(modelState_t state);
	modelState_t GetState();
};

#endif
