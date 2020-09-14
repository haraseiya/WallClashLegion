#include <SDL/SDL.h>
#include <GLEW/include/GL/glew.h>
#include <iostream>
#include<string>
#include "Game.h"

int main(int argc,char** argv)
{
	if (!GAMEINSTANCE.Initialize(1280, 768, false)) return -1;

	GAMEINSTANCE.Run();
	GAMEINSTANCE.ShutDown();

	return 0;
}