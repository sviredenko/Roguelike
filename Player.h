#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H
#include<string>
#include<vector>
#include "Image.h"
#include <iostream>
#include <fstream>
#include<cmath>
#include <cstdlib>


struct Point
{
  int x;
  int y;
};

enum class MovementDir
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};
struct Map{
public:
    explicit Map(const std::string &a_path,int n );
    char GetChar(int x,int y);
    void PutChar(int x,int y,char c);
    bool avaible(int x,int y);
    void interact(int x_old,int y_old,int x,int y,MovementDir dir);
    void change_map(const std::string & a_path);
private:
    std::vector<std::string>map;
    int n;
};
struct Player
{
    explicit Player(Point pos = {.x = 10, .y = 10}) :
                 coords(pos), old_coords(coords) {};
    Player(Map my_map);
    bool Moved() const;
    void ProcessInput(MovementDir dir,Map &my_map);
    void Draw(Image &screen,Image &background_map,Image &hero);
    
    bool consequence_dead(Map my_map);
    bool consequence_exit(Map my_map);
    int get_x();
    int get_y();
    void change_coord(Map my_map);
private:
  Point coords {.x = 10, .y = 10};
  Point old_coords {.x = 10, .y = 10};
  Point prev_coords{.x=10,.y=10};
  Pixel color {.r = 255, .g = 255, .b = 0, .a = 255};
  
  int move_speed = 4;
   // Image hero;
    //Image background_map;
};
void Load_over(Image& screen,Image& img);
void Load_tile(Image& screen,Image& type_tyle,Map &my_map,char s);
void Load_tile_to_tile(Image& first_tile,Image&second_tile);
void Load_light(Image & screen,Map & my_map);
#endif //MAIN_PLAYER_H
