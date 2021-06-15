#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
void Image::add_to_end_screen(Image& table ){
    int height2=Height()-table.Height();
    for(int i=0;i<table.Width();i++)
        for(int j=0;j<table.Height();j++)
            PutPixel(i,height2+j,table.GetPixel(i,j));
    
 return;   
}
Pixel bright(Pixel x)
{
    Pixel buf;
    buf.r= ceil(x.r*1.25)>255?   255:ceil(x.r*1.25);
    buf.g=ceil(x.g*1.25)>255?  255:ceil(x.g*1.25);
    buf.b=ceil(x.b*1.25)>255?  255:ceil(x.b*1.25);
    buf.a=x.a;
    return buf;
}
void Image::copy_part_of_screen(Image& main_screen,int x_hero,int y_hero,int lenth_of_table){
    int w1,w2,h1,h2;
    height=height-lenth_of_table;
     if(x_hero-width/2<0){
        w1=0;
        w2=width;
     }
    else if(x_hero+width/2>main_screen.Width()){
        w2=main_screen.Width();
        w1=main_screen.Width()-width;
    }
    else{
        w1=x_hero-width/2;
        w2=x_hero+width/2;
    }
    if(y_hero-height/2<0){
        h1=0;
        h2=height;
     }
    else if(y_hero+height/2>main_screen.Height()){
        h2=main_screen.Height();
        h1=main_screen.Height()-height;
    }   
    else{
        h1=y_hero-height/2;
        h2=y_hero+height/2;
    }
    //определили окнно которое нудно скопировать относительно точки нашего нахождения 
    for(int j=0;j<height;j++)
        for( int i=0;i<width;i++)
            PutPixel(i,j,main_screen.GetPixel(w1+i,h1+j));
    height=height+lenth_of_table; 
}
Image::Image(const std::string &a_path)
{
  if((data = (Pixel*)stbi_load(a_path.c_str(), &width, &height, &channels, 0)) != nullptr)
  {
    size = width * height * channels;
  }
}
Image::Image(Image& img,int a_width, int a_height,int a_channels){
    data=new Pixel[a_width*a_height]{};
    int n=img.Width(),m=img.Height();
    if(data!=nullptr){
        width = a_width;
        height = a_height;
        size = a_width * a_height * a_channels;
        channels = a_channels;
        self_allocated = true;
        for (int j=0;j<a_height;j++)
            for(int i=0;i<a_width;i++){
                    Pixel buf=img.GetPixel(i%n,j%m);
                    data[j*a_width+i]=buf;
            }
    }

}
    
Image::Image(int a_width, int a_height, int a_channels)
{
  data = new Pixel[a_width * a_height ]{};

  if(data != nullptr)
  {
    width = a_width;
    height = a_height;
    size = a_width * a_height * a_channels;
    channels = a_channels;
    self_allocated = true;
  }
}


int Image::Save(const std::string &a_path)
{
  auto extPos = a_path.find_last_of('.');
  if(a_path.substr(extPos, std::string::npos) == ".png" || a_path.substr(extPos, std::string::npos) == ".PNG")
  {
    stbi_write_png(a_path.c_str(), width, height, channels, data, width * channels);
  }
  else if(a_path.substr(extPos, std::string::npos) == ".jpg" || a_path.substr(extPos, std::string::npos) == ".JPG" ||
          a_path.substr(extPos, std::string::npos) == ".jpeg" || a_path.substr(extPos, std::string::npos) == ".JPEG")
  {
    stbi_write_jpg(a_path.c_str(), width, height, channels, data, 100);
  }
  else
  {
    std::cerr << "Unknown file extension: " << a_path.substr(extPos, std::string::npos) << "in file name" << a_path << "\n";
    return 1;
  }

  return 0;
}

Image::~Image()
{
  if(self_allocated)
    delete [] data;
  else
  {
    stbi_image_free(data);
  }
}
