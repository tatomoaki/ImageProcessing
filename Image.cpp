#include "Image.h"
#include <string>
#include <sstream>
#include <memory>
#include <iostream>
#include <fstream>
using namespace std;

Image::Image(void) {
}    

Image::Image(string &fileName){
   readImage(fileName);
 }


Image::~Image(){    
   data = nullptr;
   height = width = 0;
}
Image::Image(const Image&img):width(img.width), height(img.height){ 
   unsigned char* buffer  = new unsigned char[img.width*img.height];
   for(int i =0; i< height*width; i++){ 
	buffer[i] =  img.data[i];
 }   
   data.reset(buffer);
}
   
Image::Image(Image&& img): width(img.width), height(img.height){
 unsigned char* buffer  = new unsigned char[img.width*img.height];
   for(int i =0; i< height*width; i++){            
     
      buffer[i] =  img.data[i];
}
data.reset(buffer); 
	img.data = nullptr;
         
   img.height = img.width = 0;
  
}
/**
int Image::getHeight(){
return height;

}
int Image::getWidth(){
return width;

}**/   
Image& Image::operator=(const Image&img){
   if(this == &img)
      return *this; 
   
   if(data != nullptr){
     
      data = nullptr;
      
   }       
   width = img.width;
   height  = img.height;
   unsigned char* buffer = new unsigned char[width*height];
         
   for(int i =0; i< height*width; i++){
            
          
      buffer[i] =  img.data[i]; }
   data.reset(buffer);   
   return *this;
      
}
Image& Image::operator=(Image&& img){

   if(this == &img)
      return *this;    
   
   if(data != nullptr){     
      data = nullptr;
   }

      
   width = img.width;
   height  = img.height;
    unsigned char* buffer = new unsigned char[width*height];
         
   for(int i =0; i < height*width; i++){   
          
      buffer[i] =  img.data[i]; 
       }  
   data.reset(buffer);
   
   img.data = nullptr;
   img.height = img.width = 0;   
   return *this;
}
void Image::readImage(std::string &fileName){
   int  Ncols, Nrows;
 
   ifstream file(fileName , ios::in |ios::binary);
   string line;
   
   if(file.is_open()) {
      getline (file,line);     
      while(line.compare("255")!=0){        
         if(line.at(0)!='#'){ 
             if(line.compare("P5")!=0){               
               istringstream iss(line);
            
               iss >> Nrows;
               iss >> Ncols;
            
               width = Ncols;
               height =  Nrows;
            }            
         }
         getline(file ,line);        
      }     
      data.reset(new unsigned char[width*height]);   
	  skipws(file);    
      
      file.read((char*)&data[0], Nrows*Ncols);     
      file.close();
	}
   else{
      std::cerr<<"Image not opened"<<std::endl;	
     
   } 
   
}
void Image::writeImage(std::string &outfile){
   
   std::ofstream ofs(outfile,ios::out|ios::binary);
   if(ofs.is_open()){
      ofs<<"P5"<<endl;      
      ofs<< height<< " "<< width<<std::endl;
      ofs<<"255"<<std::endl;       
       
      unsigned char byte;
      for(auto it = this->begin();it !=end();++it){        
         byte  = *it;
         ofs.write((char*)&byte,1);
      }
      ofs.close();
   }
   else{
      std::cerr<<"Cannot write Image"<<std::endl;
   }
}
   
Image::Iterator Image::begin(void) const{ 
   return  Iterator(&(data.get()[0]));   
}
Image::Iterator Image::end(void) const{
   return Iterator(&(data.get()[width*height]));
}
   
Image Image::operator+(const Image&img){ 
   if(img.height != height || img.width != width ){
      std::cerr<< "Image dimensions don't match, can't add"<< std::endl;
      return *this;
   }
    Image temp(*this);   
   Image::Iterator beg = temp.begin(), end = temp.end();
   Image::Iterator inStart = img.begin(), inEnd = img.end();

   while ( beg != end) {    
      int add = (*beg + *inStart);
      if(add > 255){
         add= 255;
      }   
	*beg = add; 
   
   ++beg;
   ++inStart;
   }
   return temp;
 }
Image Image::operator-(const Image&img){
   Image temp(*this);
   if(img.height != height || img.width != width ){
      cerr<< "Image dimensions don't match, can't subtract" << std::endl;;
      return *this;
   }   
   Image::Iterator beg = temp.begin(), end = temp.end();
   Image::Iterator inStart = img.begin(), inEnd = img.end();

   while ( beg != end) {    
      int sub = (*beg - *inStart);
      if(sub < 0){
         sub = 0;
      }     
	  *beg = sub; 
      ++beg;
      ++inStart;
   }    
   return temp;

}
Image Image::operator/(const Image&img){
   Image temp(*this);
   if(img.height != height || img.width != width ){
      cerr<< "Image dimensions don't match, can't mask" << std::endl;;
      return *this;
   }   
   Image::Iterator beg = temp.begin(), end = temp.end();
   Image::Iterator inStart = img.begin(), inEnd = img.end();

   while ( beg != end) { 
   
      bool check = (*inStart==255);
      if(!check){
         *beg = 0;
      }
     ++beg;
   ++inStart;
   
   } 

   return temp;
}
Image Image::operator!(){
   Image temp(*this);
  
   Image::Iterator beg = temp.begin(), end = temp.end(); 

   while ( beg != end) { 
   *beg = 255 - *beg;
   ++beg;
   } 

   return temp;
}

Image Image::operator*(int val){
   Image temp(*this);
   Image::Iterator beg = temp.begin(), end = temp.end();
   while ( beg != end) { 
         
      bool check = (*beg>val);
      if(check){         
         *beg = 255 ;
      }
      else{            
         *beg = 0 ;     
      }      
      ++beg;   
   } 
   return temp;  
}
ostream& operator<<(ostream&ofs, const Image&img){
   if(ofs){      
      unsigned char byte;
      for(auto i=img.begin();i!=img.end();++i){
      
         byte  = *i;
         ofs.write((char*)&byte,1);
      } 
      return ofs;
   }
   else{
      std::cerr<<"Image cannot be open"<<std::endl;
   }
   return ofs; 
}
istream& operator>>( istream& file,  Image&img){
    string line;
    int Nrows,Ncols;
   
   if(file) {
      getline (file,line);   
  
      while(line.compare("255")!=0){
        
         if(line.at(0)!='#'){    
            
            if(line.compare("P5")!=0){               
               istringstream iss(line);            
               iss >> Nrows;
               iss >> Ncols;
            
               img.width = Ncols;
               img.height =  Nrows;
            }
            
         }
         getline(file ,line);
      }
      img.data.reset(new unsigned char[img.width*img.height]);   
     skipws(file);
    file.read((char*)(&(img.data[0])), Nrows*Ncols); 
    //file.close();       
      return file;}
   else{
      std::cerr<<"Image cannot be read"<<std::endl;	
      return file;	
   }
   }

bool Image::operator==(const Image& img) {
   if(sizeof(img.data.get())!= sizeof(data.get()))
      return false;
   unsigned int i;  
   for(i = 0; i< sizeof(data.get()); i++){
      if(data[i]!= img.data[i])
         return false;
    }
   return true;
}
   

