#include <vector>
#include <time.h>
#include <GL/glut.h>
#include <al.h>
#include <alc.h>

#include <Windows.h>

class Simon
{
public:
	//Structure to hold our element information for each element in Simon.
	struct element
	{
		float color[3];
		float translate[3];
		bool active;
		ALuint source;
	};

	//Game state enumeration to keep track of the current game's state.
	enum GameState {playSequence, playerInput, playerCorrect, playerIncorrect, gameReady, pause};

	//Constructor
	Simon()
	{
		up = new element();
		down = new element();
		right = new element();
		left = new element();
		center = new element();

		up->color[0] = 0.25f;
		up->color[1] = 0.0f;
		up->color[2] = 0.0f;

		down->color[0] = 0.25f;
		down->color[1] = 0.25f;
		down->color[2] = 0.0f;

		right->color[0] = 0.0f;
		right->color[1] = 0.0f;
		right->color[2] = 0.25f;

		left->color[0] = 0.0f;
		left->color[1] = 0.25f;
		left->color[2] = 0.0f;

		center->color[0] = 0.01f;
		center->color[1] = 0.01f;
		center->color[2] = 0.0f;

		up->translate[0] = 0.0f;
		up->translate[1] = 2.0f;
		up->translate[2] = -5.0f;

		down->translate[0] = 0.0f;
		down->translate[1] = -2.0f;
		down->translate[2] = -5.0f;

		right->translate[0] = 2.0f;
		right->translate[1] = 0.0f;
		right->translate[2] = -5.0f;

		left->translate[0] = -2.0f;
		left->translate[1] = 0.0f;
		left->translate[2] = -5.0f;

		center->translate[0] = 0.0f;
		center->translate[1] = 0.0f;
		center->translate[2] = -5.0f;

		up->active = false;
		down->active = false;
		right->active = false;
		left->active = false;
		center->active = false;

		camera[0] = 0.0;
		camera[1] = 0.0;

		srand((unsigned)time(0));

		rotationAngle = 0.0f;

		InitSoundEngine();

		up->source = LoadWavFile("Sounds/beep.wav", 0.0500f, 1.0f, AL_FALSE);
		right->source = LoadWavFile("Sounds/beep.wav", 0.0500f, 0.75f, AL_FALSE);
		down->source = LoadWavFile("Sounds/beep.wav", 0.05f, 0.5f, AL_FALSE);
		left->source = LoadWavFile("Sounds/beep.wav", 0.05f, 0.25f, AL_FALSE);

		musicSource = LoadWavFile("Sounds/simonMusic.wav", 0.35f, 1.0f, AL_TRUE);
		alSourcePlay(musicSource);
	}

	//Destructor
	~Simon()
	{
		alSourceStop(musicSource);

		CleanUpSoundEngine();

		delete[] up;
		delete[] down;
		delete[] center;
		delete[] left;
		delete[] right;
	}

	//Static function to return the instance for Simon.  We only want one instance
	//of Simon activate at a time.
	static Simon* Instance()
	{
		static Simon *simon = new Simon();
		
		return simon;
	}

	//A function to initialize the sequence, add the first item in the sequence,
	//and set the game flag to false.
	void Init()
	{
		sequence.clear();
		sequenceCount = 0;
		AddItemToSequence();
		flag = false;
	}

	//A function to activate the passed element.  This will brighten the
	//the element on screen.
	void Activate(element* _element)
	{
		if (_element != center)
		{
			if (!_element->active)
			{
				for (int i = 0; i < 3; i++)
					_element->color[i] *= 4.0f;

				PlaySoundWav(_element);
				_element->active = true;
			}
		}

		else
		{
			if (gameState == GameState::playerCorrect)
				_element->color[1] *= 100.0f;

			else if (gameState == GameState::playerIncorrect)
				_element->color[0] *= 100.0f;
		}
	}

	//A function to deactivate the passed element.  This will dim the element
	//on screen.
	void Deactivate(element* _element)
	{
		if (_element != center)
		{
			if (_element->active)
			{
				for (int i = 0; i < 3; i++)
					_element->color[i] /= 4.0f;

				_element->active = false;

				if (gameState == GameState::playerInput)
				{
					if ((*iter) != _element)
					{
						gameState = GameState::playerIncorrect;
						flag = false;
					}

					iter++;
				}
			}
		}

		else 
		{
			if (gameState == GameState::playerCorrect)
				_element->color[1] /= 100.0f;

			else if (gameState == GameState::playerIncorrect)
				_element->color[0] /= 100.0f;
		}
	}

	//A function to rotate the camera according to which elements are active
	//and not active.
	void RotateCamera()
	{
		if (up->active)
			if (camera[1] < up->translate[1] / 3)
				camera[1] += (((up->translate[1] / 3) - camera[1]) / 10.0);

		if (down->active)
			if (camera[1] > down->translate[1] / 3)
				camera[1] += (((down->translate[1] / 3) - camera[1]) / 10.0);

		if (right->active)
			if (camera[0] < right->translate[0] / 3)
				camera[0] += (((right->translate[0] / 3) - camera[0]) / 10.0);

		if (left->active)
			if (camera[0] > left->translate[0] / 3)
				camera[0] += (((left->translate[0] / 3) - camera[0]) / 10.0);

		if (!(up->active || down->active))
			if (camera[1] != 0.0)
				camera[1] -= (camera[1] / 10.0);
		
		if (!(right->active || left->active))
			if (camera[0] != 0.0)
				camera[0] -= (camera[0] / 10.0);
	}
	
	//A function to add a random item to the sequence in our Simon game.
	void AddItemToSequence()
	{
		switch(rand() % 4)
		{
		case 0:
			sequence.push_back(up);
			break;
		case 1:
			sequence.push_back(down);
			break;
		case 2:
			sequence.push_back(right);
			break;
		case 3:
			sequence.push_back(left);
			break;
		}

		sequenceCount++;
	}

	//A function to initialize the openAL sound engine.
	void InitSoundEngine()
	{
		device = alcOpenDevice(0);
		context = alcCreateContext(device, 0);

		alcMakeContextCurrent(context);
	}

	//A function to clean up the openAL elements in the proper order.
	void CleanUpSoundEngine()
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		alcCloseDevice(device);
	}

	//A function to load a wav file.  We will pass the file name, the gain, the pitch, and if the
	//sound should loop.
	ALuint LoadWavFile(char* _fileName, const float _gain, const float _pitch, const int _loop)
	{
		//Declare a file, data, wave format, riff header, and wave data objects.  This will be used
		//to break down the wave file for playing.
		FILE* soundFile = NULL;
		WAVE_Format waveFormat;
		RIFF_Header riffHeader;
		WAVE_Data waveData;
		unsigned char* data;

		//Create a format, buffer, and source object for playing the wav file.
		ALuint buffer;
		ALuint source;
		ALenum format;

		//Create arrays to hold the source position, source velocity, listener position,
		//listener velocity, and listener orientation. Velocity for both will be 0.
		//Position will be set to the same area and turn the listener so it is facing
		//the source.
		ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };
		ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };
		ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
		ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
		ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };  
		
		//Open the sound file prepping it for reading.
		soundFile = fopen(_fileName, "rb");

		//Read the riff header, wwave format, and wave data respectively.
		fread(&riffHeader, sizeof(RIFF_Header), 1, soundFile);
		fread(&waveFormat, sizeof(WAVE_Format), 1, soundFile);
		fread(&waveData, sizeof(WAVE_Data), 1, soundFile);

		//Initialize and load the data from the wave file.
		data = new unsigned char[waveData.subChunk2Size];
		fread(data, waveData.subChunk2Size, 1, soundFile);

		//Check to see how many bitsPerSample and number of channels the wav
		//file uses.  Set the format for the wave file based on this information.
		if (waveFormat.bitsPerSample == 8)
		{
			if (waveFormat.numOfChannels == 1)
			{
				format = AL_FORMAT_MONO8;
			}

			else if (waveFormat.numOfChannels == 2)
			{
				format = AL_FORMAT_STEREO8;
			}
		}

		else if (waveFormat.bitsPerSample == 16)
		{
			if (waveFormat.numOfChannels == 1)
			{
				format = AL_FORMAT_MONO16;
			}

			else if (waveFormat.numOfChannels == 2)
			{
				format = AL_FORMAT_STEREO16;
			}
		}
		
		//Generate a source and buffer in openAL.
		alGenBuffers(1, &buffer);
		alGenSources(1, &source);

		//Add the wave data to the buffer using the format and sampleRate of the wav file.
		alBufferData(buffer, format, data, waveData.subChunk2Size, waveFormat.sampleRate);

		//Set the listener position, velocity, and orientation in openAL.
		alListenerfv(AL_POSITION, ListenerPos);
		alListenerfv(AL_VELOCITY, ListenerVel);
		alListenerfv(AL_ORIENTATION, ListenerOri);

		//Set the source buffer, gain, pitch, position, velocity, and if the sound loops in
		//openAL.
		alSourcei(source, AL_BUFFER, buffer);
		alSourcef(source, AL_PITCH, _pitch);
		alSourcef(source, AL_GAIN, _gain);
		alSourcefv(source, AL_POSITION, SourcePos);
		alSourcefv(source, AL_VELOCITY, SourceVel);
		alSourcei(source, AL_LOOPING, _loop);

		//Return the source to store in the element structure.
		return source;
	}

	//Function to play the the sound associated to the element passed.
	void PlaySoundWav(element* _element)
	{
		alSourcePlay(_element->source);
	}

	void SaveTime()
	{
		saveTime = clock();
	}

	void SetSequenceIter()
	{
		iter = sequence.begin();
	}

	void SetGameState(GameState _gameState)
	{
		gameState = _gameState;
	}

	void SetFlag(bool _flag)
	{
		flag = _flag;
	}

	//A function to keep track of the current window size.  This will be used to
	//reshape the window and help handle the camera rotation when projecting.
	void SetResolution(int _width, int _height)
	{
		screenResolution[0] = _width;
		screenResolution[1] = _height;
	}
	
	//A function to handle rotating the center element.
	void RotateAngle()
	{
		rotationAngle += 0.5f;

		if (rotationAngle > 360.0f)
			rotationAngle = 0.0f;
	}
	
	//Getter to return the center element rotation angle.
	const float GetRotationAngle()
	{
		return rotationAngle;
	}

	//A function to return the current iterator for the sequence.
	std::vector<element*>::iterator& GetSequenceIter()
	{
		return iter;
	}

	//A function to advance the iterator in the sequence.
	void AdvanceSequenceIter()
	{
		iter++;
	}

	//Getter to return the current flag status.
	bool GetFlag()
	{
		return flag;
	}

	//Getter to return the current time saved.
	clock_t GetSavedTime()
	{
		return saveTime;
	}

	//Getter to return the current time elapsed.
	clock_t GetTimer()
	{
		return clock();
	}

	//Getter to return the pause between sequence activations to deactivations.
	const int GetSequencePause()
	{
		return (((1500 + (sequenceCount * 500)) / sequenceCount) + 250);
	}

	//Getter to return the pause between sequence deactivations to activations.
	const int GetBetweenSequencePause()
	{
		return 250;
	}

	//Getter to return the pause after a player is incorrect.
	const int GetGamePause()
	{
		return 2000;
	}

	//Getter to return the current sequence.
	std::vector<element*>& GetSequence()
	{
		return sequence;
	}

	//Getter to return the current game state.
	GameState GetGameState()
	{
		return gameState;
	}

	//Getter to return the Up element.
	element* GetUp()
	{
		return up;
	}

	//Getter to return the Down element.
	element* GetDown()
	{
		return down;
	}

	//Getter to return the Right element.
	element* GetRight()
	{
		return right;
	}

	//Getter to return the Left element.
	element* GetLeft()
	{
		return left;
	}

	//Getter to return the Center element.
	element* GetCenter()
	{
		return center;
	}

	//Getter to return the camera coordinates.
	double* GetCameraRotation()
	{
		return camera;
	}

	//Getter to return the current window resolution.
	int* GetResolution()
	{
		return screenResolution;
	}

private:
	element* up;
	element* down;
	element* left;
	element* right;
	element* center;

	double camera[2];
	int screenResolution[2];
	float rotationAngle;
	int random, sequenceCount;
	clock_t saveTime;
	std::vector<element*> sequence;
	std::vector<element*>::iterator iter;
	GameState gameState;
	bool flag;

	ALCdevice* device;
	ALCcontext* context;
	ALuint musicSource;

	struct RIFF_Header
	{
		char chunkID[4];
		long chunkSize;
		char format[4];
	};

	struct WAVE_Format
	{
		char subChunkID[4];
		long subChunkSize;
		short audioFormat;
		short numOfChannels;
		long sampleRate;
		long byteRate;
		short blockAlign;
		short bitsPerSample;
	};

	struct WAVE_Data
	{
		char subChunkID[4];
		long subChunk2Size;
	};
};