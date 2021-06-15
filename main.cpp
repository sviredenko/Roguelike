#include "common.h"
#include "Image.h"
#include "Player.h"
#include "stb_image.h"
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <cstring>
#include<unistd.h>
constexpr GLsizei WINDOW_WIDTH = 640, WINDOW_HEIGHT = 640;
MovementDir LastDirection=MovementDir::DOWN;
struct InputState
{
  bool keys[1024]{}; //массив состояний кнопок - нажата/не нажата
  GLfloat lastX = 400, lastY = 300; //исходное положение мыши
  bool firstMouse = true;
  bool captureMouse         = true;  // Мышка захвачена нашим приложением или нет?
  bool capturedMouseJustNow = false;
} static Input;


GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


void OnKeyboardPressed(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		break;
  case GLFW_KEY_1:
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    break;
  case GLFW_KEY_2:
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    break;
	default:
		if (action == GLFW_PRESS)
      Input.keys[key] = true;
		else if (action == GLFW_RELEASE)
      Input.keys[key] = false;
	}
}

MovementDir processPlayerMovement(Player &player,Map &my_map)
{
  if (Input.keys[GLFW_KEY_W]){
    player.ProcessInput(MovementDir::UP,my_map);
    return MovementDir::UP;}
  else if (Input.keys[GLFW_KEY_S]){
    player.ProcessInput(MovementDir::DOWN,my_map);
    return MovementDir::DOWN;}
  if (Input.keys[GLFW_KEY_A]){
    player.ProcessInput(MovementDir::LEFT,my_map);
    return MovementDir::LEFT;}
  else if (Input.keys[GLFW_KEY_D]){
    player.ProcessInput(MovementDir::RIGHT,my_map);
    return MovementDir::RIGHT;}
    
    return LastDirection;
}

void OnMouseButtonClicked(GLFWwindow* window, int button, int action, int mods)
{
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    Input.captureMouse = !Input.captureMouse;

  if (Input.captureMouse)
  {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    Input.capturedMouseJustNow = true;
  }
  else
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

}

void OnMouseMove(GLFWwindow* window, double xpos, double ypos)
{
  if (Input.firstMouse)
  {
    Input.lastX = float(xpos);
    Input.lastY = float(ypos);
    Input.firstMouse = false;
  }

  GLfloat xoffset = float(xpos) - Input.lastX;
  GLfloat yoffset = Input.lastY - float(ypos);

  Input.lastX = float(xpos);
  Input.lastY = float(ypos);
}


void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
  // ...
}


int initGL()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  std::cout << "Controls: "<< std::endl;
  std::cout << "press right mouse button to capture/release mouse cursor  "<< std::endl;
  std::cout << "W, A, S, D - movement  "<< std::endl;
  std::cout << "press ESC to exit" << std::endl;

	return 0;
}

int main(int argc, char** argv)
{
	if(!glfwInit())
    return -1;

//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow*  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window); 

	glfwSetKeyCallback        (window, OnKeyboardPressed);  
	glfwSetCursorPosCallback  (window, OnMouseMove); 
  glfwSetMouseButtonCallback(window, OnMouseButtonClicked);
	glfwSetScrollCallback     (window, OnMouseScroll);

	if(initGL() != 0) 
		return -1;
    
	
    
  
  //Reset any OpenGL errors which could be present for some reason
	GLenum gl_error = glGetError();
	while (gl_error != GL_NO_ERROR)
		gl_error = glGetError();

	
    std::ifstream test("./resources/tex.png");  
  if (!test)
  {
      std::cout << "The file doesn't exist" << std::endl;
  }
	
      //Инициализируем строку тайтлов
    std::string map_path("./resources/map.txt");
   Map my_map(map_path,40);
   /*for(int j=0;j<40;j++){
       for(int i=0;i<40;i++)
            std::cout<<my_map.GetChar(i,j);
        std::cout<<std::endl;
   }*/
    Image hero_down("./resources/hero_down.png");
    Image hero_up("./resources/hero_up.png");
    Image hero_right("./resources/hero_right.png");
    Image hero_left("./resources/hero_left.png");
    Image grass("./resources/grass.png");
    Image wall("./resources/wall.png");
    Image water("./resources/water.png");
    Image stone("./resources/stone.png");
    Image sand("./resources/sand.png");
    Image background_map("./resources/grass.png");
    Image trap("./resources/trap.png");
    Image trap2("./resources/trap2.png");
    Image trap_open("./resources/trap_open.png");
    Image door_close("./resources/door_close.png");
    Image background_table("./resources/table.png");
    Image fire("./resources/fire.png");
    int map_width=1280;
    int map_height=1280;
    Image screenBuffer(background_map,WINDOW_WIDTH, WINDOW_HEIGHT,4);
    Image screenBuffer_map(background_map,map_width, map_height,4);
    Load_tile(screenBuffer_map,stone,my_map,'t');
    Load_tile(screenBuffer_map,wall,my_map,'#');
    Load_tile(screenBuffer_map,water,my_map,'w');
    Load_tile(screenBuffer_map,sand,my_map,'s');
    Load_tile(screenBuffer_map,trap2,my_map,'1');
    Load_tile(screenBuffer_map,trap,my_map,'2');
    Load_tile(screenBuffer_map,door_close,my_map,'x');
    Load_light(screenBuffer_map,my_map);
    Load_tile(screenBuffer_map,fire,my_map,'f');
    
    int lenth_of_table=16*3;
    Image table(background_table,WINDOW_WIDTH,lenth_of_table,4);
    
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);  GL_CHECK_ERRORS;
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); GL_CHECK_ERRORS;
    //Point starting_pos{.x = WINDOW_WIDTH / 2, .y = WINDOW_HEIGHT / 2};
	Player player(my_map);
    MovementDir direction=MovementDir::UP;
  //game loop
    bool check_lvl=true;
    
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
        glfwPollEvents();
    Load_tile(screenBuffer_map,trap_open,my_map,'p');
    Load_tile(screenBuffer_map,trap2,my_map,'1');
    LastDirection=processPlayerMovement(player,my_map);
    switch(LastDirection){
        case MovementDir::UP:
            player.Draw(screenBuffer_map,background_map,hero_up);
            break;
         case MovementDir::DOWN:
            player.Draw(screenBuffer_map,background_map,hero_down);  
            break;
        case MovementDir::LEFT:
            player.Draw(screenBuffer_map,background_map,hero_left);
            break;
        case MovementDir::RIGHT:
            player.Draw(screenBuffer_map,background_map,hero_right);
            break;
       
    }   
        
        screenBuffer.copy_part_of_screen(screenBuffer_map,player.get_x(),player.get_y(),lenth_of_table);
        screenBuffer.add_to_end_screen(table);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;
        glDrawPixels (WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data());GL_CHECK_ERRORS;
		glfwSwapBuffers(window);
        if(player.consequence_dead(my_map)){
            Image dead("./resources/dead.png");
            Load_over(screenBuffer,dead);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;
            glDrawPixels (WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data());GL_CHECK_ERRORS;
            glfwSwapBuffers(window);
            sleep(2);
            break;
        }
        if(player.consequence_exit(my_map)){
            if(check_lvl){
                Image level_up("./resources/level_up.png");
                Load_over(screenBuffer,level_up);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;
                glDrawPixels (WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data());GL_CHECK_ERRORS;
                glfwSwapBuffers(window);
                sleep(2);
            
                my_map.change_map("./resources/map2.txt");
                Load_tile_to_tile(background_map,grass);
                player.change_coord(my_map);
                Load_tile(screenBuffer_map,grass,my_map,'.');
                Load_tile(screenBuffer_map,stone,my_map,'t');
                Load_tile(screenBuffer_map,wall,my_map,'#');
                Load_tile(screenBuffer_map,water,my_map,'w');
                Load_tile(screenBuffer_map,sand,my_map,'s');
                Load_tile(screenBuffer_map,trap2,my_map,'1');
                Load_tile(screenBuffer_map,trap,my_map,'2');
                Load_tile(screenBuffer_map,door_close,my_map,'x');
                Load_tile(screenBuffer_map,fire,my_map,'f');
                check_lvl=false;
            }
            else{
                Image win("./resources/win.png");
                Load_over(screenBuffer,win);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;
                glDrawPixels (WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data());GL_CHECK_ERRORS;
                glfwSwapBuffers(window);
                sleep(2);
                break;
            }

        }
       
	}

	glfwTerminate();
	return 0;
}
