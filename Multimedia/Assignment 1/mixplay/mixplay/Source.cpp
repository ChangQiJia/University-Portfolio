#include <SDL_config.h>

#include <stdio.h>
#include <stdlib.h>

#if HAVE_SIGNAL_H
#include <signal.h>
#endif

#include <SDL.h>
#include <SDL_audio.h>
#undef main

static const int SCR_WIDTH = 240;
static const int SCR_HEIGHT = 180;
float volume = -1; 
int counter = 0; 
bool loop = true; 

struct {
	SDL_AudioSpec spec;
	Uint8   *sound;			/* Pointer to wave data */
	Uint32   soundlen;		/* Length of wave data */
	int      soundpos;		/* Current play position */

} wave,track2, temp;


static int done = 0;

void poked(int sig)
{
	done = 1;
}

//Print the info of both track
void printInfo () 
{
	printf("\n===============================");
	printf("\nTrack 1"); 
	printf("\nNumber of Channels: " ); 
	if (wave.spec.channels == 1) 
		{
			printf ("1"); 
		}
	else
		{
			printf ("2");		//since there is only mono and stereo
		}
	printf("\nNumber of Bits Per Sample: "); 
	
	if (wave.spec.format == AUDIO_S8 || wave.spec.format == AUDIO_U8) 
		{
			printf ("8"); 
		}
	else
		{
			printf ("16");		//since there is only 8 and 16
		}

	printf("\nSampling Frequency: "); 
	printf("%i", wave.spec.freq); 

	printf("\nDuration in seconds: "); 
	printf ("%d", wave.soundlen/wave.spec.freq/wave.spec.channels/2); 

	printf ("\n"); 
	printf("\n===============================");
	printf("\nTrack 2"); 
	printf("\nNumber of Channels: " ); 
	if (track2.spec.channels == 1) 
		{
			printf ("1"); 
		}
	else
		{
			printf ("2");		//since there is only mono and stereo
		}
	printf("\nNumber of Bits Per Sample: "); 
	
	if (track2.spec.format == AUDIO_S8 || track2.spec.format == AUDIO_U8) 
		{
			printf ("8"); 
		}
	else
		{
			printf ("16");		//since there is only 8 and 16
		}

	printf("\nSampling Frequency: "); 
	printf("%i", track2.spec.freq); 

	printf("\nDuration in seconds: "); 
	printf ("%i", track2.soundlen/track2.spec.freq/track2.spec.channels/2); 

}


/* Call this instead of exit(), so we can clean up SDL: atexit() is evil. */
static void quit(int rc)
{
	SDL_Quit();
	exit(rc);
}

void process_audio(Uint8 *audio_buf, int buf_size) {
	int i;
    switch (wave.spec.format) {
    case AUDIO_U16LSB: {
        // unsigned 16-bit sample, little-endian
        Uint16 *ptr = (Uint16 *)audio_buf;
        if (wave.spec.channels == 1) {
            // process mono audio
            for (i=0; i<buf_size; i += sizeof(Uint16)) {
#if (SDL_BYTE_ORDER == SDL_BIG_ENDIAN)
                Uint16 swap = SDL_Swap16(*ptr);
                double tmp = swap * volume;
                tmp = tmp > 65535.0 ? 65535.0 : tmp;
                swap = (Uint16)tmp;
                *ptr = SDL_Swap16(swap);
                ptr++; // note here ptr will move to 16 bits higher
#else
                double tmp = (*ptr) * volume;
                tmp = tmp > 65535.0 ? 65535.0 : tmp;
                *ptr = (Uint16)tmp;
                ptr++;
#endif
            }
        } else if (wave.spec.channels == 2) {
            // process stero audio
            for (i=0; i<buf_size; i += sizeof(Uint16)*2) {
#if (SDL_BYTE_ORDER == SDL_BIG_ENDIAN)
                // process left channel
                Uint16 swap = SDL_Swap16(*ptr);
                double tmp = swap * volume;
                tmp = tmp > 65535.0 ? 65535.0 : tmp;
                swap = (Uint16)tmp;
                *ptr = SDL_Swap16(swap);
                ptr++;
                
                // process right channel
                swap = SDL_Swap16(*ptr);
                tmp = swap * volume;
                tmp = tmp > 65535.0 ? 65535.0 : tmp;
                swap = (Uint16)tmp;
                *ptr = SDL_Swap16(swap);
                ptr++;
#else
                // process left channel
                double tmp = (*ptr) * volume;
                tmp = tmp > 65535.0 ? 65535.0 : tmp;
                *ptr = (Uint16)tmp;
                ptr++;
                
                // process right channel
                tmp = (*ptr) * volume;
                tmp = tmp > 65535.0 ? 65535.0 : tmp;
                *ptr = (Uint16)tmp;
                ptr++;
#endif
            }
        } else {
            fprintf(stderr, "Doesn't support more than 2 channels!\n");
            exit(1);
        }
        break; }
    case AUDIO_S16LSB: {
        // signed 16-bit sample, little-endian
        Sint16 *ptr = (Sint16 *)audio_buf;
        if (wave.spec.channels == 1) {
            // process mono audio
            for (i=0; i<buf_size; i += sizeof(Sint16)) {
#if (SDL_BYTE_ORDER == SDL_BIG_ENDIAN)
                Sint16 swap = SDL_Swap16(*ptr);
                double tmp = swap * volume;
                tmp = tmp > 32767.0 ? 32767.0 : tmp;
                tmp = tmp < -32768.0 ? -32768.0 : tmp;
                swap = (Sint16)tmp;
                *ptr = SDL_Swap16(swap);
                ptr++;
#else
                double tmp = (*ptr) * volume;
                tmp = tmp > 32767.0 ? 32767.0 : tmp;
                tmp = tmp < -32768.0 ? -32768.0 : tmp;
                *ptr = (Sint16)tmp;
                ptr++;
#endif
            }
        } else if (wave.spec.channels == 2) {
            // process stero audio
            for (i=0; i<buf_size; i += sizeof(Sint16)*2) {
#if (SDL_BYTE_ORDER == SDL_BIG_ENDIAN)
                // process left channel
                Sint16 swap = SDL_Swap(*ptr);
                double tmp = swap * volume;
                tmp = tmp > 32767.0 ? 32767.0 : tmp;
                tmp = tmp < -32768.0 ? -32768.0 : tmp;
                swap = (Sint16)tmp;
                *ptr = SDL_Swap16(swap);
                ptr++;
                
                // process right channel
                swap = SDL_Swap(*ptr);
                tmp = swap * volume;
                tmp = tmp > 32767.0 ? 32767.0 : tmp;
                tmp = tmp < -32768.0 ? -32768.0 : tmp;
                swap = (Sint16)tmp;
                *ptr = SDL_Swap16(swap);
                ptr++;
#else
                // process left channel
                double tmp = (*ptr) * volume;
                tmp = tmp > 32767.0 ? 32767.0 : tmp;
                tmp = tmp < -32768.0 ? -32768.0 : tmp;
                *ptr = (Sint16)tmp;
                ptr++;
                
                // process right channel
                tmp = (*ptr) * volume;
                tmp = tmp > 32767.0 ? 32767.0 : tmp;
                tmp = tmp < -32768.0 ? -32768.0 : tmp;
                *ptr = (Sint16)tmp;
                ptr++;
#endif
            }
        } else {
            fprintf(stderr, "Doesn't support more than 2 channels!\n");
            exit(1);
        }
        break; }
    case AUDIO_U16MSB: {
        // unsigned 16-bit sample, big-endian
        Uint16 *ptr = (Uint16 *)audio_buf;
        if (wave.spec.channels == 1) {
            // process mono audio
            for (i=0; i<buf_size; i += sizeof(Uint16)) {
#if (SDL_BYTE_ORDER == SDL_LIL_ENDIAN)
                Uint16 swap = SDL_Swap16(*ptr);
                double tmp = swap * volume;
                tmp = tmp > 65535.0 ? 65535.0 : tmp;
                swap = (Uint16)tmp;
                *ptr = SDL_Swap16(swap);
                ptr++; // note here ptr will move to 16 bits higher
#else
                double tmp = (*ptr) * volume;
                tmp = tmp > 65535.0 ? 65535.0 : tmp;
                *ptr = (Uint16)tmp;
                ptr++;
#endif
            }
        } else if (wave.spec.channels == 2) {
            // process stero audio
            for (i=0; i<buf_size; i += sizeof(Uint16)*2) {
#if (SDL_BYTE_ORDER == SDL_LIL_ENDIAN)
                // process left channel
                Uint16 swap = SDL_Swap16(*ptr);
                double tmp = swap * volume;
                tmp = tmp > 65535.0 ? 65535.0 : tmp;
                swap = (Uint16)tmp;
                *ptr = SDL_Swap16(swap);
                ptr++;
                
                // process right channel
                swap = SDL_Swap16(*ptr);
                tmp = swap * volume;
                tmp = tmp > 65535.0 ? 65535.0 : tmp;
                swap = (Uint16)tmp;
                *ptr = SDL_Swap16(swap);
                ptr++;
#else
                // process left channel
                double tmp = (*ptr) * volume;
                tmp = tmp > 65535.0 ? 65535.0 : tmp;
                *ptr = (Uint16)tmp;
                ptr++;
                
                // process right channel
                tmp = (*ptr) * volume;
                tmp = tmp > 65535.0 ? 65535.0 : tmp;
                *ptr = (Uint16)tmp;
                ptr++;
#endif
            }
        } else {
            fprintf(stderr, "Doesn't support more than 2 channels!\n");
            exit(1);
        }
        break; }
    case AUDIO_S16MSB: {
        // signed 16-bit sample, big-endian
        Sint16 *ptr = (Sint16 *)audio_buf;
        if (wave.spec.channels == 1) {
            // process mono audio
            for (i=0; i<buf_size; i += sizeof(Sint16)) {
#if (SDL_BYTE_ORDER == SDL_LIL_ENDIAN)
                Sint16 swap = SDL_Swap16(*ptr);
                double tmp = swap * volume;
                tmp = tmp > 32767.0 ? 32767.0 : tmp;
                tmp = tmp < -32768.0 ? -32768.0 : tmp;
                swap = (Sint16)tmp;
                *ptr = SDL_Swap16(swap);
                ptr++;
#else
                double tmp = (*ptr) * volume;
                tmp = tmp > 32767.0 ? 32767.0 : tmp;
                tmp = tmp < -32768.0 ? -32768.0 : tmp;
                *ptr = (Sint16)tmp;
                ptr++;
#endif
            }
        } else if (wave.spec.channels == 2) {
            // process stero audio
            for (i=0; i<buf_size; i += sizeof(Sint16)*2) {
#if (SDL_BYTE_ORDER == SDL_LIL_ENDIAN)
                // process left channel
                Sint16 swap = SDL_Swap(*ptr);
                double tmp = swap * volume;
                tmp = tmp > 32767.0 ? 32767.0 : tmp;
                tmp = tmp < -32768.0 ? -32768.0 : tmp;
                swap = (Sint16)tmp;
                *ptr = SDL_Swap16(swap);
                ptr++;
                
                // process right channel
                swap = SDL_Swap(*ptr);
                tmp = swap * volume;
                tmp = tmp > 32767.0 ? 32767.0 : tmp;
                tmp = tmp < -32768.0 ? -32768.0 : tmp;
                swap = (Sint16)tmp;
                *ptr = SDL_Swap16(swap);
                ptr++;
#else
                // process left channel
                double tmp = (*ptr) * volume;
                tmp = tmp > 32767.0 ? 32767.0 : tmp;
                tmp = tmp < -32768.0 ? -32768.0 : tmp;
                *ptr = (Sint16)tmp;
                ptr++;
                
                // process right channel
                tmp = (*ptr) * volume;
                tmp = tmp > 32767.0 ? 32767.0 : tmp;
                tmp = tmp < -32768.0 ? -32768.0 : tmp;
                *ptr = (Sint16)tmp;
                ptr++;
#endif
            }
        } else {
            fprintf(stderr, "Doesn't support more than 2 channels!\n");
            exit(1);
        }
        break; }
    }
}


void SDLCALL fillerup (void *unused, Uint8 *stream, int len) 
{
	Uint8 *waveptr; 
	int waveleft; 

	waveptr = wave.sound + wave.soundpos; 
	waveleft = wave.soundlen - wave.soundpos; 

	while (waveleft <= len) 
	{
		Uint8 *process_buf = (Uint8*) malloc (waveleft) ;
		SDL_memcpy(process_buf, waveptr, waveleft);

		SDL_memcpy (stream, process_buf, waveleft); 
		stream += waveleft; 
		len -= waveleft; 

		waveptr = wave.sound; 
		waveleft = wave.soundlen; 
		
		if (loop)
			wave.soundpos = 0; 
	
		free(process_buf); 
	}

		Uint8 *process_buf = (Uint8 *)malloc(sizeof(Uint8)*len);
		if (process_buf == NULL) return;

		if (loop)
		{
			SDL_memcpy(process_buf, waveptr, len);
			process_audio(process_buf, len);
		}
		else 
			{
				if (wave.soundpos == wave.soundlen)
					{
						SDL_memset (process_buf, 0, len); 
						SDL_QUIT; 
					}	
				else
				{
						SDL_memcpy(process_buf, waveptr, len);
						process_audio(process_buf, len);
				}
			}		
			
			
		// play the processed samples
		if (loop || len < (wave.soundlen-wave.soundpos))
		{
			SDL_memcpy(stream, process_buf, len);
			wave.soundpos += len;
			
		}

		else
		{
			
			SDL_memset (process_buf, 0, len); 
			SDL_memcpy(stream,process_buf, len); 
			done = 1; 
		}

		free(process_buf);

}

int main (int argc, char *argv[]) 
{
	char name [32]; 
	SDL_Event event; 
	SDL_Surface *screen; 
	int len; 

	printf ("=======================================");


	if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) 
	{
		fprintf (stderr, "Couldn't initialize SDL %s\n", SDL_GetError()); 
		return (1); 
	}

	if (argv[1] == NULL)	// no arguments are entered (Only mixplay.exe) 
	{
		fprintf (stderr, "Please enter 3 arguments"); 
		return (1); 
	}

	else if (strcmp (argv[1] , "-help") == 0)	// if the 1st argument is -help (mixplay.exe -help); 
	{
		printf ("\nTo use program enter \"mixplay.exe <number between 0 to 1, this is for volume of the 1st wav file> <1st wav file name> <2nd wav file name>\" "); 
		printf ("\nExample : \"mixplay.exe 0.5 22khzMusicMono16bits.wav 22khzSpeechMono16bits.wav\""); 
		printf ("\nPress Q to exit the program"); 
		printf ("\nPress T to enable/disable loop"); 
		printf ("\nPress R to Rewind to the beginning"); 
		return (1); 
	}

	else // if 1st argument is not help, check if 2 other arguments are keyed in for the wav file
	{
		if (argv[2] == NULL || argv [3] == NULL)			// if either 2nd or 3rd argument is empty 
			fprintf (stderr, "\nPlease enter 3 arguments"); 
		else												//set volume to the value
			volume = atof (argv[1]);
	}

	if (volume < 0 || volume > 1 )						// if volume is below 0 or more than 1 
	{
		fprintf (stderr, "\nAlpha cannot be larger than 1 or smaller than 0\n"); 
		return (1); 
	}

#ifndef __DARWIN__ 
	screen = SDL_SetVideoMode (SCR_WIDTH, SCR_HEIGHT, 0, 0); 
#else
	screen = SDL_SetVideoMode(SCR_WIDTH, SCR_HEIGHT, 24, 0);
#endif 

	 if (!screen) {
        fprintf(stderr, "SDL: could not set video mode - exiting\n");
        quit(1);
    }
	
	 //Loading 2nd arg into wave
	if ( SDL_LoadWAV(argv[2],
			&wave.spec, &wave.sound, &wave.soundlen) == NULL ) {
		fprintf(stderr, "Couldn't load %s: %s\n",
						argv[2], SDL_GetError());
		quit(1);
	}

	 //Loading 3rd arg into wave
	if ( SDL_LoadWAV(argv[3],
			&track2.spec, &track2.sound, &track2.soundlen) == NULL ) {
		fprintf(stderr, "Couldn't load %s: %s\n",
						argv[3], SDL_GetError());
		quit(1);
	}

	//Check if wave is not of 16 bit
	if (wave.spec.format != AUDIO_U16MSB && wave.spec.format != AUDIO_S16MSB && wave.spec.format != AUDIO_U16LSB && wave.spec.format != AUDIO_S16LSB)
	{
		printf ("\nTrack 1 is not of 16 bit"); 
		printInfo (); 
		quit(2);
	}

	//Check if track2 is not of 16 bit
	if (track2.spec.format != AUDIO_U16MSB && track2.spec.format != AUDIO_S16MSB && track2.spec.format != AUDIO_U16LSB && track2.spec.format != AUDIO_S16LSB)
	{
		printf ("\nTrack 2 is not of 16 bit"); 
		printInfo (); 
		quit(2);
	}

	//Check if wave and track 2 has the same sampling frequency 
	if (wave.spec.freq != track2.spec.freq) 
	{
		printf ("\nBoth track do not have the same sampling frequency"); 
		printInfo (); 
		quit(2);
	}


	// If wave is stereo
	if (wave.spec.channels == 2 )
			{
			//and track2 is mono, conversion for track2 to stereo needs to happen
			if (track2.spec.channels == 1)
				{

					SDL_AudioCVT cvt; 
					if (SDL_BuildAudioCVT (&cvt, track2.spec.format, track2.spec.channels, track2.spec.freq, track2.spec.format, 2, track2.spec.freq) < 0) 
						printf ("\nUnable to convert sound"); 

					cvt.len = track2.soundlen; 


					Uint8* process_buf = (Uint8*) malloc (cvt.len * cvt.len_mult); 
					if (process_buf == NULL) 
						printf ("\nMemory alloc fail"); 

					SDL_memcpy (process_buf, track2.sound, track2.soundlen); 

					cvt.buf = process_buf; 

					if (SDL_ConvertAudio (&cvt) < 0) 
						printf ("\nAudio Conversion Failed"); 

					SDL_FreeWAV (track2.sound); 
					track2.sound = process_buf; 
					track2.soundlen = track2.soundlen * cvt.len_mult; 

				}
			}
	
			// if wave is mono
	else          
			{
				// and track2 is stereo, conversion needs to happen as well
			if (track2.spec.channels == 2)
				{
					temp = track2; 
					track2 = wave; 
					wave = temp; 

					volume = 1 - volume;	// since swapping of samples have occured, the volume will have to be the opposite as well

					SDL_AudioCVT cvt; 
					if (SDL_BuildAudioCVT (&cvt, track2.spec.format, track2.spec.channels, track2.spec.freq, track2.spec.format, 2, track2.spec.freq) < 0) 
						printf ("\nUnable to convert sound"); 

					cvt.len = track2.soundlen; 


					Uint8* process_buf = (Uint8*) malloc (cvt.len * cvt.len_mult); 
					if (process_buf == NULL) 
						printf ("\nMemory alloc fail"); 

					SDL_memcpy (process_buf, track2.sound, track2.soundlen); 

					cvt.buf = process_buf; 

					if (SDL_ConvertAudio (&cvt) < 0) 
						printf ("\nAudio Conversion Failed"); 

					SDL_FreeWAV (track2.sound); 
					track2.sound = process_buf; 
					track2.soundlen = track2.soundlen * cvt.len_mult; 

				}
			}


	wave.spec.callback = fillerup;
	#if HAVE_SIGNAL_H
	/* Set the signals */
#ifdef SIGHUPq
	signal(SIGHUP, poked);
#endif
	signal(SIGINT, poked);
#ifdef SIGQUIT
	signal(SIGQUIT, poked);
#endif
	signal(SIGTERM, poked);
#endif /* HAVE_SIGNAL_H */

	SDL_AudioSpec desired, obtained; 

	desired.freq = wave.spec.freq; 
	desired.format = wave.spec.format; 
	desired.samples = wave.spec.samples; 
	desired.channels = wave.spec.channels; 
	desired.callback = fillerup ;
	desired.userdata = NULL; 

	/* Initialize fillerup() variables */
	if ( SDL_OpenAudio(&desired, &obtained) < 0 ) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		SDL_FreeWAV(wave.sound);
		quit(2);
	}

	printf ("\nLooping is enabled"); 
	// start playing
	SDL_PauseAudio(0);
	
		// if wave is of shorter duration than track2
		if (wave.soundlen < track2.soundlen)
		{
			while (wave.soundlen < track2.soundlen)
			{
				len = track2.soundlen - wave.soundlen; 
				int shortlen = wave.soundlen; 

				//Extend length of shorter track
				Uint8* process_buf = (Uint8*) malloc (sizeof (Uint8) * track2.soundlen); 
		
				SDL_memset(process_buf, 0, track2.soundlen); 
				SDL_memcpy(process_buf, wave.sound, wave.soundlen); 
		
				Uint8* soundpos; 
				soundpos = (Uint8*) malloc (sizeof (Uint8*) * track2.soundlen); 

				soundpos = process_buf + shortlen; 
				SDL_memcpy (soundpos, process_buf, len) ;
	
				if (wave.soundlen + len >= track2.soundlen)
					wave.soundlen = track2.soundlen; 
				else
					wave.soundlen += len; 
		
				free (wave.sound); 
				wave.sound = (Uint8*) malloc (sizeof (Uint8) * wave.soundlen); 
				SDL_memcpy (wave.sound, process_buf, wave.soundlen);	
			}
		
		}

		// if track 2 has a shorter duration
		else if (wave.soundlen > track2.soundlen)
		{
			while (wave.soundlen > track2.soundlen)
			{
				len = wave.soundlen - track2.soundlen; 
				int shortlen = track2.soundlen; 
		
				//Extend length of shorter track
				Uint8* process_buf = (Uint8*) malloc (sizeof (Uint8) * wave.soundlen); 
		
				SDL_memset(process_buf, 0, wave.soundlen); 
				SDL_memcpy(process_buf, track2.sound, track2.soundlen); 
		
				Uint8* soundpos; 
				soundpos = (Uint8*) malloc (sizeof (Uint8*) * track2.soundlen); 

				soundpos = process_buf + shortlen; 
				SDL_memcpy (soundpos, process_buf, len);

				if (track2.soundlen + len >= wave.soundlen)
					track2.soundlen = wave.soundlen; 
				else
					track2.soundlen += len; 
		
				free (track2.sound); 
				track2.sound = (Uint8*) malloc (sizeof (Uint8) * wave.soundlen); 
				SDL_memcpy (track2.sound, process_buf, wave.soundlen);	//track2.sound is changed to process_buf
			}
		}


		//Adjust volume of track1 
		Uint8 *newSound = (Uint8*) malloc (sizeof (Uint8) * wave.soundlen); 
		SDL_memset(newSound, 0, wave.soundlen);	
		SDL_MixAudio (newSound, wave.sound, wave.soundlen, SDL_MIX_MAXVOLUME*volume); 		
		SDL_memcpy (wave.sound, newSound, wave.soundlen);

		//Adjust volume of track2 
		free (newSound); 
		newSound = (Uint8*) malloc (sizeof (Uint8) * wave.soundlen); 
		SDL_memset(newSound, 0, wave.soundlen);	
		SDL_MixAudio (newSound, track2.sound, wave.soundlen, SDL_MIX_MAXVOLUME*(1-volume)); 		
		SDL_memcpy (track2.sound, newSound, wave.soundlen);


		//Mixing 2 audio together
		SDL_MixAudio (wave.sound, track2.sound, wave.soundlen, SDL_MIX_MAXVOLUME); 


	/* Let the audio run */
	printf("\nUsing audio driver: %s\n", SDL_AudioDriverName(name, 32));
	while ( ! done && (SDL_GetAudioStatus() == SDL_AUDIO_PLAYING)) {
        // Poll input queue, run keyboard loop
        while ( SDL_PollEvent(&event) ) {
            switch ( event.type )
				{
					case SDL_QUIT :
						done = 1;
						break; 
					case SDL_KEYDOWN: 
						switch (event.key.keysym.sym)
						{
							case SDLK_t:
									
									if (loop) 
										{
											loop = false; 
											printf ("Looping is disabled\n"); 
										}
									else
										{
											loop = true; 
											printf ("Looping is enabled\n"); 
											done = 0; 
										}
								break;
							
							case SDLK_q: 

									done = 1;	

								break;

							case SDLK_r:

									wave.soundpos = 0; 
									printf ("\nRewinding to start!"); 
								break;
						
						}

						break;	
				}
        } 
		
		SDL_Delay(100);
		
	}

	/* Clean up on signal */
	SDL_CloseAudio();
	SDL_FreeWAV(wave.sound);
	SDL_Quit();
	return(0);

}

