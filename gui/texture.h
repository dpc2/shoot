#ifndef __TEXTURE_H
#define __TEXTURE_H

#define BITMAP_ID 0x4D42		// the universal bitmap ID

enum texTypes_t
{
	PCX,
	BMP,
	TGA,
	ERR,
};


// only partial pcx file header
typedef struct
{
	unsigned char manufacturer;
	unsigned char version;
	unsigned char encoding;
	unsigned char bits;
	unsigned char xMin;
	unsigned char yMin;
	unsigned char xMax;
	unsigned char yMax;
	unsigned char *palette;
} PCXHEADER;

typedef struct
{
	unsigned char imageTypeCode;
	short int imageWidth;
	short int imageHeight;
	unsigned char bitCount;
} TGAHEADER;

class Texture
{
private:
	long int scaledWidth;
	long int scaledHeight;
	unsigned char *palette;

	texTypes_t textureType;
	unsigned char tgaImageCode;        // 0 = not TGA image, 2 = color, 3 = greyscale
	unsigned char *data;
	int width_;
	int height_;
	int bitDepth;
	unsigned int texID_;
//	unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
//	unsigned char *LoadBitmapFileWithAlpha(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);

	void load_imagine(char *filename);
	void load_pcx_imagine(char *filename);
	void load_bmp_imagine(char *filename);
	void load_tga_imagine(char *filename);
	unsigned char *do_load_pcx_imagine(char *filename, PCXHEADER *pcxHeader);
	unsigned char * do_load_bmp_imagine(const char * file_name, int * width, int * height, int * total_bytes);
	unsigned char *do_load_tga_imagine(char *filename, TGAHEADER *tgaHeader);

public:
	Texture();
	~Texture();

	int load_texture(char *filename);
	int texID();
	int width();
	int height();
};

int Load_texture(char *filename);

#endif
