#ifndef TERRAIN_H
#define TERRAIN_H

using namespace std;

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
	/** @brief destructeur de la classe */
		~Terrain();

	/** @brief récupére la taille dim_x */
		unsigned int getdim_x() const;

	/** @brief modifie dim_x
	 *  @param dimensionX : entier */
		void setdim_x(unsigned int dimensionX);

		/** @brief récupére la taille dim_y */
		unsigned int getdim_y() const;

		/** @brief modifie dim_y
		 *  @param dimensionY : entier */
		void setdim_y(unsigned int dimensionY);
};


#endif
