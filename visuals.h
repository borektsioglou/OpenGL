#define MODEL1 1
#define MODEL2 2
#define MODEL3 3
#define MODEL4 4


struct point 
{
	float x; 
	float y; 
	float z; 
	float vnx; 
	float vny; 
	float vnz; 
};

struct face
{
	int vtx[6];
};

struct starposition{
	float x;
	float y;
	float z;
};

struct model
{
	point *points;
	face *faces;
	int nvertices;
	int nfaces;
};


//-------- Functions --------------------------------
void Keyboard(unsigned char key,int x,int y);
void Render();
// The function responsible for drawing everything in the 
// OpenGL context associated to a window. 
void MenuSelect(int choice);
void text(const char *str,float size);
void Resize(int w, int h);
// Handle the window size changes and define the world coordinate 
// system and projection type

void Setup();
// Set up the OpenGL state machine and create a light source

void Idle();

void ReadFile(model*);
//Function for reading a model file

void DisplayModel(model);
// Function for displaying a model

void missilelaunch();