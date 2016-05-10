#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Image.h"
using namespace std;
int main(int argc, char* argv[]){
	if(argc > 5  || argc < 3){
		cerr << "Exceeded argument bounds" << endl;	
	}else { 
		string image, image_2, outfile;		
		
		if(string(argv[1]).compare("-a") ==  0 ){ //add
				image = argv[2];
				image_2 = argv[3]; 
				outfile = argv[4];
				Image image_obj(image);
				Image image_obj2(image_2);
				Image add_image = image_obj + image_obj2;				
				add_image.writeImage(outfile);						
		}
		else if(string(argv[1]).compare("-s") ==  0){ //difference
				image = argv[2];
				image_2 = argv[3]; 
				outfile = argv[4];
				Image image_obj(image);
				Image image_obj2(image_2);
				Image diff_image = image_obj - image_obj2;				
				diff_image.writeImage(outfile);
				}
	    else if(string(argv[1]).compare("-i") ==  0){ //invert
				image = argv[2];
				outfile = argv[3];
				Image invert(image);
				Image inverted =!invert;
				inverted.writeImage(outfile);
				}
		else if(string(argv[1]).compare("-l") ==  0){ //mask
				image = argv[2];
				image_2 = argv[3]; 
				outfile = argv[4];
				Image image_obj(image);
				Image image_obj2(image_2);
				Image mask_image = image_obj / image_obj2;				
				mask_image.writeImage(outfile);
				
				}
		else if(string(argv[1]).compare("-t") ==  0){ //threshold
				image = argv[2];
				outfile = argv[4];
				int threshold;
				std::istringstream iss(argv[3]);
				iss >> threshold;
				Image obj(image);
				//Image thresh = threshold*obj;
				//thresh.writeImage(oufile);
				}
		else {
				cerr << "Invalid arguments" << endl;
				
				}
			
			
		}
	
	
	
	return 0;
	}
