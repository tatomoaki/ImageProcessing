#ifndef IMAGE_H
#define IMAGE_H
#include <memory>
#include <string>
#include <iostream>

using namespace std;

class Image{
   private:
      int width, height;
      unique_ptr<unsigned char[]> data;
 
   public:
	  Image(void);
	  ~Image();
	  Image operator+(const Image&);
      Image operator-(const Image&);
      Image operator/(const Image&);
      Image operator!();
      Image operator*(int);
      friend ostream& operator<<(ostream&,const Image&);     
      friend istream& operator>>( istream&,Image&);      
      bool operator==(const Image&);
	 
      Image(int, int, unsigned char*); 
      Image(string&);   
	  Image(const Image&);   
      Image(Image&&);    
   
      Image& operator=(const Image&);    
      Image& operator=(Image&&); 
     /**
	  int Image getHeight(void);
	  int Image getWidth(void);**/
      void readImage(std::string&);
      void writeImage(std::string&);
      
  class Iterator{
      private:
        unsigned char *ptr;   
		friend class Image;
		Iterator(unsigned char *p);
      
      public:       
         Iterator(const Iterator&);    
         ~Iterator();      
         Iterator(Iterator&&);       
         Iterator& operator=(const Iterator&);         
      
         Iterator& operator=(Iterator&&);
         const Iterator& operator ++();
         const Iterator& operator --();
         unsigned char& operator *();
         bool operator !=( const Iterator&);
         Iterator&  operator+=(int);
       
      };   
      Image::Iterator begin(void) const;
      Image::Iterator end(void) const;
    
 };
     
     
#endif
