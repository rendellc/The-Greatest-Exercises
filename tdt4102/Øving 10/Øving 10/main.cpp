//#define NDEBUG

#include "Matrix.h"
#include "Vector.h"
#include "Image.h"
#include "Line.h"
#include "Rectangle.h"
#include "Circle.h"
#include "HalfCircle.h"
//#include "CircleArc.h"
#include "Canvas.h"
#include <iostream>
#include <string>
#include <memory>



using namespace std;

void matrixTest();
void imageTest();
void drawSmiley(string filename);
void drawBartOnKvinne();

int main()
{
	//matrixTest();

	//imageTest();

	//drawSmiley("smileyTest.bmp");

	drawBartOnKvinne();

	system("pause");
	return 0;
}

void matrixTest()
{
	Matrix M(4, 4);
	for (unsigned int r = 0; r < 4; ++r) {
		for (unsigned int c = 0; c < 4; ++c) {
			M.set(r, c, r + c);
		}
	}
	cout << "M:\n" << M << endl;

	Vector V(4);
	V.set(0, 3.0);
	V.set(1, 2.5);
	V.set(2, 10.0);
	V.set(3, 0.0);

	cout << "V:\n" << V << endl;

	Matrix Product(M*V);
	cout << "Product:\n" << Product << endl;
	cout << "Resultat for hånd:\n 22.5\n38\n53.5\n69" << endl;
}

void imageTest()
{	
	unsigned int height = 500;
	unsigned int width = 500;

	Color bg(193, 84, 193);
	Color white(0, 255, 255); // it's not white
	Color red(255, 0, 0);
	
	Image img(width,height);
	
	img.fill(bg);
	//saveImage(img, "image_test1.bmp");

	img.fill(white);
	img.setPixelColor(width / 2, height / 2, red);
	saveImage(img, "image_redDotCenter.bmp");

	img.fill(white);
	Line line1(0, 0, 100, 50, red);
	line1.draw(img);
	saveImage(img, "line_100_50.bmp");

	img.fill(white);
	Line line2(0, 0, 100, 200, red);
	line2.draw(img);
	saveImage(img, "line_100_200.bmp");

	img.fill(white);
	Line line3(50, 50, 25, 100, red);
	line3.draw(img);
	saveImage(img, "line_straight_up.bmp");

	img.fill(white);
	Line line4(100, -60, 100, 100, red);
	line4.draw(img);
	saveImage(img, "line_dot.bmp");

	img.fill(white);
	Rectangle rect(200, 200, 100, -50, Color(0, 255, 0));
	rect.draw(img);
	saveImage(img, "rectangle.bmp");

	img.fill(white);
	Circle circle(width/2, width / 2, height / 2, Color(0,0,0));
	circle.draw(img);
	saveImage(img, "circle.bmp");


	cout << "finito!" << endl;
}

// draw smiley in the center of the image
void drawSmiley(string filename)
{
	const size_t height = 500;
	const size_t width = 500;

	Canvas canvas;

	Image img(width, height);

	// *** Colors **'
	Color bgColor(153, 190, 200);
	Color headColor(255, 153, 51);
	Color smileColor(255, 51, 51);
	Color eyeColor(255, 255, 255);
	Color pupilColor(0, 0, 0);

	// background
	Rectangle background(0, 0, width, height, bgColor);
	canvas.addShape(&background);

	// Head is a circle
	const size_t headCenterX = width / 2;
	const size_t headCenterY = height / 2;
	const size_t headSize = height/3;
	Circle head(headSize, headCenterX, headCenterY, headColor);
	canvas.addShape(&head);

	// Smile
	const size_t smileCenterX = headCenterX;
	const size_t smileCenterY = headCenterY - headSize / 5;
	const size_t smileSize = headSize / 2;
	HalfCircle smile(smileSize, smileCenterX, smileCenterY, smileColor);
	canvas.addShape(&smile);

	// Eyes
	const size_t eyeSize = headSize / 5;
	const size_t closeness = 3; // changes distance between eyes 
	const size_t leftEyeCenterX = headCenterX - headSize / closeness;
	const size_t rightEyeCenterX = headCenterX + headSize / closeness;
	const size_t eyeCenterY = headCenterY + headSize / 4;
	Circle leftEye(eyeSize, leftEyeCenterX, eyeCenterY, eyeColor);
	Circle rightEye(eyeSize, rightEyeCenterX, eyeCenterY, eyeColor);
	canvas.addShape(&leftEye);
	canvas.addShape(&rightEye);

	// pupils
	const size_t pupilSize = eyeSize / 2;
	Circle leftPupil(pupilSize, leftEyeCenterX, eyeCenterY, pupilColor);
	Circle rightPupil(pupilSize, rightEyeCenterX, eyeCenterY, pupilColor);
	canvas.addShape(&leftEye);
	canvas.addShape(&rightEye);

	canvas.rasterizeTo(img);
	saveImage(img, filename);
}

void drawBartOnKvinne() {
	Image* lenaPt = loadImage("lena512.bmp");
	
	
	Color bartColor(10, 10, 10);
	Canvas canvas;

	//Rectangle styggBart(295, 175, 305, 185, bartColor);
	//canvas.addShape(&styggBart);
	canvas.rasterizeTo(*lenaPt);

	saveImage(*lenaPt, "lenaBart.bmp");
	delete lenaPt;
}