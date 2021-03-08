/*
 *
 */

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "texture.h"

#ifndef LOG
#define LOG(fmt, args...)			do{ \
	printf("tuxRacer--%-40s--%5d--%-10s-- " fmt "\n", __FUNCTION__, __LINE__, __FILE__, ##args); \
	}while(0)
#endif

// desc: Returns a pointer to the bitmap image of the bitmap specified
//       by filename. Also returns the bitmap header information.
//		 No support for 8-bit bitmaps.
//unsigned char *Texture::LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
//{
//	FILE *filePtr;							// the file pointer
//	BITMAPFILEHEADER	bitmapFileHeader;		// bitmap file header
//	unsigned char		*bitmapImage;			// bitmap image data
//	int				imageIdx = 0;			// image index counter
//	unsigned char		tempRGB;				// swap variable
//
//	// open filename in "read binary" mode
//	filePtr = fopen(filename, "rb");
//	if (filePtr == nullptr)
//		return nullptr;
//
//	// read the bitmap file header
//	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
//
//	// verify that this is a bitmap by checking for the universal bitmap id
//	if (bitmapFileHeader.bfType != BITMAP_ID)
//	{
//		fclose(filePtr);
//		return nullptr;
//	}
//
//	// read the bitmap information header
//	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
//
//	// move file pointer to beginning of bitmap data
//	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
//
//	// allocate enough memory for the bitmap image data
//	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);
//
//	// verify memory allocation
//	if (!bitmapImage)
//	{
//		free(bitmapImage);
//		fclose(filePtr);
//		return nullptr;
//	}
//
//	// read in the bitmap image data
//	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
//
//	// make sure bitmap image data was read
//	if (bitmapImage == nullptr)
//	{
//		fclose(filePtr);
//		return nullptr;
//	}
//
//	// swap the R and B values to get RGB since the bitmap color format is in BGR
//	for (imageIdx = 0; imageIdx < (int)bitmapInfoHeader->biSizeImage; imageIdx+=3)
//	{
//		tempRGB = bitmapImage[imageIdx];
//		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
//		bitmapImage[imageIdx + 2] = tempRGB;
//	}
//
//	// close the file and return the bitmap image data
//	fclose(filePtr);
//	return bitmapImage;
//}

/*****************************************************************************
 Loads a bitmap file normally, and then adds an alpha component to use for
 blending
 *****************************************************************************/
//unsigned char *Texture::LoadBitmapFileWithAlpha(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
//{
//  unsigned char *bitmapImage = LoadBitmapFile(filename, bitmapInfoHeader);
//  unsigned char *bitmapWithAlpha = (unsigned char *)malloc(bitmapInfoHeader->biSizeImage * 4 / 3);
//
//  // loop through the bitmap data
//  for (int src = 0, dst = 0; src < bitmapInfoHeader->biSizeImage; src +=3, dst +=4)
//  {
//    // if the pixel is black, set the alpha to 0. Otherwise, set it to 255.
//    if (bitmapImage[src] == 0 && bitmapImage[src+1] == 0 && bitmapImage[src+2] == 0)
//      bitmapWithAlpha[dst+3] = 0;
//    else
//      bitmapWithAlpha[dst+3] = 0xFF;
//
//    // copy pixel data over
//    bitmapWithAlpha[dst] = bitmapImage[src];
//    bitmapWithAlpha[dst+1] = bitmapImage[src+1];
//    bitmapWithAlpha[dst+2] = bitmapImage[src+2];
//  }
//
//  free(bitmapImage);
//
//  return bitmapWithAlpha;
//}
// desc: loads a PCX file into memory
unsigned char *Texture::do_load_pcx_imagine(char *filename, PCXHEADER *pcxHeader)
{
	int idx = 0;                  // counter index
	int c;                             // used to retrieve a char from the file
	int i;                             // counter index
	int numRepeat;
	FILE *filePtr;                // file handle
	int width;                         // pcx width
	int height;                        // pcx height
	unsigned char *pixelData;        // pcx image data
	unsigned char *paletteData;        // pcx palette data

	// open PCX file
	filePtr = fopen(filename, "rb");
	if(filePtr == nullptr)
		return nullptr;

	// retrieve first character; should be equal to 10
	c = getc(filePtr);
	if(c != 10)
	{
		fclose(filePtr);
		return nullptr;
	}

	// retrieve next character; should be equal to 5
	c = getc(filePtr);
	if(c != 5)
	{
		fclose(filePtr);
		return nullptr;
	}

	// reposition file pointer to beginning of file
	rewind(filePtr);

	// read 4 characters of data to skip
	fgetc(filePtr);
	fgetc(filePtr);
	fgetc(filePtr);
	fgetc(filePtr);

	// retrieve leftmost x value of PCX
	pcxHeader->xMin = fgetc(filePtr);        // loword
	pcxHeader->xMin |= fgetc(filePtr) << 8;        // hiword

	// retrieve bottom-most y value of PCX
	pcxHeader->yMin = fgetc(filePtr);        // loword
	pcxHeader->yMin |= fgetc(filePtr) << 8;        // hiword

	// retrieve rightmost x value of PCX
	pcxHeader->xMax = fgetc(filePtr);        // loword
	pcxHeader->xMax |= fgetc(filePtr) << 8;        // hiword

	// retrieve topmost y value of PCX
	pcxHeader->yMax = fgetc(filePtr);        // loword
	pcxHeader->yMax |= fgetc(filePtr) << 8;        // hiword

	// calculate the width and height of the PCX
	width = pcxHeader->xMax - pcxHeader->xMin + 1;
	height = pcxHeader->yMax - pcxHeader->yMin + 1;

	// allocate memory for PCX image data
	pixelData = (unsigned char*) malloc(width * height);

	// set file pointer to 128th byte of file, where the PCX image data starts
	fseek(filePtr, 128, SEEK_SET);

	// decode the pixel data and store
	while(idx < (width * height))
	{
		c = getc(filePtr);
		if(c > 0xbf)
		{
			numRepeat = 0x3f & c;
			c = getc(filePtr);

			for(i = 0; i < numRepeat; i++)
			{
				pixelData[idx++] = c;
			}
		}
		else
			pixelData[idx++] = c;

		fflush(stdout);
	}

	// allocate memory for the PCX image palette
	paletteData = (unsigned char*) malloc(768);

	// palette is the last 769 bytes of the PCX file
	fseek(filePtr, -769, SEEK_END);

	// verify palette; first character should be 12
	c = getc(filePtr);
	if(c != 12)
	{
		fclose(filePtr);
		return nullptr;
	}

	// read and store all of palette
	for(i = 0; i < 768; i++)
	{
		c = getc(filePtr);
		paletteData[i] = c;
	}

	// close file and store palette in header
	fclose(filePtr);
	pcxHeader->palette = paletteData;

	// return the pixel image data
	return pixelData;
}

// LoadPCXTexture()
// desc: loads a PCX image file as a texture
void Texture::load_pcx_imagine(char *filename)
{
	PCXHEADER texInfo;            // header of texture
//     texture_t *thisTexture;       // the texture
	unsigned char *unscaledData;            // used to calculate pcx
	int i;                             // index counter
	int j;                             // index counter
	int w;                         // width of texture
	int h;                        // height of texture

	// load the PCX file into the texture struct
	data = do_load_pcx_imagine(filename, &texInfo);
	if(data == nullptr)
	{
		LOG("filename %s", filename);
		exit(1);
	}

	// store the texture information
	palette = texInfo.palette;
	width_ = texInfo.xMax - texInfo.xMin + 1;
	height_ = texInfo.yMax - texInfo.yMin + 1;
	textureType = PCX;

	w = width_;
	h = height_;

	// allocate memory for the unscaled data
	unscaledData = (unsigned char*) malloc(w * h * 4);

	// store the unscaled data via the palette
	for(j = 0; j < h; j++)
	{
		for(i = 0; i < w; i++)
		{
			unscaledData[4 * (j * w + i) + 0] = (unsigned char) palette[3 * data[j * w + i] + 0];
			unscaledData[4 * (j * w + i) + 1] = (unsigned char) palette[3 * data[j * w + i] + 1];
			unscaledData[4 * (j * w + i) + 2] = (unsigned char) palette[3 * data[j * w + i] + 2];
			unscaledData[4 * (j * w + i) + 3] = (unsigned char) 255;
		}
	}

	// find width and height's nearest greater power of 2
	// find width's
	i = 0;
	while(w)
	{
		w /= 2;
		i++;
	}
	scaledHeight = (long) pow(2, i - 1);

	// find height's
	i = 0;
	while(h)
	{
		h /= 2;
		i++;
	}
	scaledWidth = (long) pow(2, i - 1);

	// clear the texture data
	if(data != nullptr)
	{
		free(data);
		data = nullptr;
	}

	// reallocate memory for the texture data
	data = (unsigned char*) malloc(scaledWidth * scaledHeight * 4);

	// use the GL utility library to scale the texture to the unscaled dimensions
	gluScaleImage(GL_RGBA, this->width_, this->height_, GL_UNSIGNED_BYTE, unscaledData, scaledWidth, scaledHeight,
	GL_UNSIGNED_BYTE, data);

	free(unscaledData);
//     return thisTexture;
}

#ifndef LOG
#define LOG(fmt, args...)			do{printf("----%-30s--%5d--%-10s--" fmt "\n", \
		__FUNCTION__, __LINE__, __FILE__, ##args);}while(0)
#endif

// 函数power_of_two用于判断一个整数是不是2的整数次幂
inline int power_of_two(int n)
{
	if(n <= 0)
		return 0;
	return (n & (n - 1)) == 0;
}

unsigned char * Texture::do_load_bmp_imagine(const char * file_name, int * width, int * height, GLint * total_bytes)
{
#define BMP_Header_Length 54  //图像数据在内存块中的偏移量

//	LOG("file_name: %s", file_name);
	FILE* pFile = fopen(file_name, "rb");
	if(pFile == 0)
	{
		LOG("file_name: %s", file_name);
		exit(1);
	}

	// 读取文件中图象的宽度和高度
	fseek(pFile, 0x0012, SEEK_SET);
	fread(width, 4, 1, pFile);
	fread(height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// 计算每行像素所占字节数，并根据此数据计算总像素字节数
	{
		GLint line_bytes = *width * 3;
		while(line_bytes % 4 != 0)
			++line_bytes;
		*total_bytes = line_bytes * *height;
	}

	// 根据总像素字节数分配内存
	unsigned char *pixels = (GLubyte*) calloc(*total_bytes, 1);
	if(pixels == 0)
	{
		LOG();
		exit(1);
	}

	// 读取像素数据
	if(fread(pixels, *total_bytes, 1, pFile) <= 0)
	{
		LOG();
		exit(1);
	}
	fclose(pFile);

	// 对就旧版本的兼容，如果图象的宽度和高度不是的整数次方，则需要进行缩放
	// 若图像宽高超过了OpenGL规定的最大值，也缩放
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
//		LOG("file_name: %s, *width: %d, *height: %d, *total_bytes: %d, max: %d",
//		file_name, *width, *height, *total_bytes, max);

		if(!power_of_two(*width)
				|| !power_of_two(*height)
				|| *width > max
				|| *height > max)
		{

			const GLint new_width = 256;
			const GLint new_height = 256;        // 规定缩放后新的大小为边长的正方形
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// 计算每行需要的字节数和总字节数
			new_line_bytes = new_width * 3;
			while(new_line_bytes % 4 != 0)
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			new_pixels = (GLubyte*) calloc(new_total_bytes, 1);
			if(new_pixels == 0)
			{
				LOG();
				exit(1);
			}

			gluScaleImage(GL_RGBA,
					*width, *height, GL_UNSIGNED_BYTE, pixels,
					new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
			free(pixels);
			pixels = new_pixels;
			*width = new_width;
			*height = new_height;
			*total_bytes = new_total_bytes;
		}
	}

	return pixels;
}
void Texture::load_bmp_imagine(char *filename)
{
	int w;
	int h;
	int t;

//	data = LoadBitmapFileWithAlpha(filename);
	data = do_load_bmp_imagine(filename, &w, &h, &t);
	if(data == nullptr)
	{
		LOG("filename %s", filename);
		exit(1);
	}

	width_ = w;
	height_ = h;
	palette = nullptr;
	scaledHeight = 0;
	scaledWidth = 0;
	textureType = BMP;
}
void Texture::load_imagine(char *filename)
{
	char *extStr;

	// get extension from filename
	extStr = strchr(filename, '.');
	extStr++;

	// set the texture type based on extension of filename
	if((strcmp(extStr, "BMP") == 0) || (strcmp(extStr, "bmp") == 0))
		load_bmp_imagine(filename);
	else
		if((strcmp(extStr, "PCX") == 0) || (strcmp(extStr, "pcx") == 0))
			load_pcx_imagine(filename);
		else
			if((strcmp(extStr, "TGA") == 0) || (strcmp(extStr, "tga") == 0))
				load_tga_imagine(filename);
}
Texture::Texture()
{
	data = nullptr;
	palette = nullptr;
	textureType = ERR;
	tgaImageCode = -1;        // 0 = not TGA image, 2 = color, 3 = greyscale

	width_ = -1;
	height_ = -1;
	bitDepth = -1;
	texID_ = 0;
}
Texture::~Texture()
{
//	glDeleteTextures(1, &texID);

	if(data != nullptr)
		free(data);
	if(palette != nullptr)
		free(palette);

	data = nullptr;
	palette = nullptr;
}
unsigned char *Texture::do_load_tga_imagine(char *filename, TGAHEADER *tgaHeader)
{
	FILE *filePtr;
	unsigned char ucharBad;        // garbage data
	short int sintBad;        // garbage data
	long imageSize;        // size of TGA image
	int colorMode;			// 4 for RGBA, 3 for RGB
	long imageIdx;			// counter variable
	unsigned char colorSwap;        // swap variable
	unsigned char *imageData;        // the TGA data

	// open the TGA file
	filePtr = fopen(filename, "rb");
	if(!filePtr)
		return nullptr;

	// read first two bytes of garbage
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

	// read in the image type
	fread(&tgaHeader->imageTypeCode, sizeof(unsigned char), 1, filePtr);

	// for our purposes, the image type should be either a 2 or a 3
	if((tgaHeader->imageTypeCode != 2) && (tgaHeader->imageTypeCode != 3))
	{
		fclose(filePtr);
		return nullptr;
	}

	// read 13 bytes of garbage data
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);

	// read image dimensions
	fread(&tgaHeader->imageWidth, sizeof(short int), 1, filePtr);
	fread(&tgaHeader->imageHeight, sizeof(short int), 1, filePtr);

	// read bit depth
	fread(&tgaHeader->bitCount, sizeof(unsigned char), 1, filePtr);

	// read garbage
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

	// colormode -> 3 = BGR, 4 = BGRA
	colorMode = tgaHeader->bitCount / 8;
	imageSize = tgaHeader->imageWidth * tgaHeader->imageHeight * colorMode;

	// allocate memory for image data
	imageData = (unsigned char*) malloc(sizeof(unsigned char) * imageSize);

	// read image data
	fread(imageData, sizeof(unsigned char), imageSize, filePtr);

	// change BGR to RGB so OpenGL can use the data
	for(imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
	{
		colorSwap = imageData[imageIdx];
		imageData[imageIdx] = imageData[imageIdx + 2];
		imageData[imageIdx + 2] = colorSwap;
	}

	fclose(filePtr);
	return imageData;
}

void Texture::load_tga_imagine(char *filename)
{
	TGAHEADER tga;        // BMP header

	data = do_load_tga_imagine(filename, &tga);
	if(data == nullptr)
	{
		LOG("filename %s", filename);
		exit(1);
	}

	width_ = tga.imageWidth;
	height_ = tga.imageHeight;
	palette = nullptr;
	scaledHeight = 0;
	scaledWidth = 0;
	tgaImageCode = tga.imageTypeCode;
	bitDepth = tga.bitCount;
	textureType = TGA;
}
int Texture::load_texture(char *filename)
{
	load_imagine(filename);

	// set the proper parameters for an MD2 texture
	glGenTextures(1, &texID_);
	glBindTexture(GL_TEXTURE_2D, texID_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	switch(textureType)
	{
		case BMP:
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width_, height_,
			GL_RGB, GL_UNSIGNED_BYTE, data);
			break;
		case PCX:
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width_, height_,
			GL_RGBA, GL_UNSIGNED_BYTE, data);
			break;
		case TGA:
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width_, height_,
			GL_RGB, GL_UNSIGNED_BYTE, data);
			break;
		default:
			break;
	}

	return texID_;
}
int Texture::texID()
{
	return texID_;
}
int Texture::width()
{
	return width_;
}
int Texture::height()
{
	return height_;
}

int Load_texture(char *filename)
{
	Texture t;
	return t.load_texture(filename);
}

