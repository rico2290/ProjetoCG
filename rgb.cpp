#include "rgb.h"

RGB::RGB()
{
 this->R=0;this->G=0;this->B=0;
}
RGB::RGB(float r, float g, float b){
    this->R=r;
    this->G=g;
    this->B=b;
}

void RGB::Normalize(){
      if(this->R>1)
          this->R=1;
      if(this->G>1)
          this->G=1;
      if(this->B>1)
          this->B=1;
}



