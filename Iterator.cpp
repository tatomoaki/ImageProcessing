#include "Image.h"

Image::Iterator::Iterator(const Iterator& it){
   ptr =it.ptr;
         
}
 Image::Iterator::Iterator(unsigned char *p):ptr(p){
         }
        
  Image::Iterator::~Iterator(){
            ptr = nullptr;
  }
 Image::Iterator::Iterator(Iterator&&it){
            ptr =it.ptr;
            it = nullptr;
            
         }     
Image::Iterator&  Image::Iterator::operator=(const Iterator& it){
               if(this!=&it){
                  ptr  =it.ptr;
               }
               return *this;
         }
Image::Iterator&  Image::Iterator::operator=(Iterator&&it){
             if(this!=&it){
                  ptr  =it.ptr;
               }
               it= nullptr;
               return *this;
         }
         
         Image::Iterator&  Image::Iterator::operator+=(int val){
            ptr += val;
            return *this;
         }
      const  Image::Iterator& Image::Iterator::operator++(){
            ++ptr;
            return *this;
         }
        
const Image::Iterator& Image::Iterator::operator--(){
            ptr--;
            return *this;
}
unsigned char& Image::Iterator::operator*(){
 return *ptr;}
 
 bool  Image::Iterator::operator!=( const Iterator& it){
   return (ptr != it.ptr);
 }
