#include "SDL.h"

void colorInterpolation (SDL_Surface* interpolate, int size) 
{
		Uint8 R ; 
		Uint8 G ; 
		Uint8 B ; 
		Uint8 A ; 
		Uint32 temp, pixel ; 

		float tR, tG, tB ; 
		Uint8 r, g, b; 

		float Y, U, V; 

		Uint32 R32, G32, B32, pixel32; 

		SDL_PixelFormat* fmt = interpolate -> format; 

		int row = 0 ; 

		SDL_LockSurface (interpolate); 
		
		for (int i = 0; i < size; i++)
			{
				pixel = *((Uint32*) interpolate->pixels + i); 

				temp = pixel & fmt -> Amask; 
				temp = temp >> fmt -> Ashift; 
				temp = temp << fmt -> Aloss; 
				A = (Uint8) temp; 

				// First Column (GB Downwards)
				if ( i % interpolate -> w == 0 )	 
				{
					//First pixel (Starts with G) or if 1st pixel of odd rows
					if (i == 0 || row %2 == 0) 
						{
							pixel = *((Uint32*) interpolate->pixels + i);	// Green component its green
							temp = pixel & fmt -> Gmask; 
							temp = temp >> fmt -> Gshift; 
							temp = temp << fmt -> Gloss; 
							G = (Uint8) temp ; 

							pixel = *((Uint32*) interpolate->pixels+ (i + 1));  // Next pixel is red (Nearest Neighbour) 
							temp = pixel & fmt -> Rmask; 
							temp = temp >> fmt -> Rshift; 
							temp = temp << fmt -> Rloss; 
							R = (Uint8) temp ; 

							pixel = *((Uint32*) interpolate -> pixels + (i + 640));	// Closest blue is next row
							temp = pixel & fmt -> Bmask; 
							temp = temp >> fmt -> Bshift; 
							temp = temp << fmt -> Bloss; 
							B = (Uint8) temp; 
						}

					else if ( i == (size - interpolate-> w) || row % 2 == 1 )	// Last row 1st pixel (Starts with b) or 1st pixel of even rows
						{
							pixel = *((Uint32*) interpolate->pixels+ (i + 1));	//Closest green is next 
							temp = pixel & fmt -> Gmask; 
							temp = temp >> fmt -> Gshift; 
							temp = temp << fmt -> Gloss; 
							G = (Uint8) temp ; 

							pixel = *((Uint32*) interpolate->pixels+ (i - 639));  //Closest red is row above
							temp = pixel & fmt -> Rmask; 
							temp = temp >> fmt -> Rshift; 
							temp = temp << fmt -> Rloss; 
							R = (Uint8) temp ; 

							pixel = *((Uint32*) interpolate -> pixels + i);	// Blue is itself
							temp = pixel & fmt -> Bmask; 
							temp = temp >> fmt -> Bshift; 
							temp = temp << fmt -> Bloss; 
							B = (Uint8) temp; 
						}
				}

				// Last column (RG Downwards)
				else if (  (i + 1) % interpolate -> w == 0 )
				{
					if( i == interpolate->w - 1 || row % 2 == 0 )	// 1st row last pixel or all odd rows last pixel 
						{
							pixel = *((Uint32*)interpolate->pixels + (i - 1));
							temp = pixel & fmt -> Gmask;
							temp = temp >> fmt -> Gshift;
							temp = temp << fmt -> Gloss;
							G = (Uint8)temp;
						
							pixel = *((Uint32*)interpolate->pixels + i);
							temp = pixel & fmt -> Rmask;
							temp = temp >> fmt -> Rshift;
							temp = temp << fmt -> Rloss;
							R = (Uint8)temp;

							pixel = *((Uint32*)interpolate->pixels + (i + 639));
							temp = pixel & fmt -> Bmask;
							temp = temp >> fmt -> Bshift;
							temp = temp << fmt -> Bloss;
							B = (Uint8)temp;
						}
					
					// Last pixel and all even rows 
					else if ( i == (size - 1) || row % 2 == 1)
					{
							pixel = *((Uint32*)interpolate->pixels + i);
							temp = pixel & fmt -> Gmask;
							temp = temp >> fmt -> Gshift;
							temp = temp << fmt -> Gloss;
							G = (Uint8)temp;

							// Get Red Component
							pixel = *((Uint32*)interpolate->pixels + (i - 640));
							temp = pixel & fmt -> Rmask;
							temp = temp >> fmt -> Rshift;
							temp = temp << fmt -> Rloss;
							R = (Uint8)temp;

							//	Get Blue Component
							pixel = *((Uint32*)interpolate->pixels + (i - 1));
							temp = pixel & fmt -> Bmask;
							temp = temp >> fmt -> Bshift;
							temp = temp << fmt -> Bloss;
							B = (Uint8)temp;
					}
				}

				//1st row (GR) 
				else if (i > 0 && i < interpolate -> w ) 
				{
					if (i % 2 == 0)  // all odd columns (G)
					{
							pixel = *((Uint32*) interpolate->pixels+i); 
							temp = pixel & fmt -> Gmask; 
							temp = temp >> fmt -> Gshift; 
							temp = temp << fmt -> Gloss; 
							G = (Uint8) temp ; 

							pixel = *((Uint32*) interpolate->pixels+ (i + 1));  
							temp = pixel & fmt -> Rmask; 
							temp = temp >> fmt -> Rshift; 
							temp = temp << fmt -> Rloss; 
							R = (Uint8) temp ; 

							pixel = *((Uint32*) interpolate -> pixels + (i + 640));	
							temp = pixel & fmt -> Bmask; 
							temp = temp >> fmt -> Bshift; 
							temp = temp << fmt -> Bloss; 
							B = (Uint8) temp; 
					}

					else if (i % 2 == 1) // all even columns (R)
					{
							pixel = *((Uint32*) interpolate->pixels+ (i + 1)); 
							temp = pixel & fmt -> Gmask; 
							temp = temp >> fmt -> Gshift; 
							temp = temp << fmt -> Gloss; 
							G = (Uint8) temp ; 

							pixel = *((Uint32*) interpolate->pixels + i);  
							temp = pixel & fmt -> Rmask; 
							temp = temp >> fmt -> Rshift; 
							temp = temp << fmt -> Rloss; 
							R = (Uint8) temp ; 

							pixel = *((Uint32*) interpolate -> pixels + i + 639);	
							temp = pixel & fmt -> Bmask; 
							temp = temp >> fmt -> Bshift; 
							temp = temp << fmt -> Bloss; 
							B = (Uint8) temp; 
					}
				}

				else if (i > (size - interpolate -> w ) && i < (size - 1) ) // last row  (BG)
				{
					if (i % 2 == 0)		// all odd columns (B)
					{
							pixel = *((Uint32*) interpolate->pixels+ (i - 1)); 
							temp = pixel & fmt -> Gmask; 
							temp = temp >> fmt -> Gshift; 
							temp = temp << fmt -> Gloss; 
							G = (Uint8) temp ; 

							pixel = *((Uint32*) interpolate->pixels+ (i - 639));  
							temp = pixel & fmt -> Rmask; 
							temp = temp >> fmt -> Rshift; 
							temp = temp << fmt -> Rloss; 
							R = (Uint8) temp ; 

							pixel = *((Uint32*) interpolate -> pixels + i);	
							temp = pixel & fmt -> Bmask; 
							temp = temp >> fmt -> Bshift; 
							temp = temp << fmt -> Bloss; 
							B = (Uint8) temp; 
					}

					else if ( i % 2 == 1)	// all even columns (G)
					{
							pixel = *((Uint32*)interpolate->pixels + i);
							temp = pixel & fmt -> Gmask;
							temp = temp >> fmt -> Gshift;
							temp = temp << fmt -> Gloss;
							G = (Uint8)temp;

							pixel = *((Uint32*)interpolate->pixels + (i - 640));
							temp = pixel & fmt -> Rmask;
							temp = temp >> fmt -> Rshift;
							temp = temp << fmt -> Rloss;
							R = (Uint8)temp;

							pixel = *((Uint32*)interpolate->pixels + (i - 1));
							temp = pixel & fmt -> Bmask;
							temp = temp >> fmt -> Bshift;
							temp = temp << fmt -> Bloss;
							B = (Uint8)temp;
					}
				}

				else // Non edge
				{
					if (row % 2 == 0) //Odd rows (GR)
					{
						if (i % 2 == 0) // Odd columns (G)
						{
							pixel = *((Uint32*)interpolate->pixels + i);
							temp = pixel & fmt -> Gmask;
							temp = temp >> fmt -> Gshift;
							temp = temp << fmt -> Gloss;
							G = (Uint8)temp;

							// Get Red Component
							pixel = *((Uint32*)interpolate->pixels + (i - 1));
							temp = pixel & fmt -> Rmask;
							temp = temp >> fmt -> Rshift;
							temp = temp << fmt -> Rloss;
							R = (Uint8)temp;

							//	Get Blue Component
							pixel = *((Uint32*)interpolate->pixels + (i - 640));
							temp = pixel & fmt -> Bmask;
							temp = temp >> fmt -> Bshift;
							temp = temp << fmt -> Bloss;
							B = (Uint8)temp;
						}

						else if ( i % 2 == 1) //Even columns (R)
						{
							pixel = *((Uint32*)interpolate->pixels + (i - 1));
							temp = pixel & fmt -> Gmask;
							temp = temp >> fmt -> Gshift;
							temp = temp << fmt -> Gloss;
							G = (Uint8)temp;

							// Get Red Component
							pixel = *((Uint32*)interpolate->pixels + i);
							temp = pixel & fmt -> Rmask;
							temp = temp >> fmt -> Rshift;
							temp = temp << fmt -> Rloss;
							R = (Uint8)temp;

							//	Get Blue Component
							pixel = *((Uint32*)interpolate->pixels + (i - 639));
							temp = pixel & fmt -> Bmask;
							temp = temp >> fmt -> Bshift;
							temp = temp << fmt -> Bloss;
							B = (Uint8)temp;
						}
					}

					else if ( row % 2 == 1) //Even rows (BG)
					{
						if ( i % 2 == 0 ) // Odd columns (B)
						{
							pixel = *((Uint32*)interpolate->pixels + (i - 1));
							temp = pixel & fmt -> Gmask;
							temp = temp >> fmt -> Gshift;
							temp = temp << fmt -> Gloss;
							G = (Uint8)temp;

							// Get Red Component
							pixel = *((Uint32*)interpolate->pixels + (i - 639));
							temp = pixel & fmt -> Rmask;
							temp = temp >> fmt -> Rshift;
							temp = temp << fmt -> Rloss;
							R = (Uint8)temp;

							//	Get Blue Component
							pixel = *((Uint32*)interpolate->pixels + i);
							temp = pixel & fmt -> Bmask;
							temp = temp >> fmt -> Bshift;
							temp = temp << fmt -> Bloss;
							B = (Uint8)temp;
						}

						else if ( i % 2 == 1) //Even columnns (G)
						{
							pixel = *((Uint32*)interpolate->pixels + i);
							temp = pixel & fmt -> Gmask;
							temp = temp >> fmt -> Gshift;
							temp = temp << fmt -> Gloss;
							G = (Uint8)temp;

							// Get Red Component
							pixel = *((Uint32*)interpolate->pixels + (i - 640));
							temp = pixel & fmt -> Rmask;
							temp = temp >> fmt -> Rshift;
							temp = temp << fmt -> Rloss;
							R = (Uint8)temp;

							//	Get Blue Component
							pixel = *((Uint32*)interpolate->pixels + (i - 1));
							temp = pixel & fmt -> Bmask;
							temp = temp >> fmt -> Bshift;
							temp = temp << fmt -> Bloss;
							B = (Uint8)temp;
						}
					}
				}

				if ( ( i + 1 ) % interpolate-> w == 0) 
					row ++; 

				tR = R/255.0; 
				tG = G/255.0; 
				tB = B/255.0;


				Y = (0.299 * tR + 0.587 * tG + 0.114 * tB); 
				U = (-0.14713 * tR - 0.28886 * tG + 0.436 * tB); 
				V = (0.615 * tR  - 0.51499 * tG  - 0.10001 * tB); 


				r = (Y + 1.13983 * V) * 255;
				g = (Y - 0.39465 * U - 0.58060*V) * 255;
				b = (Y + 2.03211 * U) * 255;

				R32 = (Uint32) (r) << fmt -> Rshift; 
				G32 = (Uint32) (g) << fmt -> Gshift; 
				B32 = (Uint32) (b) << fmt -> Bshift; 

				pixel32 = R32 | G32 | B32 | A ; 
				* ( (Uint32 *) interpolate -> pixels + i) = pixel32; 

 
			}

			SDL_UnlockSurface (interpolate); 


}

void colorCorrection (SDL_Surface* correction, int size)
{
		Uint8 R , rP; 
		Uint8 G , gP ; 
		Uint8 B , bP ; 
		Uint8 A ; 
		Uint32 temp, pixel ; 

		float tR, tG, tB ; 
		Uint8 r, g, b; 

		float Y, U, V; 

		Uint32 R32, G32, B32, pixel32; 

		SDL_PixelFormat* fmt = correction -> format; 

		SDL_LockSurface (correction); 

		for (int i = 0; i < size ; i++ )
		{
			pixel = *((Uint32*) correction->pixels + i); 
			temp = pixel & fmt -> Amask; 
			temp = temp >> fmt -> Ashift; 
			temp = temp << fmt -> Aloss; 
			A = (Uint8) temp; 

			pixel = *((Uint32*)correction->pixels + i);
			temp = pixel & fmt -> Gmask;
			temp = temp >> fmt -> Gshift;
			temp = temp << fmt -> Gloss;
			G = (Uint8)temp;

			// Get Red Component
			pixel = *((Uint32*)correction->pixels + i);
			temp = pixel & fmt -> Rmask;
			temp = temp >> fmt -> Rshift;
			temp = temp << fmt -> Rloss;
			R = (Uint8) temp;

			//	Get Blue Component
			pixel = *((Uint32*)correction->pixels + i);
			temp = pixel & fmt -> Bmask;
			temp = temp >> fmt -> Bshift;
			temp = temp << fmt -> Bloss;
			B = (Uint8) temp;

			tR = ((float) R* 1.18 + (float) G * -0.05 + (float) B * -0.13); 
			tG = ((float) R* -0.24 + (float) G * 1.29 + (float) B * -0.05);
			tB = ((float) R* -0.18 + (float) G * -0.44 + (float) B * 1.71);

			/*tR = ((float) R* 1.18 ); 
			tG = ((float) G * 1.29);
			tB = ((float) B * 1.71);*/

			if (tR > 255) 
				tR = 255; 
			else if (tR < 0) 
				tR = 0; 

			if (tG > 255) 
				tG = 255; 
			else if (tG < 0) 
				tG = 0; 

			if (tB > 255) 
				tB = 255; 
			else if (tB < 0) 
				tB = 0; 

			R32 = (Uint32) (tR) << fmt -> Rshift; 
			G32 = (Uint32) (tG) << fmt -> Gshift; 
			B32 = (Uint32) (tB) << fmt -> Bshift; 

			
			pixel32 = R32 | G32 | B32 | A ; 
			* ( (Uint32 *) correction -> pixels + i) = pixel32; 
		}

		SDL_UnlockSurface (correction); 

}

int main (int argc , char* argv []) 
{
	SDL_Surface *screen, *image; 
	SDL_Surface *interpolate, *correction; 
	SDL_Event event; 
	Uint8* keys; 
	int done = 0; 
	int size; 
	
	SDL_Init (SDL_INIT_EVERYTHING); 
	atexit (SDL_Quit); 

	SDL_WM_SetCaption ("ColorChain", "app.ico"); 

	screen = SDL_SetVideoMode (640,480,32, SDL_HWSURFACE);

	if (screen == NULL) 
	{
		printf("\nCant set video mode: %s", SDL_GetError()); 
		exit (1); 
	}

	image = SDL_LoadBMP (argv[1]);

	if ( image == NULL) 
	{
		printf("\nCant load image: %s", SDL_GetError()); 
		exit (1); 
	}

	size = image->w * image ->h; 

	SDL_BlitSurface (image, NULL, screen, NULL); 
	SDL_UpdateRect (screen, 0, 0, screen -> w, screen -> h); 

	interpolate = SDL_DisplayFormat (image); 
	colorInterpolation (interpolate, size); 

	correction = SDL_DisplayFormat (interpolate); 
	colorCorrection (correction, size); 


	while (!done)
	{
		while (SDL_PollEvent (&event))
		{
			if (event.type == SDL_QUIT)
			{
				done = 1; 
				break; 
			}
		}

		keys = SDL_GetKeyState (NULL); 
		
		if (keys [SDLK_q]) 
		{
			done = 1; 
		}

		else if (keys [SDLK_i])		// interpolate
		{
			SDL_BlitSurface (interpolate, NULL, screen, NULL); 
			SDL_UpdateRect (screen, 0, 0, screen -> w, screen -> h); 
			SDL_Flip (screen); 
		}

		else if (keys [SDLK_c])		// correction
		{
			SDL_BlitSurface (correction, NULL, screen, NULL); 
			SDL_UpdateRect (screen, 0, 0, screen -> w, screen -> h); 
			SDL_Flip (screen); 
		}

		else if (keys [SDLK_r])		//raw
		{
			SDL_BlitSurface (image, NULL, screen, NULL); 
			SDL_UpdateRect (screen, 0, 0, screen -> w, screen -> h); 
			SDL_Flip (screen); 
		}

		SDL_Delay (100); 
		
	}	

	

		SDL_FreeSurface (image); 
		SDL_FreeSurface (interpolate); 


		SDL_FreeSurface (screen); 
		SDL_Quit(); 

		return 0; 

}
