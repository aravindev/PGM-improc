/*
This header file has been created by
Name : Aravind E Vijayan
       B110487EC
       National Institute of Technology Calicut
*/

#include "pgm.hpp"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
using namespace std;

/*----------------------------------------------------------------------------------------------------------------------------------------*/
table pgm_imread(char *argv)			//reads pgm image
	{
	char line[80];
	int imagetype = 0, cols, rows, maxintensity, p2read;
	int **data;
	unsigned char p5read;
	stringstream buffer;
	ifstream infile(argv);			//opens image
	if (infile == NULL)
    		{
	        cerr<<argv[1]<<" either cannot be read or does not exist\n";
        	exit(0);
	        }
	infile.getline(line, 80);
	if(line[0] == 'P')
		switch(line[1])
			{
			case '5' :	imagetype = 1; cout<<"P5 PGM image detected\n"; 		break; //raw image
			case '2' :	imagetype = 2; cout<<"P2 PGM image detected\n"; 		break; //ASCII image
			default	 :	imagetype = 0; cerr<<"unsupported PGM image format\n"; exit(0); break;
			}
	else
		{
		cerr<<"Invalid image format\n";
		exit(0);
		}
	while (infile.peek()=='#')
        	infile.getline(line,80); 	//read all the comments and oomit them.
	infile >> cols >> rows >> maxintensity;	//read the no of coloumns rows and pixel intensity
	data = new int* [cols];		//memory allocation
	if (!data)
		{
      	     cout << "allocation failure in matrix";
	     exit(1);
    		}
	for(int i = 0; i<cols;i++)
		{
		data[i] = new int[rows];	//making allocation for 2d matrix
	        if (!data[i])
			{
	       		cout << "allocation failure in matrix";
	       		exit(1);
      			}
		}
	if(imagetype == 1)			//raw image mode
		for (int i=0;i<cols;i++)
        	{
        	 for (int j=0;j<rows;j++)
			{
         	        infile>>p5read;
			data[i][j] = (int)p5read;
			}
	        }
	else if(imagetype == 2)			//ASCII image mode
		{
		buffer << infile.rdbuf();
		for (int i=0;i<cols;i++)
       			{
       			 for (int j=0;j<rows;j++)
				{
       			        buffer>>p2read;
				data[i][j] = p2read;
				}
       			 }
		}
	table image = {data, cols, rows};
	cout<<"Image read complete\n";
	infile.close();
    	return image; 		 		//returns the image as a 2-D array in a structure
}


/*----------------------------------------------------------------------------------------------------------------------------------------*/
double *pgm_hist_calc(table image)		//calculates the histogram of the image and returns it as a 1-D matrix
	{
	double *histo;
	histo = new double[256];
	for(int i = 0; i<256; i++)
		*(histo+i) = 0;
	for(int i = 0; i<image.cols; i++)
		for(int j = 0; j<image.rows; j++)
			histo[(image.data[i][j])]++;
	cout<<"Histogram calculation complete\n";
	return histo;
	}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
double pgm_hist_maxval(double *hist, table image)		//calculates and returns the maximum value in the histogram 
	{
	double maxim = 0;
	for(int i = 0; i<255; i++)
	{
		if(*(hist+i) > maxim)
			maxim = *(hist+i);
	}
	cout<<"Histogram maximum value calculated :"<<maxim<<"\n";
	return maxim;
	}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
void pgm_hist_save(char *argv, double *hist, double maxim, int cols = 1024)	//saves the histogram into an image
	{
	ofstream outfile(argv);
	int no_of_pixels = cols*cols;
	if (outfile == NULL)
    		{
	        cerr<<argv[1]<<" either cannot be read or does not exist\n";
        	exit(0);
	        }
	outfile<<"P2\n"<<"#Aravind's Histogram image\n"<<cols<<" "<<cols<<" "<<"1\n";
	for(int i = 0; i<no_of_pixels;i++)
    {
    int y = i%cols;
    int r = cols - (i/cols);
    if(r < ((hist[y/(cols/256)]/maxim)*cols))
        outfile<<"0 ";
    else
        outfile<<"1 ";
    }
	outfile.close();
	}
