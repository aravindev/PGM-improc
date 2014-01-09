/*
This file has been created by
Name : Aravind E Vijayan
       B110487EC
       National Institute of Technology Calicut
*/
#include "pgm.cpp"
using namespace std;
int main(int argc, char *argv[])
	{
if (argc < 3)
    {
        cerr<<"Usage: readimage input-file-name output-file-name\n";
        exit(0);
    }
	struct table image = pgm_imread(argv[1]);
	double *hists = pgm_hist_calc(image);
	double maxim = pgm_hist_maxval(hists, image);
	pgm_hist_save(argv[2], hists, maxim, 1024
);
}
