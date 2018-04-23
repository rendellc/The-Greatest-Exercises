#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include "Image.h"

/////////////////////////////////////////////////////////////////////
//  NB! Include this file and the file Image.h in your project.    //
//  You should *NOT* do any changes to this file.                  //
//                                                                 //
//  Disclaimer: Provided as is etc. etc. No rights reserved.       //
/////////////////////////////////////////////////////////////////////

// SaveImage/LoadImage written by Einar Johan Trøan Sømåen (somaen@stud.ntnu.no)
// Version 6 - 2014-03-11
// Thanks to Einar Hov for patches supplied during the spring semester 2014.

// Reference-information regarding the BMP-file-format used from:
// http://en.wikipedia.org/wiki/BMP_file_format#File_structure

// Convenience read-functions:
// TODO: This code does not support Big-Endian computers, like old PowerPC Macs.
// The file-reading functions below are however a convenient place to add the
// endian-swapping needed for such support.
namespace FileIO {
	static char readChar(std::istream &stream) {
		char val = 0;
		stream.read(&val, 1);
		return val;
	}

	static unsigned char readUnsignedChar(std::istream &stream) {
		unsigned char val = 0;
		stream.read((char *)&val, 1);
		return val;
	}

	static short readShort(std::istream &stream) {
		short val = 0;
		stream.read((char *)&val, 2);
		return val;
	}

	static signed int readSignedInt(std::istream &stream) {
		signed int val = 0;
		stream.read((char *)&val, 4);
		return val;
	}

	static unsigned int readUnsignedInt(std::istream &stream) {
		unsigned int val = 0;
		stream.read((char *)&val, 4);
		return val;
	}

	// Convenience write-functions:
	static void writeChar(std::ostream &stream, char val) {
		stream.write(&val, 1);
	}

	static void writeShort(std::ostream &stream, short val) {
		stream.write((char *)&val, 2);
	}

	static void writeSignedInt(std::ostream &stream, signed int val) {
		stream.write((char *)&val, 4);
	}

	static void writeUnsignedInt(std::ostream &stream, unsigned int val) {
		stream.write((char *)&val, 4);
	}
}

// Avoid polluting the student's namespace.
using namespace FileIO;

// BMP-header-constants:
static const short BITS_PER_PIXEL = 24;
static const int BYTES_PER_PIXEL = BITS_PER_PIXEL / 8;

static const int BMPHEADER_SIZE = 54;
// Header
static const char HEADER1 = 'B';
static const char HEADER2 = 'M';
// DIB
static const unsigned int DIB_SIZE = 40; // Should be 40
static const short int COLOR_PLANES = 1; // 1

unsigned int rowSize(unsigned int width, unsigned int bpp) {
	// http://en.wikipedia.org/wiki/BMP_file_format#Pixel_storage
	return ((bpp * width + 31) / 32) * 4;
}

Image *loadImage(const std::string &filename) {
	std::fstream file;
	file.open(filename.c_str(), std::ios::in | std::ios::binary);

	if (!file) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return NULL;
	}
	if (!(readChar(file) == HEADER1)) {
		file.close();
		std::cerr << "Failed reading BMP-header: No 'B' " << std::endl;
		return NULL;
	}
	if (!(readChar(file) == HEADER2)) {
		file.close();
		std::cerr << "Failed reading BMP-header: No 'M' " << std::endl;
		return NULL;
	}
	unsigned int fileSize = readUnsignedInt(file);  // size (bmpheader + (row_size * imageHeight))
	readUnsignedInt(file);  // Reserved
	unsigned int offset = readUnsignedInt(file);
	if (!(readUnsignedInt(file) == DIB_SIZE)) {   // dib_size
		file.close();
		std::cerr << "Failed reading BMP-header: Invalid DIB-size " << std::endl;
		return NULL;
	}
	int imageWidth = readSignedInt(file);
	int imageHeight = readSignedInt(file);
	if (imageWidth < 0 || imageHeight < 0) {
		file.close();
		std::cerr << "Failed reading BMP-header: Negative width or height not supported "
			<< imageWidth << " x " << imageHeight << std::endl;
		return NULL;
	}
	Image *image = new Image(imageWidth, imageHeight);

	readShort(file);  // color_planes
	short bpp = readShort(file);
	if (!(bpp == BITS_PER_PIXEL) && !(bpp == 8)) { // bits per pixel
		file.close();
		delete image;
		std::cerr << "Failed reading BMP-header: Unsupported bpp " << bpp << std::endl;
		return NULL;
	}
	if (readUnsignedInt(file) != 0) {  // Compression_method
		file.close();
		delete image;
		std::cerr << "Failed reading BMP-header: Compression not supported" << std::endl;
		return NULL;
	}
	unsigned int imageSize = readUnsignedInt(file);
	if (imageSize != (rowSize(image->getWidth(), bpp) * image->getHeight()) && imageSize != 0) {   // imageSize;
		file.close();
		delete image;
		std::cerr << "Failed reading BMP-header: Invalid image-size " << imageSize << std::endl;
		return NULL;
	}
	readSignedInt(file);  // horizontal_res
	readSignedInt(file);  // vertical_res
	unsigned int paletteColors = readUnsignedInt(file);  // palette_colors
	readUnsignedInt(file);  // important_colors

	if (paletteColors == 0 && bpp == 8) {
		// 0 in a 8bpp image means 2^n colors, hardcode for 8bpp, as that is the only non 24bpp we support.
		paletteColors = 256;
	}

	// Additional sanity-checks:
	bool failure = false;
	// Verify that the reported fileSize is atleast as large as the image should be.
	// BMPs are apparently allowed to be larger than the usefull data they contain.
	if (fileSize < (offset + (rowSize(image->getWidth(), bpp) * imageHeight))) {
		std::cerr << "Failed reading BMP-header: Image size mismatch" << std::endl;
		failure = true;
	}

	if (failure) {
		delete image;
		file.close();
		return NULL;
	}

	// http://en.wikipedia.org/wiki/BMP_file_format#Pixel_storage
	int padBytes = rowSize(image->getWidth(), bpp) - (image->getWidth() * BYTES_PER_PIXEL);

	if (bpp == 8) { // Indexed, color-mapped image
					// Read palette:
		unsigned char *palette = new unsigned char[paletteColors * 4];
		// Only works on Little-Endian-machines
		for (unsigned int i = 0; i < paletteColors * 4; i++) {
			palette[i] = readUnsignedChar(file);
		}
		file.seekg(offset, std::ios::beg);
		for (unsigned int y = 0; y < image->getHeight(); y++) {
			for (unsigned int x = 0; x < image->getWidth(); x++) {
				if (!file.good()) {
					file.close();
					delete image;
					delete[] palette;
					std::cerr << "Failed reading BMP: Error while reading image data" << std::endl;
					return NULL;
				}
				unsigned int index = readUnsignedChar(file);
				if (index > paletteColors) {
					std::cerr << "Failed reading BMP: Indexed color out of range" << std::endl;
					delete image;
					file.close();
					return NULL;
				}
				Color c(palette[index * 4 + 0], palette[index * 4 + 1], palette[index * 4 + 2]);
				image->setPixelColor(x, y, c);
			}
			if (padBytes) {
				file.ignore(padBytes);
			}

		}
		delete[] palette;
	}
	else if (bpp == 24) {
		file.seekg(offset, std::ios::beg);
		for (unsigned int y = 0; y < image->getHeight(); y++) {
			if (!file.good()) {
				file.close();
				delete image;
				std::cerr << "Failed reading BMP: Error while reading image data at line" << y << std::endl;
				return NULL;
			}
			for (unsigned int x = 0; x < image->getWidth(); x++) {
				Color pixel;
				pixel.blue = readUnsignedChar(file);
				pixel.green = readUnsignedChar(file);
				pixel.red = readUnsignedChar(file);
				image->setPixelColor(x, y, pixel);
			}

			// Rows in BMPs are padded to power-of-four lengths.
			if (padBytes) {
				file.ignore(padBytes);
			}
		}
	}

	file.close();
	// TODO: Differing sizes?
	return image;
}


int saveImage(const Image &image, const std::string &filename) {
	if (image.getWidth() > INT_MAX || image.getHeight() > INT_MAX) { // Might want to use 0x7FFFFFFF to avoid platform specifics
		std::cerr << "Failed writing BMP: Image dimensions too large " << image.getWidth() << " x "
			<< image.getHeight() << std::endl;
		return -1;
	}
	std::fstream file;
	file.open(filename.c_str(), std::ios::out | std::ios::binary);
	if (!file.is_open()) {
		return -1;
	}

	// Write Header:
	writeChar(file, HEADER1);
	writeChar(file, HEADER2);
	writeUnsignedInt(file, BMPHEADER_SIZE + rowSize(image.getWidth(), BITS_PER_PIXEL) * image.getHeight());   // size
	writeUnsignedInt(file, 0);  // reserved
	writeUnsignedInt(file, BMPHEADER_SIZE);  //offset;
											 // DIB
	writeUnsignedInt(file, DIB_SIZE);
	writeSignedInt(file, image.getWidth());
	writeSignedInt(file, image.getHeight());

	writeShort(file, COLOR_PLANES);  // color_planes
	writeShort(file, BITS_PER_PIXEL);
	writeUnsignedInt(file, 0);  // compression_method
	writeUnsignedInt(file, rowSize(image.getWidth(), BITS_PER_PIXEL) * image.getHeight());   // imageSize
	writeSignedInt(file, 0);  // horizontal_res
	writeSignedInt(file, 0);  // vertical_res
	writeUnsignedInt(file, 0);  // palette_colors
	writeUnsignedInt(file, 0);  // important_colors

								// Write Actual data:

								// http://en.wikipedia.org/wiki/BMP_file_format#Pixel_storage
	unsigned int imagePitch = image.getWidth() * BYTES_PER_PIXEL;
	unsigned int padBytes = rowSize(image.getWidth(), BITS_PER_PIXEL) - (image.getWidth() * BYTES_PER_PIXEL);

	unsigned char * pixelRow = new unsigned char[imagePitch + padBytes];

	// BMPs have 0,0 in lower-left corner, so flip.
	for (unsigned int y = 0; y < image.getHeight(); y++) {
		if (!file.good()) {
			file.close();
			std::cerr << "Failed writing BMP: Error while writing Image data" << std::endl;
			return -1;
		}

		memcpy(pixelRow, image.getScanLine(y), imagePitch);

		// Swap R and B (as BMP is stored in the opposite order)
		for (unsigned int x = 0; x < imagePitch; x += BYTES_PER_PIXEL) {
			std::swap(pixelRow[x], pixelRow[x + 2]);
		}

		//Write Line
		// Rows in BMPs are padded to multiple-of-four lengths.
		// Thus we need to also write the pad-bytes, which we
		// don't care about the value of.
		file.write((const char*)pixelRow, imagePitch + padBytes);
	}

	delete[] pixelRow;

	file.close();
	return 0;
}
