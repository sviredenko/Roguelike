#include "Player.h"




Map::Map(const std::string &a_path,int k ){
    n=k;
    std::ifstream in(a_path);
    for(int i=0;i<n;i++){
        std::string line;
        in>>line;
        map.push_back(line);
    }
    in.close();
}
void Map::change_map(const std::string & a_path){
    std::ifstream in(a_path);
    map.clear();
    for(int i=0;i<n;i++){
            std::string line;
            in>>line;
            map.push_back(line);
    }
    in.close();
    
}
char Map::GetChar(int x, int y){
    return map[n-y-1][x];
}
void Map::PutChar(int x,int y,char c){
    map[n-y-1][x]=c;
}
bool Map::avaible(int x,int y){
    return GetChar(x,y)!='#' && GetChar(x,y)!='t';
}
void Map::interact(int x_old,int y_old,int x,int y,MovementDir dir){
    //std::cout<<"fff"<<std::endl;
    switch(dir){
    
        
    case MovementDir::UP:
       if(floor(float(y_old)/tileSize)!=floor(float(y)/tileSize)){
            char  buf=GetChar(floor(float(x_old)/tileSize),floor(float(y_old)/tileSize));
            char    buf2=GetChar(ceil(float(x_old)/tileSize),floor(float(y_old)/tileSize));
             if(buf=='1'){ 
                    PutChar(floor(float(x_old)/tileSize),floor(float(y_old)/tileSize),'p');
                    
             }        
            
               if(buf=='2')
                    PutChar(floor(float(x_old)/tileSize),floor(float(y_old)/tileSize),'1');
               if(buf2=='1')    
                    PutChar(ceil(float(x_old)/tileSize),floor(float(y_old)/tileSize),'p');
               if(buf2=='2')
                    PutChar(ceil(float(x_old)/tileSize),floor(float(y_old)/tileSize),'1');
       }
    break;
    case MovementDir::DOWN:
        if(ceil(float(y_old)/tileSize)!=ceil(float(y)/tileSize)){
            char  buf=GetChar(floor(float(x_old)/tileSize),ceil(float(y_old)/tileSize));
            char    buf2=GetChar(ceil(float(x_old)/tileSize),ceil(float(y_old)/tileSize));
             if(buf=='1')    
                    PutChar(floor(float(x_old)/tileSize),ceil(float(y_old)/tileSize),'p');
               if(buf=='2')
                    PutChar(floor(float(x_old)/tileSize),ceil(float(y_old)/tileSize),'1');
               if(buf2=='1')    
                    PutChar(ceil(float(x_old)/tileSize),ceil(float(y_old)/tileSize),'p');
               if(buf2=='2')
                    PutChar(ceil(float(x_old)/tileSize),ceil(float(y_old)/tileSize),'1');
       }
            
    break;
    case MovementDir::LEFT:
        if(ceil(float(x_old)/tileSize)!=ceil(float(x)/tileSize)){
            char  buf=GetChar(ceil(float(x_old)/tileSize),ceil(float(y_old)/tileSize));
            char    buf2=GetChar(ceil(float(x_old)/tileSize),floor(float(y_old)/tileSize));
             if(buf=='1')    
                    PutChar(ceil(float(x_old)/tileSize),ceil(float(y_old)/tileSize),'p');
               if(buf=='2')
                    PutChar(ceil(float(x_old)/tileSize),ceil(float(y_old)/tileSize),'1');
               if(buf2=='1')    
                    PutChar(ceil(float(x_old)/tileSize),floor(float(y_old)/tileSize),'p');
               if(buf2=='2')
                    PutChar(ceil(float(x_old)/tileSize),floor(float(y_old)/tileSize),'1');
       }
    break;
    case MovementDir::RIGHT:
        if(floor(float(x_old)/tileSize)!=floor(float(x)/tileSize)){
            char  buf=GetChar(floor(float(x_old)/tileSize),ceil(float(y_old)/tileSize));
            char    buf2=GetChar(floor(float(x_old)/tileSize),floor(float(y_old)/tileSize));
             if(buf=='1')    
                    PutChar(floor(float(x_old)/tileSize),ceil(float(y_old)/tileSize),'p');
               if(buf=='2')
                    PutChar(floor(float(x_old)/tileSize),ceil(float(y_old)/tileSize),buf--);
               if(buf2=='1')    
                    PutChar(floor(float(x_old)/tileSize),floor(float(y_old)/tileSize),'p');
               if(buf2=='2')
                    PutChar(floor(float(x_old)/tileSize),floor(float(y_old)/tileSize),'1');
       }
    break;
        
        
    }
    
    
}
void Load_over(Image& screen,Image& img){
                for(int k=0;k<screen.Width();k++)
                    for(int l=0;l<screen.Height();l++){
                        Pixel buf=img.GetPixel(k,l);
                        if(buf.r!=0 || buf.g!=0 || buf.b!=0)
                            screen.PutPixel(k,l,img.GetPixel(k,l));
                    
                    }
            
}
void Load_light(Image& screen,Map & my_map){

    for(int i=0;i<40;i++)
        for(int j=0;j<40;j++)
            if(my_map.GetChar(i,j)=='f'){
                for(int k=0;k<tileSize;k++)
                    for(int l=0;l<tileSize;l++){
                        screen.PutPixel(i*tileSize+k,(j-1)*tileSize+l,bright(screen.GetPixel(i*tileSize+k,(j-1)*tileSize+l)));
                        screen.PutPixel(i*tileSize+k,(j+1)*tileSize+l,bright(screen.GetPixel(i*tileSize+k,(j+1)*tileSize+l)));
                        screen.PutPixel((i-1)*tileSize+k,j*tileSize+l,bright(screen.GetPixel((i-1)*tileSize+k,j*tileSize+l)));
                        screen.PutPixel((i+1)*tileSize+k,j*tileSize+l,bright(screen.GetPixel((i+1)*tileSize+k,j*tileSize+l)));
                        screen.PutPixel((i+1)*tileSize+k,(j+1)*tileSize+l,bright(screen.GetPixel((i+1)*tileSize+k,(j+1)*tileSize+l)));
                        
                       
                        screen.PutPixel((i-1)*tileSize+k,(j+1)*tileSize+l,bright(screen.GetPixel((i-1)*tileSize+k,(j+1)*tileSize+l)));
                        
                        
                        screen.PutPixel((i-1)*tileSize+k,(j-1)*tileSize+l,bright(screen.GetPixel((i-1)*tileSize+k,(j-1)*tileSize+l)));
                        
                        
                        screen.PutPixel((i+1)*tileSize+k,(j-1)*tileSize+l,bright(screen.GetPixel((i+1)*tileSize+k,(j-1)*tileSize+l)));
                        
                        
                        screen.PutPixel((i)*tileSize+k,(j)*tileSize+l,bright(screen.GetPixel((i)*tileSize+k,(j)*tileSize+l)));
                        
                    }
                
    
            }
}

void Load_tile(Image& screen,Image& type_tyle,Map& my_map,char s){
    for(int j=0;j<40;j++)
        for(int i=0;i<40;i++)
            if(my_map.GetChar(i,j)==s){
                for(int k=0;k<tileSize;k++)
                    for(int l=0;l<tileSize;l++){
                        Pixel buf=type_tyle.GetPixel(k,l);
                        if(buf.r!=0 || buf.g!=0 || buf.b!=0)
                            screen.PutPixel(i*tileSize+k,j*tileSize+l,type_tyle.GetPixel(k,l));
                    }
                
            }
}
void Load_tile_to_tile(Image& first_tile,Image&second_tile){
    if (first_tile.Width()!= second_tile.Width() || first_tile.Height()!= second_tile.Height()){
        return;
    }
    else{
        int width=first_tile.Width();
        int height=first_tile.Height();
        for(int i=0;i<width;i++)
            for(int j=0;j<height;j++)
                first_tile.PutPixel(i,j,second_tile.GetPixel(i,j));
    }
}
int Player::get_x(){return coords.x;}
int Player::get_y(){return coords.y;}
Player::Player(Map my_map){
    coords.x=10;
    coords.y=10;
    old_coords.x=10;
    old_coords.y=10;
    for(int j=0;j<40;j++)
        for(int i=0;i<40;i++)
            if(my_map.GetChar(i,j)=='@'){
                coords.x=i*tileSize;
                coords.y=j*tileSize;
                old_coords.x=i*tileSize;
                old_coords.y=j*tileSize;
            }
}
 void Player::change_coord(Map my_map)
 {
    coords.x=10;
    coords.y=10;
    old_coords.x=10;
    old_coords.y=10;
    for(int j=0;j<40;j++)
        for(int i=0;i<40;i++)
            if(my_map.GetChar(i,j)=='@'){
                coords.x=i*tileSize;
                coords.y=j*tileSize;
                old_coords.x=i*tileSize;
                old_coords.y=j*tileSize;
            }
     
     
   return;  
 }

bool Player::Moved() const
{
  if(coords.x == old_coords.x && coords.y == old_coords.y)
    return false;
  else
    return true;
}
//bool Player::able_Moved(const char* map) const;
//bool Player:: последствия 
    
 bool Player::consequence_dead(Map my_map) {
     if(my_map.GetChar(floor(coords.x/tileSize),floor(coords.y/tileSize))=='p' || my_map.GetChar(floor(coords.x/tileSize),floor(coords.y/tileSize))=='w')
        return true;
     return false;
 }
 bool Player::consequence_exit(Map my_map) {
     if(my_map.GetChar(floor(coords.x/tileSize),floor(coords.y/tileSize))=='x' )
        return true;
     return false;
 }

void Player::ProcessInput(MovementDir dir,Map &my_map)
{
  int move_dist = move_speed * 1;
  switch(dir)
  {
    case MovementDir::UP:
        if(my_map.avaible( floor(float(coords.x)/tileSize),ceil(float(coords.y+move_dist)/tileSize)) && my_map.avaible( ceil(float(coords.x)/tileSize),ceil(float(coords.y+move_dist)/tileSize))){
            old_coords.y = coords.y;
            prev_coords.y=coords.y;
            coords.y += move_dist;
            my_map.interact(prev_coords.x,prev_coords.y,coords.x,coords.y,MovementDir::UP);
        }
      break;
    case MovementDir::DOWN:
        if(my_map.avaible( floor(float(coords.x)/tileSize),floor(float(coords.y-move_dist)/tileSize))&& my_map.avaible( ceil(float(coords.x)/tileSize),floor(float(coords.y-move_dist)/tileSize) )){
            old_coords.y = coords.y;
            prev_coords.y=coords.y;
            coords.y -= move_dist;
            my_map.interact(prev_coords.x,prev_coords.y,coords.x,coords.y,MovementDir::DOWN);
        }
      break;
    case MovementDir::LEFT:
        if(my_map.avaible(floor(float(coords.x-move_dist)/tileSize),ceil(float(coords.y)/tileSize))&& my_map.avaible(floor(float(coords.x-move_dist)/tileSize),floor(float(coords.y)/tileSize))){
            old_coords.x = coords.x;
            prev_coords.x=coords.x;
            coords.x -= move_dist;
            my_map.interact(prev_coords.x,prev_coords.y,coords.x,coords.y,MovementDir::LEFT);
        }
      break;
    case MovementDir::RIGHT:
        if(my_map.avaible(ceil(float(coords.x+move_dist)/tileSize),ceil(float(coords.y)/tileSize))&& my_map.avaible(ceil(float(coords.x+move_dist)/tileSize),floor(float(coords.y)/tileSize))){
            old_coords.x = coords.x;
            prev_coords.x=coords.x;
            coords.x += move_dist;
            my_map.interact(prev_coords.x,prev_coords.y,coords.x,coords.y,MovementDir::RIGHT);
        }
      break;
    default:
      break;
  }
}

void Player::Draw(Image &screen,Image &background_map,Image &hero)
{
  if(Moved())
  {
    for(int y = 0; y < tileSize; ++y)
    {
      for(int x = 0; x <tileSize; ++x)
      {
        screen.PutPixel(old_coords.x+x, old_coords.y+y, background_map.GetPixel(x,y));
         
      }
    }
    old_coords = coords;
    for(int y = 0; y <  tileSize; ++y)
    {
        for(int x = 0; x < tileSize; ++x)
        {
        
            background_map.PutPixel(x,y,screen.GetPixel(x+coords.x,y+coords.y));
        }
    }
  }

  for(int y = 0; y < tileSize; ++y)
  {
    for(int x = 0; x < tileSize; ++x)
    {
        Pixel buf=hero.GetPixel(x,y);
        if(buf.r!=0 || buf.g!=0 || buf.b!=0)
            screen.PutPixel(x+coords.x, y+coords.y, buf);
    }
  }
}
