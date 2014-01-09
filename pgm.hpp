/*
This header file has been created by
Name : Aravind E Vijayan
       B110487EC
       National Institute of Technology Calicut
*/
#ifndef PGM_HPP
#define PGM_HPP

struct table	//image structure
	{
	int **data;
	int cols;
	int rows;
	};
/*
function to read pgm image
Usage :
	parameter must be the path of image passed from terminal
	the function returns the image as a 2-D matrix along with size informations
*/
table pgm_imread(char *); 
/*
function to calculate the histogram
usage :
	parameter is the image structure
	it returns a 256 element structure containing the histogram information
*/
double *pgm_hist_calc(table);
/*
function to find the maximum value in the histogram
usage	:
	The maximum value of the histogram is returned. This can be used to resize the histogram image
	the histogram array must be passed along with the image structure
*/	
double pgm_hist_maxval(double*, table);
/*
function to save the histogram as an image
usage :
	This function can be used to save the histogram file as a PGM image.
	The second image name passed through the terminal, histogram array and the maximum value of histogram must be passed
	The last parameter is the size of the histogram image. Default value if 1024
*/
void pgm_hist_save(char *,double *, double, int);
#endif
