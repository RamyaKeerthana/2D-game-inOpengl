#include <iostream>
#include <cmath>
#include <fstream>
#include<string.h>
#include<sstream>
#include <vector>
#include<math.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include<stdio.h>
#include<stdlib.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define PI 3.14159265358979323846
#define DEG2RAD(DEG) ((DEG)*((PI)/(180.0)))
float b=0.1f;
float b2=0.2f;
float camera_rotation_angle=90;
float bird_rotation=0;
float bird_x=0;
float bird_h=0;
float t=0;
float u=0.0f;
float hit=0;
int angle=45;
float Stwinkle=20;
float g=1,mu=0.2,itsdown=0,offset=0,mu1=0.8;
float justhitim1=0,justhitim2=0,justhitim3=0,justhitim4=0;
float off=0;
int xdir=1;
int i=1;
float pan=0.0f,d1=0,d2=0;
int flag1=0,flag2=0,flag3=0,flag4=0,flag5=0,flag6=0,flag7=0,flag8=0,flag9=0;
float imoffsetx=0,imoffsety=0;
int r=0;
int Lifes=0,Score=0,speedangle=0;
char smds[3]={'s','a','f'};

int angle1=0;
float shape_rotation=0;
float shape1_rotation=0;
float shape2_rotation=0;
float shape3_rotation=0;
bool shape_rot_status = true;
float shape_rot_dir = 1;
bool shape1_rot_status = true;
float shape1_rot_dir = 1;
bool shape2_rot_status = true;
float shape2_rot_dir = 1;
bool shape3_rot_status = true;
float shape3_rot_dir = 1;
float zoom=1.0f;
void displayText( float x, float y,float z, int r, int g, int b, const char *string ) {
	int j = strlen( string );
 
	glColor3f( r, g, b );
	glRasterPos3d( x, y,z );
	for( int i = 0; i < j; i++ ) {
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
	}
}
void Restart()
{
if(Lifes==5)
{
printf("Game Over \n You Lost :( \n");
exit(0);
return;
}
printf("Lifes left: %d\n",5-Lifes);



if(flag1==0 or flag2==0 or flag3==0 or flag4==0 or flag5==0)
{
 b=0.1f;
 b2=0.2f;
 camera_rotation_angle=90,speedangle=0;
 bird_rotation=0;
 bird_x=0;
 bird_h=0;
 t=0;
 u=0.0f;
 hit=0;
angle=45;
 Stwinkle=20;
 g=1,mu=0.2,itsdown=0,offset=0,mu1=0.8;
 justhitim1=0,justhitim2=0,justhitim3=0,justhitim4=0;
 off=0;
 xdir=1;
 i=1;
 pan=0.0f,d1=0,d2=0;
 flag6=0,flag7=0,flag8=0,flag9=0;
 imoffsetx=0,imoffsety=0;
 r=0;
// Lifes=0;


 angle1=0;
 shape_rotation=0;
 shape1_rotation=0;
 shape2_rotation=0;
 shape3_rotation=0;
 shape_rot_status = true;
 shape_rot_dir = 1;
 shape1_rot_status = true;
 shape1_rot_dir = 1;
 shape2_rot_status = true;
 shape2_rot_dir = 1;
 shape3_rot_status = true;
 shape3_rot_dir = 1;
 zoom=1.0f;
}
else 
{
printf("Game Over \n You Won!!!!!!\n");
exit(0);
return;
}

}


using namespace std;
float T;

struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
	glm::mat4 projection;
	glm::mat4 model;
	glm::mat4 view;
	GLuint MatrixID;
} Matrices;

GLuint programID;

/* Function to load Shaders - Use it as it is */
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open())
	{
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

	// Link the program
	fprintf(stdout, "Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

/* Generate VAO, VBOs and return VAO handle */
struct VAO* create3DObject (GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat* color_buffer_data, GLenum fill_mode=GL_FILL)
{
    struct VAO* vao = new struct VAO;
    vao->PrimitiveMode = primitive_mode;
    vao->NumVertices = numVertices;
    vao->FillMode = fill_mode;

    // Create Vertex Array Object
    glGenVertexArrays(1, &(vao->VertexArrayID)); // VAO
    glGenBuffers (1, &(vao->VertexBuffer)); // VBO - vertices
    glGenBuffers (1, &(vao->ColorBuffer));  // VBO - colors

    glBindVertexArray (vao->VertexArrayID); // Bind the VAO 
    glBindBuffer (GL_ARRAY_BUFFER, vao->VertexBuffer); // Bind the VBO vertices 
    glBufferData (GL_ARRAY_BUFFER, 3*numVertices*sizeof(GLfloat), vertex_buffer_data, GL_STATIC_DRAW); // Copy the vertices into VBO
    glVertexAttribPointer(
                          0,                  // attribute 0. Vertices
                          3,                  // size (x,y,z)
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );

    glBindBuffer (GL_ARRAY_BUFFER, vao->ColorBuffer); // Bind the VBO colors 
    glBufferData (GL_ARRAY_BUFFER, 3*numVertices*sizeof(GLfloat), color_buffer_data, GL_STATIC_DRAW);  // Copy the vertex colors
    glVertexAttribPointer(
                          1,                  // attribute 1. Color
                          3,                  // size (r,g,b)
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );

    return vao;
}

/* Generate VAO, VBOs and return VAO handle - Common Color for all vertices */
struct VAO* create3DObject (GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode=GL_FILL)
{
    GLfloat* color_buffer_data = new GLfloat [3*numVertices];
    for (int i=0; i<numVertices; i++) {
        color_buffer_data [3*i] = red;
        color_buffer_data [3*i + 1] = green;
        color_buffer_data [3*i + 2] = blue;
    }

    return create3DObject(primitive_mode, numVertices, vertex_buffer_data, color_buffer_data, fill_mode);
}

/* Render the VBOs handled by VAO */
void draw3DObject (struct VAO* vao)
{
    // Change the Fill Mode for this object
    glPolygonMode (GL_FRONT_AND_BACK, vao->FillMode);

    // Bind the VAO to use
    glBindVertexArray (vao->VertexArrayID);

    // Enable Vertex Attribute 0 - 3d Vertices
    glEnableVertexAttribArray(0);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, vao->VertexBuffer);

    // Enable Vertex Attribute 1 - Color
    glEnableVertexAttribArray(1);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, vao->ColorBuffer);

    // Draw the geometry !
    glDrawArrays(vao->PrimitiveMode, 0, vao->NumVertices); // Starting from vertex 0; 3 vertices total -> 1 triangle
}

/**************************
 * Customizable functions *
 **************************/

void collisiontest()
{
	if(((-33+9*cos(DEG2RAD(angle))+bird_x-0)*(-33+9*cos(DEG2RAD(angle))+bird_x-0)+(-32+9*sin(DEG2RAD(angle))+bird_h-30)*(-32+9*sin(DEG2RAD(angle))+bird_h-30))<35 and flag1==0)
	{
		flag1=1;
		Score=Score+1;
		printf("Score : %d\n",Score);
	}

	if(((-33+9*cos(DEG2RAD(angle))+bird_x-30)*(-33+9*cos(DEG2RAD(angle))+bird_x-30)+(-32+9*sin(DEG2RAD(angle))+bird_h-10)*(-32+9*sin(DEG2RAD(angle))+bird_h-10))<35 and flag2==0)
	{
		flag2=1;
		Score=Score+1;
		printf("Score : %d\n",Score);
	}

	if(((-33+9*cos(DEG2RAD(angle))+bird_x-60)*(-33+9*cos(DEG2RAD(angle))+bird_x-60)+(-32+9*sin(DEG2RAD(angle))+bird_h-30)*(-32+9*sin(DEG2RAD(angle))+bird_h-30))<35 and flag3==0)
	{
		flag3=1;
		Score=Score+1;
		printf("Score : %d\n",Score);
	}
	
	if(((-33+9*cos(DEG2RAD(angle))+bird_x+60)*(-33+9*cos(DEG2RAD(angle))+bird_x+60)+(-32+9*sin(DEG2RAD(angle))+bird_h-0)*(-32+9*sin(DEG2RAD(angle))+bird_h-0))<35 and flag4==0)
	{
		flag4=1;
		Score=Score+1;
		printf("Score : %d\n",Score);
	}

	if(((-33+9*cos(DEG2RAD(angle))+bird_x-90)*(-33+9*cos(DEG2RAD(angle))+bird_x-90)+(-32+9*sin(DEG2RAD(angle))+bird_h-0)*(-32+9*sin(DEG2RAD(angle))+bird_h-0))<35 and flag5==0)
	{
		flag5=1;
		Score=Score+1;
		printf("Score : %d\n",Score);
	}
	if(-33+9*cos(DEG2RAD(angle))+bird_x >-13.5 and -33+9*cos(DEG2RAD(angle))+bird_x <13.5 and -33+9*sin(DEG2RAD(angle))+bird_h>=18 and -33+9*sin(DEG2RAD(angle))+bird_h<=19)
	{
		flag6=1;
	}
	if(-33+9*cos(DEG2RAD(angle))+bird_x <73.5 and -33+9*cos(DEG2RAD(angle))+bird_x >48 and -33+9*sin(DEG2RAD(angle))+bird_h>=18  and -33+9*sin(DEG2RAD(angle))+bird_h<=19) 
	{
		flag6=1;
	}
	if(-33+9*cos(DEG2RAD(angle))+bird_x<-52.5 and -33+9*cos(DEG2RAD(angle))+bird_x>-54.5 and  -33+9*sin(DEG2RAD(angle))+bird_h>=-35  and -33+9*sin(DEG2RAD(angle))+bird_h<=-11 )
	{
		//printf("ok1\n");
		flag7=1;
	}
	if(-33+9*cos(DEG2RAD(angle))+bird_x>24 and -33+9*cos(DEG2RAD(angle))+bird_x<26.5 and  -33+9*sin(DEG2RAD(angle))+bird_h>=-35  and -33+9*sin(DEG2RAD(angle))+bird_h<=-11)
	{
		flag8=1;
	//printf("ok2\n");
	}
	if(-33+9*cos(DEG2RAD(angle))+bird_x>84 and -33+9*cos(DEG2RAD(angle))+bird_x<86.5 and  -33+9*sin(DEG2RAD(angle))+bird_h>=-35  and -33+9*sin(DEG2RAD(angle))+bird_h<=-11)
	{
		flag9=1;
		//printf("ok3\n");
	}


}





/* Executed when a regular key is pressed */
void keyboardDown (unsigned char key, int x, int y)
{
    switch (key) {
        case 'Q':
        case 'q':
        case 27: //ESC
            exit (0);
        default:
            break;
    }
}

/* Executed when a regular key is released */
void keyboardUp (unsigned char key, int x, int y)
{
    switch (key) {
        
        case ' ':
         	hit=1;
//            rectangle_rot_status = !rectangle_rot_status;
            break;
        case 'a':
        case 'A':
		r=1;
		if(hit!=1)
		{
			if((angle%360)<150)
			{
				angle=angle+5;
				angle1=angle1+5;
				//printf("%d\n",angle);
			}
		}	
            break;
        case 'b':
        case 'B':
		if(hit!=1)
		{
			if(angle%360>0 )
			{
		  		angle=angle-5;
				angle1=angle1-5;
				//printf("%d\n",angle);
			}
		}
            break;
        case 'x':
	Stwinkle=Stwinkle+1.5;
            // do something
            break;
	case 'y':
	Stwinkle=Stwinkle-1.5;
            // do something
            break;
	case 'F':
	case 'f':
		
		if(hit != 1)
		{
			if(speedangle<180)
			{
			u=u+0.2;
			speedangle=speedangle+1;
			}
		}
            break;
	case 'S':
	case 's':
		if(hit != 1 and u>0)
		{
			
			u=u-0.2;
			
			speedangle=speedangle-1;
			
		}        
	    break;
	
        default:
            break;
    }
}

/* Executed when a special key is pressed */
void keyboardSpecialDown (int key, int x, int y)
{
switch(key)
{
	case GLUT_KEY_UP:
	zoom=zoom-0.1;
//do something here
		break;	
	case GLUT_KEY_DOWN:
	zoom=zoom+0.1;
//do something here
		break;
	case GLUT_KEY_RIGHT:
	
		
	if(pan<=76)	
	{
			
		pan=pan+3;
//printf("%f\n",pan);
	}
		break;
	case GLUT_KEY_LEFT:
	if (pan>=-37)
	{
		pan=pan-3;
//printf("%f\n",pan);
	}
		break;	
default:
break;
}

}

/* Executed when a special key is released */
void keyboardSpecialUp (int key, int x, int y)
{
switch(key)
{
	case GLUT_KEY_UP:
	zoom=zoom-0.1;
//do something here
		break;	
	case GLUT_KEY_DOWN:
	zoom=zoom+
0.1;
//do something here
		break;
	case GLUT_KEY_RIGHT:
	
		
	if(pan<=76)	
	{
			
		pan=pan+3;
//printf("%f\n",pan);
	}
		break;
	case GLUT_KEY_LEFT:
	if (pan>=-37)
	{
		pan=pan-3;
//printf("%f\n",pan);
	}
		break;	
default:
break;
}

}
void mouseWheel(int button, int dir, int x, int y)
{
    if (dir > 0)
    {
	zoom=zoom+0.1;
        // Zoom in
    }
    else
    {
	zoom=zoom-0.1;
        // Zoom out
    }

    return;
}



/* Executed when a mouse button 'button' is put into state 'state'
 at screen position ('x', 'y')
 */
void mouseClick (int button, int state, int x, int y)
{
    switch (button) {
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_UP or GLUT_DOWN)
	{
	if(pan<=76)	
	{
		pan=pan+3;
//printf("%f\n",pan);
	}
		}
    //            triangle_rot_dir *= -1;
            break;
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_UP or GLUT_DOWN) {
if (pan>=-37)
	{
		pan=pan-3;
//printf("%f\n",pan);
	}
            //    rectangle_rot_dir *= -1;
            }
            break;
}
}

/* Executed when the mouse moves to position ('x', 'y') */
void mouseMotion (int x, int y)
{
;
}


/* Executed when window is resized to 'width' and 'height' */
/* Modify the bounds of the screen here in glm::ortho or Field of View in glm::Perspective */
void reshapeWindow (int width, int height)
{
	GLfloat fov = 90.0f;
	// sets the viewport of openGL renderer
	glViewport (0, 0, (GLsizei) width, (GLsizei) height);
glMatrixMode(GL_PROJECTION);
//glLoadIdentity();

   // double aspect_ratio = (double)width / (double)height;
    //glOrtho(-10*aspect_ratio, 10*aspect_ratio, -10, 10, -1, 1);
	// set the projection matrix as perspective/ortho
	// Store the projection matrix in a variable for future use

    // Perspective projection for 3D views
    // Matrices.projection = glm::perspective (fov, (GLfloat) width / (GLfloat) height, 0.1f, 500.0f);

    // Ortho projection for 2D views

   
}

VAO *ground,*gallon,*gallonhead,*bird,*shape, *shape1, *shape2, *shape3, *tar1,*tar2,*tar3,*tar4,*tar5,*movable1,*movable2,*immovable3,*immovable1,*immovable2,*speed,*speedhead,*lifemeter,*life;










void createspeed()
{

GLfloat* vertex_buffer_data=new GLfloat[3*360];
int i;
for(i=0;i<180;i++)
{
vertex_buffer_data[3*i]=(7 *cos(DEG2RAD(i)));
vertex_buffer_data[3*i+1]=(7 *sin(DEG2RAD(i)));
vertex_buffer_data[3*i+2]=0;
}
GLfloat color_buffer_data[3*360];

for(i=0;i<360;i++)
{

color_buffer_data[3*i]=0;
color_buffer_data[3*i+1]=0;
color_buffer_data[3*i+2]=0;

}
 speed=create3DObject(GL_LINE_LOOP,360,vertex_buffer_data,color_buffer_data,GL_FILL);
}




void createspeedhead ()
{
  // GL3 accepts only Triangles. Quads are not supported


 static const GLfloat data [] = {

     0,0.85*0.5,0, // vertex 1
    6,0.85*0.5,0, // vertex 2
    6, -0.85*0.5,0, // vertex 3

    6, -0.85*0.5,0, // vertex 3
    0, -0.85*0.5,0, // vertex 4
    0,0.85*0.5,0, // vertex 1
  };

  static const GLfloat color_buffer_data [] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0.3,0,0,0.3,0,0,0.3,0,0,0.3,0,0,0.3,0,0,0.3,
48,26,26,48,26,26,48,26,26,48,26,26,48,26,26,48,26,26,

   0,1,2, // color 1
    0,1,7, // color 2
    7,10,15, // color 3

    0,2,15, // color 3
    0,2,15, // color 4
    0,2,20,  // color 1
  };

  // create3DObject creates and returns a handle to a VAO that can be used later
  speedhead = create3DObject(GL_TRIANGLES, 6, data, color_buffer_data, GL_FILL);

}


void createtar()
{
static const GLfloat vertex_buffer_data [] = {

-1,1,0,
5,5,0,
1,-1,0,

1,1,0,
5,-5,0,
-1,-1,0,

1,-1,0,
-1,1,0,
-5,-5,0,

-1,-1,0,
1,1,0,
-5,5,0,


1,1,0,
0,6,0,
-1,1,0,

-1,1,0,
1,1,0,
0,0,0,

1,1,0,
0,0,0,
1,-1,0,

1,-1,0,
4.5,0,0,
1,1,0,

0,0,0,
1,-1,0,
-1,-1,0,

-1,-1,0,
0,-6,0,
1,-1,0,

-1,-1,0,
0,0,0,
-1,1,0,

-1,1,0,
-4.5,0,0,
-1,-1,0,




};
static const GLfloat color_buffer_data [] = {
    

0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,
    
  };

tar1= create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color_buffer_data, GL_FILL);
tar2= create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color_buffer_data, GL_FILL);
tar3= create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color_buffer_data, GL_FILL);
tar4= create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color_buffer_data, GL_FILL);
tar5= create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color_buffer_data, GL_FILL);

}








void createshape ()
{
	static const GLfloat vertex_buffer_data [] = {
	

	 0,-1.5,0, -1.5,0,0, -0.1,-0.1,0, -1.5,0,0, -0.1,0.1,0, 0,1.5,0,0,1.5,0, 0.1,0.1,0, 1.5,0,0,  1.5,0,0, 0.1,-0.1,0, 0,-1.5,0, 
	
};
static const GLfloat color_buffer_data [] = {
    
     3,0,0, // color 0
    0,3,0, // color 1
    0,0,3, // color 2
    3,0,0,
    0,0,3,
    0,3,0,
	 2,0,0, // color 0
    0,2,0, // color 1
    0,0,2, // color 2
    2,0,0,
    0,0,2,
    0,2,0,
  };

shape = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data, color_buffer_data, GL_FILL);

}
void createshape1 ()
{
	static const GLfloat vertex_buffer_data [] = {
	

	 0,-1.5,0, -1.5,0,0, -0.1,-0.1,0, -1.5,0,0, -0.1,0.1,0, 0,1.5,0,0,1.5,0, 0.1,0.1,0, 1.5,0,0,  1.5,0,0, 0.1,-0.1,0, 0,-1.5,0, 
	
};
static const GLfloat color_buffer_data [] = {
    
     3,0,0, // color 0
    0,3,0, // color 1
    0,0,3, // color 2
    3,0,0,
    0,0,3,
    0,3,0,
	 2,0,0, // color 0
    0,2,0, // color 1
    0,0,2, // color 2
    2,0,0,
    0,0,2,
    0,2,0,
  };

shape1 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data, color_buffer_data, GL_FILL);

}
void createshape2 ()
{
	static const GLfloat vertex_buffer_data [] = {
	

	 0,-1,0, -1,0,0, -0.1,-0.1,0, -1,0,0, -0.1,0.1,0, 0,1,0,0,1,0, 0.1,0.1,0, 1,0,0,  1,0,0, 0.1,-0.1,0, 0,-1,0, 
	
};
static const GLfloat color_buffer_data [] = {
    
     3,0,0, // color 0
    0,3,0, // color 1
    0,0,3, // color 2
    3,0,0,
    0,0,3,
    0,3,0,
	 2,0,0, // color 0
    0,2,0, // color 1
    0,0,2, // color 2
    2,0,0,
    0,0,2,
    0,2,0,
  };

shape2 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data, color_buffer_data, GL_FILL);

}
void createshape3 ()
{
	static const GLfloat vertex_buffer_data [] = {
	

	 0,-1,0, -1,0,0, -0.1,-0.1,0, -1,0,0, -0.1,0.1,0, 0,1,0,0,1,0, 0.1,0.1,0, 1,0,0,  1,0,0, 0.1,-0.1,0, 0,-1,0, 
	
};
static const GLfloat color_buffer_data [] = {
    
     3,0,0, // color 0
    0,3,0, // color 1
    0,0,3, // color 2
    3,0,0,
    0,0,3,
    0,3,0,
	 2,0,0, // color 0
    0,2,0, // color 1
    0,0,2, // color 2
    2,0,0,
    0,0,2,
    0,2,0,
  };

shape3 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data, color_buffer_data, GL_FILL);

}

void createground ()
{
  // GL3 accepts only Triangles. Quads are not supported


 static const GLfloat data [] = { 
-80,-40,0,
-80,-35,0,
120,-35,0,
120,-40,0,

    
  };
  
  static const GLfloat color_buffer_data [] = {
    1,0,0, // color 1
    0,0,1, // color 2
    0,1,0, // color 3

    0,1,0, // color 3
   // 0.3,0.3,0.3, // color 4
   // 1,0,0  // color 1
  };

  // create3DObject creates and returns a handle to a VAO that can be used later
  ground = create3DObject(GL_TRIANGLE_FAN, 4, data, color_buffer_data, GL_FILL);
}



void creategallon()
{

GLfloat* vertex_buffer_data=new GLfloat[3*360];
int i;
for(i=0;i<360;i++)
{
vertex_buffer_data[3*i]=(3 *cos(DEG2RAD(i)));
vertex_buffer_data[3*i+1]=(3 *sin(DEG2RAD(i)));
vertex_buffer_data[3*i+2]=0;
}
GLfloat color_buffer_data[3*360];

for(i=0;i<360;i++)
{

color_buffer_data[3*i]=1;
color_buffer_data[3*i+1]=0;
color_buffer_data[3*i+2]=0;

}
 gallon=create3DObject(GL_TRIANGLE_FAN,360,vertex_buffer_data,color_buffer_data,GL_FILL);
}

void creategallonhead ()
{
  // GL3 accepts only Triangles. Quads are not supported


 static const GLfloat data [] = {

     0,0.85,0, // vertex 1
    9,0.85,0, // vertex 2
    9, -0.85,0, // vertex 3

    9, -0.85,0, // vertex 3
    0, -0.85,0, // vertex 4
    0,0.85,0, // vertex 1
  };

  static const GLfloat color_buffer_data [] = {
0,0,0.3,0,0,0.3,0,0,0.3,0,0,0.3,0,0,0.3,0,0,0.3,
48,26,26,48,26,26,48,26,26,48,26,26,48,26,26,48,26,26,

   0,1,2, // color 1
    0,1,7, // color 2
    7,10,15, // color 3

    0,2,15, // color 3
    0,2,15, // color 4
    0,2,20,  // color 1
  };

  // create3DObject creates and returns a handle to a VAO that can be used later
  gallonhead = create3DObject(GL_TRIANGLES, 6, data, color_buffer_data, GL_FILL);

}


void createbird()
{

GLfloat* vertex_buffer_data=new GLfloat[3*360];
int i;
for(i=0;i<360;i++)
{
vertex_buffer_data[3*i]=(1.1 *cos(DEG2RAD(i)))+9*cos(DEG2RAD(45));
vertex_buffer_data[3*i+1]=(1.1 *sin(DEG2RAD(i)))+9*sin(DEG2RAD(45));
vertex_buffer_data[3*i+2]=0;
}
GLfloat color_buffer_data[3*360];

for(i=0;i<360;i++)
{

color_buffer_data[3*i]=0;
color_buffer_data[3*i+1]=0;
color_buffer_data[3*i+2]=0;

}
 bird=create3DObject(GL_TRIANGLE_FAN,360,vertex_buffer_data,color_buffer_data,GL_FILL);
}



void createimmovable ()
{
  // GL3 accepts only Triangles. Quads are not supported


 static const GLfloat data [] = { 
-3*2*2,-1*1.5*2,0,
-3*2*2,1*1.5*2,0,
-1*2*2,-1*1.5*2,0,
-1*2*2,1*1.5*2,0,
1*2*2,-1*1.5*2,0,
1*2*2,1*1.5*2,0,
3*2*2,-1*1.5*2,0,
3*2*2,1*1.5*2,0,
  };
  
  static const GLfloat color_buffer_data [] = {
    1,0,0, // color 1
    0,0,1, // color 2
    0,1,0, // color 3

    0,1,0, // color 3
   // 0.3,0.3,0.3, // color 4
   // 1,0,0  // color 1
1,0,0, // color 1
    0,0,1, // color 2
    0,1,0, // color 3

    0,1,0, // color 3
   // 0.3,0.3,0.3, // color 4
   // 1,0,0  // color 1
  };

  // create3DObject creates and returns a handle to a VAO that can be used later
  immovable1 = create3DObject(GL_TRIANGLE_FAN, 8, data, color_buffer_data, GL_FILL);
  immovable2 = create3DObject(GL_TRIANGLE_FAN, 8, data, color_buffer_data, GL_FILL);
//immovable3 = create3DObject(GL_TRIANGLE_FAN, 8, data, color_buffer_data, GL_FILL);

}

void createimmovable3 ()
{
  // GL3 accepts only Triangles. Quads are not supported


 static const GLfloat data [] = { 
-1*6,2*6,0,
1*6,2*6,0,
0,1*6,0,

0,1*6,0,
-1*6,0,0,
1*6,0,0,

-1*6,0,0,
1*6,0,0,
0,-1*6,0,

0,-1*6,0,
-1*6,-2*6,0,
1*6,-2*6,0,

 };
  
  static const GLfloat color_buffer_data [] = {
    1,0,0, // color 1
    0,0,1, // color 2
    0,1,0, // color 3

    0,1,0, // color 3
   // 0.3,0.3,0.3, // color 4
   // 1,0,0  // color 1
	1,0,0, // color 1
    0,0,1, // color 2
    0,1,0, // color 3

    0,1,0, // color 3
   // 0.3,0.3,0.3, // color 4
   // 1,0,0  // color 1
 1,0,0, // color 1
    0,0,1, // color 2
    0,1,0, // color 3

    0,1,0, // color 3
   // 0.3,0.3,0.3, // color 4
   // 1,0,0  // color 1
	1,0,0, // color 1
    0,0,1, // color 2
    0,1,0, // color 3

    0,1,0, // color 3
   // 0.3,0.3,0.3, // color 4
   // 1,0,0  // color 1

  };

  // create3DObject creates and returns a handle to a VAO that can be used later
  immovable3 = create3DObject(GL_TRIANGLES, 12, data, color_buffer_data, GL_FILL);
 movable1 = create3DObject(GL_TRIANGLES, 12, data, color_buffer_data, GL_FILL);
  movable2 = create3DObject(GL_TRIANGLES, 12, data, color_buffer_data, GL_FILL);	

}
















/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw ()
{
T=glutGet(GLUT_ELAPSED_TIME);
//printf("%f\n",h);
 Matrices.projection = glm::ortho((-40.0f+pan)*zoom, (40.0f+pan)*zoom, (-40.0f)*zoom, (40.0f)*zoom, 0.1f, 500.0f);
  // clear the color and depth in the frame buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // use the loaded shader program
  // Don't change unless you know what you are doing
  glUseProgram (programID);

  // Eye - Location of camera. Don't change unless you are sure!!
  glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, (5)*sin(camera_rotation_angle*M_PI/90.0f) );
  // Target - Where is the camera looking at.  Don't change unless you are sure!!
  glm::vec3 target (0, 0, 0);
  // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
  glm::vec3 up (0, 1, 0);

  // Compute Camera matrix (view)
   //Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
  //  Don't change unless you are sure!!
  Matrices.view = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane

  // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
  //  Don't change unless you are sure!!
  glm::mat4 VP = Matrices.projection * Matrices.view;

  // Send our transformation to the currently bound shader, in the "MVP" uniform
  // For each model you render, since the MVP will be different (at least the M part)
  //  Don't change unless you are sure!!
  glm::mat4 MVP;	// MVP = Projection * View * Model







  /* Render your scene */
 
  // draw3DObject draws the VAO given to it using current MVP matrix
  




Matrices.model = glm::mat4(1.0f);

  /* Render your scene */
 glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(Stwinkle));
 glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(3.0f));
  glm::mat4 translateshape = glm::translate (glm::vec3(-10.0f, 22.0f, 0.0f)); // glTranslatef
  glm::mat4 rotateshape = glm::rotate((float)(shape_rotation*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
  glm::mat4 shapeTransform = translateshape * rotateshape* scale*Scale;
  Matrices.model *= shapeTransform; 
  MVP = VP * Matrices.model; // MVP = p * V * M

  //  Don't change unless you are sure!!
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  // draw3DObject draws the VAO given to it using current MVP matrix
  draw3DObject(shape);







Matrices.model = glm::mat4(1.0f);

  /* Render your scene */
 glm::mat4 Scale1 = glm::scale(glm::mat4(1.0f), glm::vec3(Stwinkle));
 glm::mat4 scale1 = glm::scale(glm::mat4(1.0f), glm::vec3(3.0f));
  glm::mat4 translateshape1 = glm::translate (glm::vec3(10.0f, 22.0f, 0.0f)); // glTranslatef
  glm::mat4 rotateshape1 = glm::rotate((float)(shape1_rotation*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
  glm::mat4 shape1Transform = translateshape1 * rotateshape1* scale1*Scale1;
  Matrices.model *= shape1Transform; 
  MVP = VP * Matrices.model; // MVP = p * V * M

  //  Don't change unless you are sure!!
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  // draw3DObject draws the VAO given to it using current MVP matrix
  draw3DObject(shape1);



Matrices.model = glm::mat4(1.0f);

  /* Render your scene */
 glm::mat4 Scale2 = glm::scale(glm::mat4(1.0f), glm::vec3(Stwinkle));
glm::mat4 scale2 = glm::scale(glm::mat4(1.0f), glm::vec3(7.0f));
  glm::mat4 translateshape2 = glm::translate (glm::vec3(-20.0f, 0.0f, 0.0f)); // glTranslatef
  glm::mat4 rotateshape2 = glm::rotate((float)(shape2_rotation*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
  glm::mat4 shape2Transform = translateshape2 * rotateshape2* scale2*Scale2;
  Matrices.model *= shape2Transform; 
  MVP = VP * Matrices.model; // MVP = p * V * M

  //  Don't change unless you are sure!!
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  // draw3DObject draws the VAO given to it using current MVP matrix
  draw3DObject(shape2);


Matrices.model = glm::mat4(1.0f);

  /* Render your scene */
 glm::mat4 Scale3 = glm::scale(glm::mat4(1.0f), glm::vec3(Stwinkle));
glm::mat4 scale3 = glm::scale(glm::mat4(1.0f), glm::vec3(7.0f));

  glm::mat4 translateshape3 = glm::translate (glm::vec3(20.0f, 0.0f, 0.0f)); // glTranslatef
  glm::mat4 rotateshape3 = glm::rotate((float)((-1)*shape3_rotation*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
  glm::mat4 shape3Transform = translateshape3 * rotateshape3*scale3*Scale3 ;
  Matrices.model *= shape3Transform; 
  MVP = VP * Matrices.model; // MVP = p * V * M

  //  Don't change unless you are sure!!
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  // draw3DObject draws the VAO given to it using current MVP matrix
  draw3DObject(shape3);

 


// Load identity to model matrix
  Matrices.model = glm::mat4(1.0f);  

  MVP = VP * Matrices.model; // MVP = p * V * M

  //  Don't change unless you are sure!!
 glm::mat4 Scal3 = glm::scale(glm::mat4(1.0f), glm::vec3(Stwinkle));
Matrices.model *= Scal3; 
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  // draw3DObject draws the VAO given to it using current MVP matrix
  draw3DObject(ground);


// Load identity to model matrix
  Matrices.model = glm::mat4(1.0f);

  /* Render your scene */

    
  glm::mat4 gallonTransform = glm::translate (glm::vec3(-33.0f, -32.0f, 0.0f));
  Matrices.model *= gallonTransform; 
  MVP = VP * Matrices.model; // MVP = p * V * M

  //  Don't change unless you are sure!!
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  // draw3DObject draws the VAO given to it using current MVP matrix
  draw3DObject(gallon);



  



// Pop matrix to undo transformations till last push matrix instead of recomputing model matrix
  // glPopMatrix ();
  Matrices.model = glm::mat4(1.0f);

  glm::mat4 translategallonhead = glm::translate (glm::vec3(-33.0f, -32.0f, 0.0f));        // glTranslatef
  glm::mat4 rotategallonhead= glm::rotate((float)(angle*M_PI/180), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
  Matrices.model *= (translategallonhead* rotategallonhead);
  MVP = VP * Matrices.model;
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  // draw3DObject draws the VAO given to it using current MVP matrix
  draw3DObject(gallonhead);




// Load identity to model matrix
  Matrices.model = glm::mat4(1.0f);

  /* Render your scene */
glm::mat4 translatebird= glm::translate (glm::vec3(bird_x-33.0f, bird_h-32.0f, 0.0f));
  glm::mat4 rotatebird = glm::rotate((float)(angle1*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
  Matrices.model *= (translatebird * rotatebird);
  MVP = VP * Matrices.model; // MVP = p * V * M

  //  Don't change unless you are sure!!
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  // draw3DObject draws the VAO given to it using current MVP matrix
  draw3DObject(bird);



if(flag1==0)
{
Matrices.model = glm::mat4(1.0f);
glm::mat4 scal3 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
  glm::mat4 translatetar = glm::translate (glm::vec3(0.0f, 30.0f, 0.0f)); // glTranslatef
 
  glm::mat4 tarTransform = translatetar ;
  Matrices.model *= tarTransform*scal3 ; 
  MVP = VP * Matrices.model; // MVP = p * V * M

  //  Don't change unless you are sure!!
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);


 draw3DObject(tar1);

}


Matrices.model = glm::mat4(1.0f);
glm::mat4 m1scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
glm::mat4 translatem1 = glm::translate (glm::vec3(0.0f, 21.0f, 0.0f)); // glTranslatef
Matrices.model *= translatem1*m1scale ; 
 MVP = VP * Matrices.model; 
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
draw3DObject(immovable1);


if(flag2==0)
{
Matrices.model = glm::mat4(1.0f);
glm::mat4 al3 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
  glm::mat4 translatetar2 = glm::translate (glm::vec3 (30.0f, 10.0f, 0.0f)); // glTranslatef
 
  glm::mat4 tar2Transform = translatetar2 ;
  Matrices.model *= tar2Transform*al3 ; 
  MVP = VP * Matrices.model; // MVP = p * V * M

  //  Don't change unless you are sure!!
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);


 draw3DObject(tar2);
}






Matrices.model = glm::mat4(1.0f);
glm::mat4 i1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
  glm::mat4 translatei1 = glm::translate (glm::vec3 (30.0f+d1, -23.0f, 0.0f)); // glTranslatef
 
  glm::mat4 i1Transform = translatei1 ;
  Matrices.model *= i1Transform*i1 ; 
  MVP = VP * Matrices.model; // MVP = p * V * M

  //  Don't change unless you are sure!!
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

draw3DObject(movable1);




if( flag3==0)
{
Matrices.model = glm::mat4(1.0f);
glm::mat4 cal3 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
  glm::mat4 translatetar3 = glm::translate (glm::vec3(60.0f, 30.0f, 0.0f)); // glTranslatef
 
  glm::mat4 tar3Transform = translatetar3 ;
  Matrices.model *= tar3Transform*cal3 ; 
  MVP = VP * Matrices.model; // MVP = p * V * M

  //  Don't change unless you are sure!!
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);


 draw3DObject(tar3);


}



Matrices.model = glm::mat4(1.0f);
glm::mat4 m2scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
glm::mat4 translatem2 = glm::translate (glm::vec3(60.0f, 21.0f, 0.0f)); // glTranslatef
Matrices.model *= translatem2*m2scale ; 
 MVP = VP * Matrices.model; 	
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
draw3DObject(immovable2);





if(flag4==0)
{

Matrices.model = glm::mat4(1.0f);
glm::mat4 sc3 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
  glm::mat4 translatetar4 = glm::translate (glm::vec3(-60.0f, 0.0f, 0.0f)); // glTranslatef
 
  glm::mat4 tar4Transform = translatetar4 ;
  Matrices.model *= tar4Transform*sc3 ; 
  MVP = VP * Matrices.model; // MVP = p * V * M

  //  Don't change unless you are sure!!
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);


 draw3DObject(tar4);



}


Matrices.model = glm::mat4(1.0f);
glm::mat4 m3scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
glm::mat4 translatem3 = glm::translate (glm::vec3(-60.0f, -23.0f, 0.0f)); // glTranslatef
glm::mat4 m3Transform = translatem3 ;
  Matrices.model *= m3Transform*m3scale; 
  MVP = VP * Matrices.model; // MVP = p * V * M

  //  Don't change unless you are sure!!
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);


draw3DObject(immovable3);


if(flag5==0)
{
Matrices.model = glm::mat4(1.0f);
glm::mat4 sca3 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
  glm::mat4 translatetar5 = glm::translate (glm::vec3(90.0f, 0.0f, 0.0f)); // glTranslatef
 
  glm::mat4 tar5Transform = translatetar5 ;
  Matrices.model *= tar5Transform*sca3 ; 
  MVP = VP * Matrices.model; // MVP = p * V * M

  //  Don't change unless you are sure!!
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);


 draw3DObject(tar5);
}



Matrices.model = glm::mat4(1.0f);
glm::mat4 i2 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
  glm::mat4 translatei2 = glm::translate (glm::vec3(90.0f+d2, -23.0f, 0.0f)); // glTranslatef
 
  glm::mat4 i2Transform = translatei2 ;
  Matrices.model *= i2Transform*i2 ; 
  MVP = VP * Matrices.model; // MVP = p * V * M

  //  Don't change unless you are sure!!
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

draw3DObject(movable2);


if(hit!=1)
{
 Matrices.model = glm::mat4(1.0f);
 glm::mat4 speedTransform = glm::translate (glm::vec3(-27.0f+pan, 25.0f, 0.0f));
  Matrices.model *= speedTransform; 
  MVP = VP * Matrices.model; // MVP = p * V * M

  //  Don't change unless you are sure!!
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  // draw3DObject draws the VAO given to it using current MVP matrix
  draw3DObject(speed);



  



// Pop matrix to undo transformations till last push matrix instead of recomputing model matrix
  // glPopMatrix ();
  Matrices.model = glm::mat4(1.0f);

  glm::mat4 translatespeedhead = glm::translate (glm::vec3(-27.0f+pan, 25.0f, 0.0f));        // glTranslatef
  glm::mat4 rotatespeedhead= glm::rotate((float)(speedangle*M_PI/180), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
  Matrices.model *= (translatespeedhead* rotatespeedhead);
  MVP = VP * Matrices.model;
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  // draw3DObject draws the VAO given to it using current MVP matrix
  draw3DObject(speedhead);





}





collisiontest();
 float increments = 1;
 

if(hit==1)
{





   if(bird_h>-((9*abs(sin(DEG2RAD(angle)))) + 1.8))
   {

if(flag6==1)
	{
	if(justhitim1!=1 )
	{
		//printf("asa");
		justhitim1=1;
		t=0;
		imoffsetx=bird_x;
		imoffsety=bird_h;
	}
	
			
		bird_x=(u*cos(DEG2RAD(angle)))*0.5*t+imoffsetx;
		bird_h=(u*sin(DEG2RAD(-angle))*t-(0.5)*(g)*t*t)+imoffsety;
		t=t+0.1;
	}

else if(flag7==1)
	{
	if(justhitim2!=1 )
	{
		//printf("asa");
		justhitim2=1;
		t=0;
		imoffsetx=bird_x;
		imoffsety=bird_h;
	}
	
			
		bird_x=-(u*cos(DEG2RAD(angle)))*0.5*t+imoffsetx;
		bird_h=(u*sin(DEG2RAD(0))*t-(0.5)*(g)*t*t)+imoffsety;
		t=t+0.1;
	}

 else if(flag8==1)
	{
	if(justhitim3!=1 )
	{
		//printf("asa");
		justhitim3=1;
		t=0;
		imoffsetx=bird_x;
		imoffsety=bird_h;
	}
	
			
		bird_x=-(u*cos(DEG2RAD(angle)))*0.5*t+imoffsetx;
		bird_h=(u*sin(DEG2RAD(-angle))*t-(0.5)*(g)*t*t)+imoffsety;
//printf("FDG");
		if(t<3)
		d1=((1)*t-(0.5)*mu*(t)*(t))*(0.1)+d1;
		t=t+0.1;
	}
 else if(flag9==1)
	{
	if(justhitim4!=1 )
	{
		//printf("asa");
		justhitim4=1;
		t=0;
		imoffsetx=bird_x;
		imoffsety=bird_h;
	}
	
			
		bird_x=-(u*cos(DEG2RAD(angle)))*0.5*t+imoffsetx;
		bird_h=(u*sin(DEG2RAD(-angle))*t-(0.5)*(g)*t*t)+imoffsety;
		if(t<3)
		d2=((1)*t-(0.5)*mu*(t)*(t))*(0.1)+d2;
		t=t+0.1;
	}



else{


	
  	bird_x=u*cos(DEG2RAD(angle))*t-b*u*cos(DEG2RAD(angle));
	bird_h=(u*sin(DEG2RAD(angle))*t-(0.5)*(g)*t*t);
	t=t+0.1;
   }}
	

   else
   {
	
	if(itsdown!=1)
	{
		itsdown=1;
		t=0;
		offset=bird_x;
	}
	if(flag6==1)
	{
	mu=0.8;
	
	if(t<u*abs(cos(DEG2RAD(angle)))/mu)
	{
			t=t+0.1;
			bird_x=((u*cos(DEG2RAD(angle))*t-(0.5)*(mu1)*t*t))+offset;
	}
	else
	{	
		Lifes=Lifes+1;
		if(Lifes<=5)
		Restart();
		
	}
	}
	else if(flag7==1)
	{
	//printf("SDGG");
	if(t<u*(0.7)*(abs(cos(DEG2RAD(angle))))/mu)
	{
			t=t+0.1;
			
			bird_x=(-(u*(0.7)*cos(DEG2RAD(angle))*t+(0.5)*(mu)*t*t))+offset;
	}
	else
	{	
		Lifes=Lifes+1;
		if(Lifes<=5)
		Restart();
		
	}
	}

	else if(flag8==1 or flag9==1)
	{
	if(t<u*(0.8)*(abs(cos(DEG2RAD(angle))))/mu)
	{
			t=t+0.1;
 		bird_x=(-(u*(0.8)*cos(DEG2RAD(angle))*t-(0.5)*(mu)*t*t))+offset;
	}
	else
	{	
		Lifes=Lifes+1;
		if(Lifes<=5)
		Restart();
		
	}
	}
	else
	{
	if(t<u*(abs(cos(DEG2RAD(angle))))/mu)
	{
			t=t+0.1;
			
				bird_x=(u*cos(DEG2RAD(angle*i))*t-(0.5)*(mu)*t*t)+offset;
	}	
	else
	{	
		Lifes=Lifes+1;
		if(Lifes<=5)
		Restart();
		
	}
	}
	}




}
 displayText(0, 0, 0,0, 0, 0,smds ) ;



 shape_rotation = shape_rotation + increments*shape_rot_dir*shape_rot_status;
 shape1_rotation = shape1_rotation + increments*shape1_rot_dir*shape1_rot_status;
 shape2_rotation = shape2_rotation + increments*shape2_rot_dir*shape2_rot_status;
 shape3_rotation = shape3_rotation + increments*shape3_rot_dir*shape3_rot_status;

 	glutSwapBuffers();





}

/* Executed when the program is idle (no I/O activity) */
void idle () {
    // OpenGL should never stop drawing
    // can draw the same scene or a modified scene
    draw (); // drawing same scene
}


/* Initialise glut window, I/O callbacks and the renderer to use */
/* Nothing to Edit here */
void initGLUT (int& argc, char** argv, int width, int height)
{
    // Init glut
    glutInit (&argc, argv);

    // Init glut window
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitContextVersion (3, 3); // Init GL 3.3
    glutInitContextFlags (GLUT_CORE_PROFILE); // Use Core profile - older functions are deprecated
    glutInitWindowSize (width, height);
    glutCreateWindow ("Sample OpenGL3.3 Application");

    // Initialize GLEW, Needed in Core profile
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        cout << "Error: Failed to initialise GLEW : "<< glewGetErrorString(err) << endl;
        exit (1);
    }

    // register glut callbacks
    glutKeyboardFunc (keyboardDown);
    glutKeyboardUpFunc (keyboardUp);

    glutSpecialFunc (keyboardSpecialDown);
    glutSpecialUpFunc (keyboardSpecialUp);

    glutMouseFunc (mouseClick);
    glutMotionFunc (mouseMotion);

    glutReshapeFunc (reshapeWindow);

    glutDisplayFunc (draw); // function to draw when active
    glutIdleFunc (idle); // function to draw when idle (no I/O activity)
    glutMouseWheelFunc(mouseWheel);
    glutIgnoreKeyRepeat (false); // Ignore keys held down
}

/* Process menu option 'op' */
void menu(int op)
{
    switch(op)
    {
        case 'Q':
        case 'q':
            exit(0);
    }
}

void addGLUTMenus ()
{
    // create sub menus
    int subMenu = glutCreateMenu (menu);
    glutAddMenuEntry ("Do Nothing", 0);
    glutAddMenuEntry ("Really Quit", 'q');

    // create main "middle click" menu
    glutCreateMenu (menu);
    glutAddSubMenu ("Sub Menu", subMenu);
    glutAddMenuEntry ("Quit", 'q');
    glutAttachMenu (GLUT_MIDDLE_BUTTON);
}


/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL (int width, int height)
{
		
	// Create the models
	 // Generate the VAO, VBOs, vertices data & copy into the array buffer

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "Sample_GL.vert", "Sample_GL.frag" );
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


	reshapeWindow (width, height);

	// Background color of the scene
	glClearColor (0.0f, 1.0f, 1.0f, 0.0f); // R, G, B, A
	glClearDepth (1.0f);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);

	createground ();// Generate the VAO, VBOs, vertices data & copy into the array buffer
	creategallon();
	createbird();
	creategallonhead();
createshape ();	
createshape1 ();	
createshape2 ();	
createshape3 ();
createimmovable();
createimmovable3();
createspeed();
createspeedhead();

	createtar();

	cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
	cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
	cout << "VERSION: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}






int main (int argc, char** argv)
{
	int width = 1500;
	int height = 900;

	
    initGLUT (argc, argv, width, height);
   // drawBitmapText("yoyo", 10000000, 1, 1, 0,1,1,1) ;

    addGLUTMenus ();

	initGL (width, height);

   glutMainLoop ();

    return 0;
}
