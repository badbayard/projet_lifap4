#include "Terrain.h"

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <cassert>

using namespace std;

Terrain::Terrain()
{
	dim_x = 0;
 	dim_y = 0;
}

Terrain::Terrain(unsigned int dimensionX, unsigned int dimensionY)
{
	dim_x = dimensionX;
 	dim_y = dimensionY;
	unsigned int i, j;


	for(i=0;i<=dim_x;i++)
	{
		for(j=0;j<=dim_y;j++)
		{
			cout <<"*";
		}
		cout <<endl;
	}
}

Terrain::~Terrain()
{
	dim_x= 0;
	dim_y= 0;
}

unsigned int Terrain::getdim_x() const
{
	return dim_x;
}

void Terrain::setdim_x(unsigned int dimensionX)
{
	assert(dimensionX >= 0);
	dim_x = dimensionX;
}

unsigned int Terrain::getdim_y() const
{
	return dim_y;
}

void Terrain::setdim_y(unsigned int dimensionY)
{
	assert(dimensionY >= 0);
	dim_y = dimensionY;
}	


