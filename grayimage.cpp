#include <stdio.h>
#include <cv.h>
#include <highgui.h>


IplImage *originalImage, *LBC4Image, *LBC8Image;

unsigned char LBC [495][369];
int i, j;

unsigned char T(int row, int col)
{
	
	CvScalar scalar;

	scalar = cvGet2D(originalImage, row, col);
	LBC [row][col] = (unsigned char) scalar.val[2];
	if (LBC [row][col]-LBC [i][j] < 0)
		return 0;
	else
		return 1;
	
}

void main ()
{ 
	CvScalar scalar;
	int height, width;

	originalImage = cvLoadImage("thomas.jpg", 1); //Load image
	LBC4Image = cvCloneImage(originalImage);
	LBC8Image = cvCloneImage(originalImage);
	
	height = cvGetDimSize(originalImage, 0); //Get original image's height
	width = cvGetDimSize(originalImage, 1); //Get original image's width

	
	
    for(i=0; i<=height-1; i++)
	{
        for(j=0; j<=width-1; j++)
		{
            scalar=cvGet2D(originalImage, i, j); 
			LBC[i][j] = (unsigned char) scalar.val[2];
			
        }
    }
	
	// 4-neighbor LBC

	for(i=1; i<=height-2; i++)
	{
		for(j=1; j<=width-2; j++)
		{
			LBC[i][j] = T(i-1,j)*16+T(i,j+1)*32+T(i+1,j)+T(i,j)*64+T(i,j-1)*128;
			scalar = CV_RGB(LBC[i][j], LBC[i][j], LBC[i][j]);
			cvSet2D(LBC4Image, i, j, scalar);
			
		}
	}
	//8-neighbor LBC

	for(i=1; i<=height-2; i++)
	{
		for(j=1; j<=width-2; j++)
		{
			LBC[i][j] = T(i-1, j)*1 + T(i-1, j+1)*2 + T(i, j+1)*4 + T(i+1, j+1)*8 + T(i+1, j)*16 + T(i+1, j-1)*32 + T(i, j-1)*64 + T(i-1, j-1)*128;
			scalar = CV_RGB(LBC [i][j], LBC [i][j], LBC [i][j]);
			cvSet2D(LBC8Image, i, j, scalar);
		}
	}


	cvNamedWindow("Show originalImage", 1); //new a window and name it
	cvShowImage("Show originalImage", originalImage); //display window*//
	cvNamedWindow("Show LBC4Image", 1); 
	cvShowImage("Show LBC4Image", LBC4Image); //display window*//
	cvSaveImage("LBC4.jpg", LBC4Image);
	cvNamedWindow("Show LBC8Image", 1); //new a window and name it
	cvShowImage("Show LBC8Image", LBC8Image); //display window*/
	cvSaveImage("LBC8.jpg", LBC8Image);
	cvWaitKey(0); //wait for keyboard event

    cvDestroyWindow("Show originalImage"); 
	cvReleaseImage(&originalImage); //release memory
	cvDestroyWindow("Show LBC4Image"); 
	cvReleaseImage(&LBC4Image); //release memory
	cvDestroyWindow("Show LBC8Image"); 
	cvReleaseImage(&LBC8Image); //release memory

}