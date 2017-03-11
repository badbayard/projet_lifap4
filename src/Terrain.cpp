#include "Terrain.h"

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <cassert>


Terrain::Terrain()
{
	dim_x = 0;
 	dim_y = 0;
}

Terrain::Terrain(unsigned int dimensionX, unsigned int dimensionY)
{
	dim_x = dimensionX;
 	dim_y = dimensionY;
}	
