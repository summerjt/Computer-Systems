#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include "Filter.h"

using namespace std;

#include "rdtsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
    delete input;
    delete output;
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

struct Filter *
readFilter(string filename)
{
  ifstream input(filename.c_str());

  if ( ! input.bad() ) {
    int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
    for (int i=0; i < size; i++) {
      for (int j=0; j < size; j++) {
        int value;
        input >> value;
        filter -> set(i,j,value);
      }
    }
    return filter;
  } else {
    cerr << "Bad input in readFilter:" << filename << endl;
    exit(-1);
  }
}


double
applyFilter(struct Filter *filter, cs1300bmp *input, cs1300bmp *output)
{

  long long cycStart, cycStop;

  cycStart = rdtscll();
  
  
  //outer 3 loops
  int col, row;
  int width=input -> width;
  int height=input -> height;
  int colWsub1=width - 1;
  int rowHsub1=height - 1;
  output -> width = width;
  output -> height = height;
  //inner 2 loops
  short j, i;
  short divisor = filter -> divisor;
  int dim=filter->dim;
    //CopyFilterArray
  short filterCopy[9];
  for(j=0; j<3; j++){
      for(i=0;i<3; i++){
          filterCopy[i*dim+j]=filter->data[i*dim+j];
      }
  }
  int SumColor, SumColor1, SumColor2;
  for(col = 1; col < colWsub1; col++) {
    for(row = 1; row < rowHsub1 ; row++) {
        SumColor=0;
        SumColor1=0;
        SumColor2=0;
        //output -> color[0][row][col] = 0;
        for (j = 0; j < 3; j++) {
            for(i=0;i<3;i++){
                SumColor+= input -> color[0][row+i-1][col+j-1]*filterCopy[i*dim+j];
                SumColor1+= input -> color[1][row+i-1][col+j-1]*filterCopy[i*dim+j];
                SumColor2+= input -> color[2][row+i-1][col+j-1]*filterCopy[i*dim+j];
            }
        }
        if (divisor!=1){
            SumColor /= divisor;
            SumColor1 /= divisor;
            SumColor2 /= divisor;
        }
        if (SumColor < 0) {
          output -> color[0][row][col] = 0;
        }
        else if ( SumColor > 255 ) { 
          output -> color[0][row][col] = 255;
        }
        else{
            output -> color[0][row][col] = SumColor;
        }
        if (SumColor1 < 0) {
          output -> color[1][row][col] = 0;
        }
        else if ( SumColor1 > 255 ) { 
          output -> color[1][row][col] = 255;
        }
        else{
            output -> color[1][row][col] = SumColor1;
        }
        if (SumColor2 < 0) {
          output -> color[2][row][col] = 0;
        }
        else if ( SumColor2 > 255 ) { 
          output -> color[2][row][col] = 255;
        }
        else{
            output -> color[2][row][col] = SumColor2;
        }
        
      
    }
  }

  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}
