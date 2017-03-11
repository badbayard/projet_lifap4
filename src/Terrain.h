#ifndef TERRAIN_H
#define TERRAIN_H

class Terrain {
	
	private:

		unsigned int dim_x;
		unsigned int dim_y;

	public:
	/** @brief Constructeur par défault */
		Terrain();

	/** @brief Constructeur de la classe
	 * @param dimensionX dimension Y : entier */	
		Terrain(unsigned int dimensionX, unsigned int dimensionY);
};


#endif
