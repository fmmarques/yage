
#include <arkanoid.h>


int main( int argc, 
	  char *argv[] )
{
  arkanoid *game = arkanoid::instance(); 
  game->run();
}
