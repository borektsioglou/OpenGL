#include <stdio.h>     // - Just for some ASCII messages
#include <time.h>
#include <cstdlib> 
#include <string.h>
#include <iostream>
#include <fstream>
#include "gl/glut.h"   // - An interface and windows 
                       //   management library
#include "visuals.h"   // Header file for our OpenGL functions
#include <math.h>


static bool model1 = 1;
static bool model2 = 0;
static bool model3 = 0;
static bool model4 = 0;

static float tx = 0.0;							// spaceship translate and rotate variables
static float ty = 0.0;
static float roty = 0.0;
static float rothelix = 0.0;					// helixes rotate variable

static bool strifeleft = 0;
static bool striferight = 0;

static float srotx = 0.0;						// camera rotate variables
static float sroty = 0.0;
static float srotz = 0.0;

static float outersunsize = 18;					// transparent sun size
static float transparency  = 0;					// glowing transparency
static bool glow = 1;							// glowing toggle variable

static bool pause = 0;							// pause toggle variable
static int score = 0;
static bool count = 0;
static float backfirey =-30;


static float firez = 0;
static float firex = 0;
static float firey = 0;
static float fire = 0;

static bool missile = 0;

static struct starposition explo[42];
static bool createexplosion = 0;
static bool explosiondone = 0;
static bool destroy = 0;
static float destroyx ;
static float destroyy ;
static float destroyz ;

static float missilex = 20;
static float missiley = -10;
static float missilez = 10;
static float missilerotx = 0;

static struct starposition starpos[50];
static bool createstars = 1;

model asteroid;	
static bool collision = 0;
static float asterx ;
static float astery ;
static float asterz = 300;
static float asterotx = 0.0;
static float asteroty = 0.0;
static float asterotz = 0.0;

double size=0,r=0,g=0,b=0,destroyr=0,destroyg=0,destroyb=0;	
	
using namespace std;


void spaceship()
{
	glPushMatrix();		
	
		glTranslatef(tx,ty,0);		
		glRotatef(-90,1,0,0);			
		
		glRotatef(roty,0,1,0);

		 // Body

		glPushMatrix();
			glColor3f(0.85, 0.85, 0.10);		 					
			glScalef(2,5.5,2);
			glutSolidSphere(8,50,50);
		glPopMatrix(); 

		// Wings

		glPushMatrix();
			glColor3f(1.0, 0.0, 0.0);
			glTranslatef(0,-10,0);
			glRotatef(90,0,0,1);
			glScalef(2,9,1.5);
			glutSolidSphere(6,50,50);								
		glPopMatrix(); 

		// Tail Upper Body
		
		glPushMatrix();
			glTranslatef(0,-28,25);
			glRotatef(90,0,0,1);
			glRotatef(45,0,1,0);
			glColor3f(1.0, 0.0, 0.0);
			glScalef(3,13,3.5);
			glutSolidSphere(2,50,50);								
		glPopMatrix(); 

		// Tail Lower Body
	
		glPushMatrix();
			glTranslatef(0,-22,25);			
			glRotatef(120,1,0,0);
			glColor3f(0.0, 0.0, 1.0);
			glScalef(3.5,7,3);
			glutSolidSphere(2,50,50);
		glPopMatrix(); 

		//right helix				
			
		glPushMatrix();							//horizontal part
			glTranslatef(37,2.5,0);
			glRotatef(rothelix,0,1,0);
			glRotatef(90,1,0,0);
			glColor3f(0.9, 0.91, 0.98);
			glScalef(2,6,2);
			glutSolidSphere(2,50,50);
		glPopMatrix(); 

			
		glPushMatrix();							//vertical part
			glTranslatef(37,2.5,0);
			glRotatef(rothelix,0,1,0);
			glRotatef(90,0,0,1);
			glColor3f(0.9, 0.91, 0.98);
			glScalef(2,6,2);
			glutSolidSphere(2,50,50);
		glPopMatrix(); 


		//left helix
			
		glPushMatrix();							//horizontal part
			glTranslatef(-37,2.5,0);
			glRotatef(rothelix,0,1,0);
			glRotatef(90,1,0,0);
			glColor3f(0.9, 0.91, 0.98);
			glScalef(2,6,2);
			glutSolidSphere(2,50,50);
		glPopMatrix(); 

			
		glPushMatrix();
			glTranslatef(-37,2.5,0);			//vertical part	
			glRotatef(rothelix,0,1,0);
			glRotatef(90,0,0,1);
			glColor3f(0.9, 0.91, 0.98);
			glScalef(2,6,2);
			glutSolidSphere(2,50,50);
		glPopMatrix(); 		
		
		// left helix base

		glPushMatrix();
			glTranslatef(37,-4,0);				
			glColor3f(0,0, 1);
			glScalef(3,3,3);
			glutSolidSphere(2,50,50);
		glPopMatrix();

		// right helix base

		glPushMatrix();
			glTranslatef(-37,-4,0);				
			glColor3f(0,0, 1);
			glScalef(3,3,3);
			glutSolidSphere(2,50,50);
		glPopMatrix();

		// spaceship driver

		glPushMatrix();

			//face

			glPushMatrix();
				glColor3f(1, 1, 1);
				glTranslatef(0,25,16);
				glScalef(1,1,1);
				glutSolidSphere(4,50,50);
			glPopMatrix();

			// left eye

			glPushMatrix();
				glColor3f(0, 0, 0);
				glTranslatef(-2,28,16);			
				glutSolidSphere(1.2,50,50);
			glPopMatrix();

			// right eye

			glPushMatrix();
				glColor3f(0, 0, 0);
				glTranslatef(2,28,16);			
				glutSolidSphere(1.2,50,50);
			glPopMatrix();

		glPopMatrix();

		//cockpit 

		glPushMatrix();
			glTranslatef(0,25,12);
			glColor4f(1.0,1.0, 1.0,0.4);
			glutSolidSphere(9,50,50);
		glPopMatrix();

		// I AM FIRIN MY LAZAAAH

		// central cube
		if(model1 == 0){
			glPushMatrix();
				glTranslatef(0,30,-15);
				glColor3f(0,0,1.0);
				glutSolidCube(8);
			glPopMatrix();	

			// right cube

			glPushMatrix();
				glTranslatef(7,25,-15);
				glColor3f(0,0,1.0);
				glutSolidCube(8);
			glPopMatrix();	

			// left cube

			glPushMatrix();
				glTranslatef(-7,25,-15);
				glColor3f(0,0,1.0);
				glutSolidCube(8);
			glPopMatrix();	

			// gun hole

			glPushMatrix();
				glTranslatef(0,34,-15);
				glColor3f(1,1,1);
				glutSolidSphere(2,50,50);
			glPopMatrix();	

			
		}


		if(model3 || model4){
			// left eksatmisi

			glPushMatrix();
				glScalef(2,1,2);
				glTranslatef(5,-45,0);
				glColor3f(0,0,0);			
				glutSolidSphere(4,50,50);
			glPopMatrix();

			glPushMatrix();
				glScalef(2,1,2);
				glTranslatef(5,-49,0);
				glColor3f(1,1,1);
				glutSolidSphere(2,50,50);
			glPopMatrix();

			glPushMatrix();			
				glTranslatef(10,backfirey,0);
				glScalef(1,9,1);
				glColor4f(1,0,0,0.3);
				glutSolidSphere(1,50,50);
			glPopMatrix();

			// right eksatmisi

			glPushMatrix();
				glScalef(2,1,2);
				glTranslatef(-5,-45,0);
				glColor3f(0,0,0);
				glutSolidSphere(4,50,50);
			glPopMatrix();

			glPushMatrix();
				glScalef(2,1,2);
				glTranslatef(-5,-49,0);
				glColor3f(1,1,1);
				glutSolidSphere(2,50,50);
			glPopMatrix();

			glPushMatrix();			
				glTranslatef(-10,backfirey,0);
				glScalef(1,9,1);
				glColor4f(1,0,0,0.3);
				glutSolidSphere(1,50,50);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-13,38,-1);
				glScalef(0.05,0.05,0.05);
				glRotatef(-97,0,0,1);
				glRotatef(85,1,0,0);
				glColor3f(0,0,0);
				char *str = "Apollo 13";
				for (int i=0;i<strlen(str);i++)
				  glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
			glPopMatrix();		

		}

		
		if(model4){							
			// black ring around spaceship

			glPushMatrix();			
				glTranslatef(0,-20,0);
				glColor3f(0,0,0);
				glutSolidSphere(15,50,50);
			glPopMatrix();
			if(missile == 0){				
				missilelaunch();		// when missile is idle
			}
		}
	glPopMatrix();

	if(model4 && missile == 1){								// when missile is launching (so that spaceship translation doesnt move the missile too)
		missilelaunch();
	}
}

void sun()
{	
	glPushMatrix();
		glTranslatef(320,170,-460);	
		glScalef(2,2,2);

		//inner sun sphere

		glPushMatrix();			
			glColor3f(1,1, 0);
			glutSolidSphere(16,50,50);
		glPopMatrix();

		//outer sun sphere

		glPushMatrix();			
			glColor4f(1,0, 0,transparency);
			glutSolidSphere(outersunsize,50,50);
		glPopMatrix();
	glPopMatrix();
}

void stars(){
	for(int i=0;i<50;i++){		
		glPushMatrix();	
			if(starpos[i].z > 200 || starpos[i].x > abs(220) || createstars == 1 ){		
				starpos[i].x = rand()%440 - 220;
				starpos[i].y = rand()%220 - 110;
				starpos[i].z = rand()%700 - 350;
			}
			
			glTranslatef(starpos[i].x,starpos[i].y,starpos[i].z);			
			glColor3f(1,1,1);
			glutSolidSphere(0.4,50,50);
		glPopMatrix();
	}

	if(createstars == 1){
		createstars = 0;
	}

}

void missilelaunch()
{
	glPushMatrix();									// heat seeking missile!
		if(model4 && missile == 1){
			glRotatef(-90,1,0,0);
		}

		glTranslatef(missilex,missiley,missilez);			

		// body

		glPushMatrix();
			glScalef(0.8,2,0.8);			
			glColor3f(0.7,0.7,0.7);
			glutSolidSphere(4,50,50);
		glPopMatrix();
			
		// three wings

		glPushMatrix();
			glTranslatef(0,-6,3);
			glColor3f(1,0,0);
			glScalef(1,5,1);
			glutSolidSphere(1,50,50);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-3,-6,-1);
			glColor3f(1,0,0);
			glScalef(1,5,1);
			glutSolidSphere(1,50,50);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(3,-6,-1);
			glColor3f(1,0,0);
			glScalef(1,5,1);
			glutSolidSphere(1,50,50);
		glPopMatrix();		
				
		// nose

		glPushMatrix();
			glTranslatef(0,5,0);
			glColor3f(0,0,1);
			glScalef(1,4,1);
			glutSolidSphere(2,50,50);
		glPopMatrix(); 			

	glPopMatrix();
}

void bullet()
{	
	glPushMatrix();			
		glTranslatef(firex,firey,firez);
		glScalef(1,1,7);	
		glColor3f(0,1,0);
		glutSolidSphere(2,50,50);
	glPopMatrix();
}

void explosion()
{
	
	for(int i=0;i<42;i++){		
		glPushMatrix();	
			if(	createexplosion == 1){
				explo[i].x = rand()%10 + destroyx;
				explo[i].y = rand()%10 + destroyy;
				explo[i].z = rand()%10 + destroyz;				
			}
			if(explo[i].z < -700 || explo[i].z > 300 || explo[i].x < -220 || explo[i].x > 220 || explo[i].y < -120 || explo[i].y > 120){
				explosiondone++;
			}
			if(explosiondone == 42){
				explosiondone = 0;
				destroy = 0;
				createexplosion = 0;
				break;
			}
			glTranslatef(explo[i].x,explo[i].y,explo[i].z);			
			glColor3f(destroyr,destroyg,destroyb);
			glutSolidSphere(2,50,50);
		glPopMatrix();
	}
	createexplosion = 0;
}


void Render()
{    
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();  	
	
	glTranslatef(0,0,-200);					// scene setting
	glRotatef(srotx,1,0,0);					// camera settings
	glRotatef(sroty,0,1,0);
	glRotatef(srotz,0,0,1);
	

	sun();	
	bullet();
	stars();
	spaceship();	

	DisplayModel(asteroid);
	
	if(destroy == 1){
		explosion();	
	}

	if(collision == 1){
		text("Spaceship Collapsed! Press Esc to exit!",0.05);
		pause = 1;
	}
	glPushMatrix();
		glTranslatef(-80,200,-300);
		glScalef(0.3,0.3,0.3);		
		glColor3f(1,1,1);
		char buffer[15];
		sprintf(buffer,"Score: %d",score);
		for (int i=0;i<strlen(buffer);i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN,buffer[i]);
	glPopMatrix();	

	glutSwapBuffers();
}

//-----------------------------------------------------------

void Keyboard(unsigned char key,int x,int y)
{	

	key = tolower(key);
	switch(key)
	{
	
	case '1' : srotx-=5;					// rotate camera on x
		break;
	case '2' : srotx+=5;
		break;
	case '3' : sroty+=5;					// rotate camera on y
		break;
	case '4' : sroty-=5;
		break;
	case '5' : srotz+=5;					// rotate camera on z
		break;
	case '6' : srotz-=5;
		break;
	
	case 'w' : 
		if(ty < 120 && pause == 0)
			ty+=7; 			
		break;

	case 'a' : 

		if(tx > -220 && pause == 0)
			tx-=7; 	
		if(roty > -40 && pause == 0)
			roty-=5;		
		break;

	case 's' : 
		if(ty > -120 && pause == 0)
			ty-=7;	
		break;

	case 'd' : 
		if(tx < 220 && pause == 0)
			tx+=7;	
		if(roty < 40 && pause == 0)
			roty+=5;		
		break;

	case 'q' :																					// strife left										
		if(pause == 0 && striferight == 0 && (model3 || model4)){
			strifeleft = 1;
		}
		break;

	case 'e':																					// strife right
		if(pause == 0 && strifeleft == 0 && (model3 || model4)){									
			striferight = 1;	
		}
		break;

	case 27 :  delete (asteroid.faces); delete (asteroid.points); exit(0);					// quit game if esc is pressed
		break;	

	case 'f' :	if(fire == 0 && pause == 0 && model1 == 0) { fire = 1; firey = ty -15;}			// fire!		
		break;

	case 'c' :	if(missile == 0 && pause == 0 && model4 == 1) { missile = 1; missilex = tx+20;	missilez = ty;	}		// missile launch!		
		break;

	case 'p' : if(collision == 0){ pause = 1-pause;	}			
		break;	

	case 'r' : srotx = sroty = srotz = roty = tx = ty = 0; asterz = 300;			// reset button
			   fire = collision = pause = score = count = destroy = strifeleft = striferight = 0;
		break;

	default : 		
		break;
	}
	
	glutPostRedisplay();
	
}

void AsteroidAttack()
{	
	asterz+=1;										// translate asteroid towards spaceship
	asterotx+=0.7;										// rotate asteroid
	asteroty+=0.7;
	asterotz+=0.7;

	if(asterz > 50 && count == 1){ score ++; count = 0;}

	if(asterz > 400 || asterz < -400 ){									// new asteroid incoming
		astery = rand()%100 - 50;
		asterx = rand()%200 - 100;
		asterz = -400;
		size = rand()%25 + 10;		
		size = size/1000;
		r = rand()%1000;								// new color
		g = rand()%1000;
		b = rand()%1000;
		r = r/1000;
		g = g/1000;
		b = b/1000;
		count = 1;
	}
}

void SunGlow()
{
	if(glow == 1){
		transparency+=0.001;
	}else{
		transparency-=0.001;
	}

	if(transparency > 0.3){
		glow = 0;
	}

	if(transparency < 0){
		glow = 1;
		outersunsize = rand()%6 + 18;
	}
}

void StarsGlow()
{	
	for(int i=0;i<30;i++){
		starpos[i].z+=0.1;		
	}
	for(int i=30;i<40;i++){
		starpos[i].x-=0.1;		
	}
	for(int i=40;i<50;i++){
		starpos[i].x+=0.1;		
	}	
}
void Strife(){
	if(strifeleft == 1){
		roty -= 7;
		if(tx > -220){
			tx-=2;				
		}
		if(roty <= -360){
			roty = 0;
			strifeleft = 0;
		}
	}
	if(striferight == 1){
		roty += 7;
		if(tx < 220){
			tx+=2;				
		}
		if(roty >= 360){
			roty = 0;
			striferight = 0;
		}
	}
}
void Dodge()
{
	if(roty < 0 && strifeleft == 0 && striferight == 0){
		roty+=0.7;	
	}

	if(roty > 0 && strifeleft == 0 && striferight == 0){
		roty-=0.7;
	}

	if(roty < -40 && strifeleft == 0 && striferight == 0){
		roty = -40;		
	}

	if(roty > 40 && strifeleft == 0 && striferight == 0){
		roty = 40;
	}
}

void Collision()
{	
	int x=0,y=0,z=0;		
	float approx = 400*size;
	

	if(asterz >= -(44+approx) && asterz <= 0){
	   if( fabsf(asterx - tx) <= 16 + approx) {
			x = 1;
	   }
	   if( fabsf(astery - ty) <= 16 + approx){
			y = 1;
	   }
	   z = 1;
	}
	
	if(asterz >= 0 && asterz <= 10){
	   if( fabsf(asterx - tx) <= 54 + approx){
			x = 1;
	   }
	   if( fabsf(astery - ty) <= 9 + approx){
			y = 1;
	   }
	   z = 1;
	 }

	 if(asterz >= 10 && asterz <= 54){
	   if( fabsf(asterx - tx) <= 26 + approx){
			x = 1;
	   }
	   if( fabsf(astery - ty) <= 33 + approx){
			y = 1;
	   }
	   z = 1;
	 }	

	if(x == 1 && y == 1 && z == 1){
		collision = 1;
	}
	
}

void Fire()
{
	if(fire == 1){
		firez-=15;
		if(firez < -600){
			fire = 0;
		}

		if(fabsf(astery - firey)<=20 && fabsf(asterx - firex) <= 20 && fabsf(asterz - firez) <= 15){
			asterz = 300;			
		}

	}else{
		firex = tx;
		firey = ty;
		firez = -30;
	}
}
void AsteroidExplosion(){
		
	explo[0].x-=1;	
	explo[1].x+=1;		
	explo[2].y-=1;				
	explo[3].y+=1;
	explo[4].z+=1;
	explo[5].z+=1;

	explo[6].x-=1;	 explo[6].y-=1;
	explo[7].x-=1;	 explo[7].y+=1;	
	explo[8].x+=1;	 explo[8].y-=1;	
	explo[9].x+=1;	 explo[9].y+=1;	

	explo[10].x-=1;	 explo[10].z-=1;
	explo[11].x-=1;	 explo[11].z+=1;	
	explo[12].x+=1;	 explo[12].z-=1;	
	explo[13].x+=1;	 explo[13].z+=1;

	explo[14].y-=1;	 explo[14].z-=1;
	explo[15].y-=1;	 explo[15].z+=1;	
	explo[16].y+=1;	 explo[16].z-=1;	
	explo[17].y+=1;	 explo[17].z+=1;

	explo[18].x-=1;	 explo[18].y-=1;explo[18].z-=1;
	explo[19].x-=1;	 explo[19].y+=1;explo[19].z-=1;	
	explo[20].x+=1;	 explo[20].y-=1;explo[20].z-=1;	
	explo[21].x+=1;	 explo[21].y+=1;explo[21].z-=1;

	explo[22].x-=1;	 explo[22].y-=1;explo[22].z+=1;
	explo[23].x-=1;	 explo[23].y+=1;explo[23].z+=1;	
	explo[24].x+=1;	 explo[24].y-=1;explo[24].z+=1;	
	explo[25].x+=1;	 explo[25].y+=1;explo[25].z+=1;	

	explo[26].x-=1;	 explo[26].z-=1;explo[26].y-=1;
	explo[27].x-=1;	 explo[27].z+=1;explo[27].y-=1;
	explo[28].x+=1;	 explo[28].z-=1;explo[28].y-=1;	
	explo[29].x+=1;	 explo[29].z+=1;explo[29].y-=1;

	explo[30].x-=1;	 explo[30].z-=1;explo[30].y+=1;
	explo[31].x-=1;	 explo[31].z+=1;explo[31].y+=1;
	explo[32].x+=1;	 explo[32].z-=1;explo[32].y+=1;
	explo[33].x+=1;	 explo[33].z+=1;explo[33].y+=1;

	explo[34].y-=1;	 explo[34].z-=1;explo[34].x+=1;	
	explo[35].y-=1;	 explo[35].z+=1;explo[35].x+=1;		
	explo[36].y+=1;	 explo[36].z-=1;explo[36].x+=1;		
	explo[37].y+=1;	 explo[37].z+=1;explo[37].x+=1;	

	explo[38].y-=1;	 explo[38].z-=1;explo[38].x-=1;
	explo[39].y-=1;	 explo[39].z+=1;explo[39].x-=1;
	explo[40].y+=1;	 explo[40].z-=1;explo[40].x-=1;	
	explo[41].y+=1;	 explo[41].z+=1;explo[41].x-=1;

}			
	
void MissileLaunch()
{
	if(missile == 1){

		if(fabsf(asterx - missilex) > 1){
			if(asterx > missilex){
				missilex+=2;
			}else{
				missilex-=2;
			}
		}
		if(fabsf(astery - missilez) > 1){
			if(astery > missilez){
				missilez+=2;
			}else{
				missilez-=2;
			}
		}

		missiley+=5;

		if(fabsf(astery - missilez)<=15 && fabsf(asterx - missilex) <= 15 && fabsf(asterz + missiley) <= 10){
			destroyx = asterx;
			destroyy = astery;
			destroyz = asterz;
			destroyr = r;
			destroyg = g;
			destroyb = b;
			score++;
			asterz = -700;		
			destroy = 1;
			createexplosion = 1;			
			missile = 0;
			missilex = 20;
			missiley = -10;
			missilez = 10;	
		}

		if(missiley > 600){
			missile = 0;
			missilex = 20;
			missiley = -10;
			missilez = 10;			
		}
	}
}


void Idle()
{
	if(pause == 0){

		rothelix+=1;

		backfirey -= 20;
		if(backfirey < -400){
			backfirey = -20;
		}

		Strife();
		Fire();		
		Dodge();
		SunGlow();	
		StarsGlow();
		AsteroidAttack();
		AsteroidExplosion();	
		Collision();
		MissileLaunch();
	}
	
    glutPostRedisplay(); 
}




//-----------------------------------------------------------

void Resize(int w, int h)
{ 
	// define the visible area of the window ( in pixels )
	if (h==0) h=1;
	glViewport(0,0,w,h); 

	// Setup viewing volume

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();

	float aspect = (float)w/(float)h;             /// aspect ratio
	gluPerspective(60.0, aspect, 1.0, 800.0);
}


//-----------------------------------------------------------

void Setup()  
{ 
	ReadFile(&asteroid);

	glShadeModel( GL_SMOOTH );

	glEnable(GL_DEPTH_TEST);
	glDepthFunc( GL_LEQUAL );  
	glClearDepth(1); 	
	
    
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	//Set up light source
	GLfloat light_position[] = { 320, 170.0, -600 , 1.0 };
	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.7, 0.7, 0.7, 1.0 };	

	   
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
	glLightfv( GL_LIGHT0, GL_POSITION, light_position);
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0);

	glClearColor(0.0f,0.0f,0.0f,1.0f);
}


void ReadFile(model *asteroid)
{
	ifstream file;                   // Open the file for reading OBJINFO.TXT

	if (file.fail()) 
		exit(1);

	char buffer[256],c;
	

	if (file.fail()) 
		exit(1);

    int vnumber = 0,fnumber=0;
	int i=0,j=0,f1;
	
	file.open("asteroid.obj");
	
	while(file.getline(buffer,256)) {	    
		if(buffer[0] == 'v'){
			if(buffer[1] != 'n'){			
				vnumber++;
			}
		}
		if(buffer[0] == 'f'){
			fnumber++;
		}
	}

	file.close();	

	asteroid->points = new point[vnumber];
	asteroid->faces = new face[fnumber];
	asteroid->nfaces = fnumber;
	asteroid->nvertices = vnumber;
	
	file.clear();
	file.open("asteroid.obj");

	while(file.get(c)) {	 
					     
		if(c == 'v'){
			 
	        file.get(c);
	 	    if(c != 'n'){	 	
	 		    file >> asteroid->points[i].x;
				file >> asteroid->points[i].y;
				file >> asteroid->points[i].z;			
				i++;
		    }
			continue;		
		}
		
		if(c == 'f'){
	      
	        file >> asteroid->faces[j].vtx[0];
			file.get(c); file.get(c); 
			file >> asteroid->faces[j].vtx[3];
			
		    file >> asteroid->faces[j].vtx[1];
			file.get(c); file.get(c); 
			file >> asteroid->faces[j].vtx[4];
			
		    file >> asteroid->faces[j].vtx[2];
			file.get(c); file.get(c); 
			file >> asteroid->faces[j].vtx[5];
 		    j++;
	 		continue; 		    
		}
 		if(c == '#' || c == ' '){		
			file.getline(buffer, 256);
	        continue;
	    }
	 				    
	}		
	
   file.close();

	 file.clear();
	file.open("asteroid.obj");
	i=0;	
	while(file.get(c)) {	 
					     
		if(c == 'v'){
			 
	        file.get(c);
	 	    if(c == 'n'){	 	
	 		    file >> asteroid->points[i].vnx;
				file >> asteroid->points[i].vny;
				file >> asteroid->points[i].vnz;			
				i++;
		    }
			continue;		
		}		
		
 		if(c == '#' || c == ' '){		
			file.getline(buffer, 256);
	        continue;
	    }
	 				    
	}		
	
   file.close();


 
   
}


void DisplayModel(model asteroid)
{	
	glPushMatrix();
	glColor3f(r,g,b);
	glTranslatef(asterx,astery,asterz);
	glRotatef(asterotx,1,0,0);
	glRotatef(asteroty,0,1,0);	
	glRotatef(asterotz,0,0,1);

	glScalef(size,size,size);

	glBegin(GL_TRIANGLES);
	

	for (int i = 0; i < asteroid.nfaces; i++)
	{		
		glVertex3f(asteroid.points[asteroid.faces[i].vtx[0]-1].x,asteroid.points[asteroid.faces[i].vtx[0]-1].y,asteroid.points[asteroid.faces[i].vtx[0]-1].z);
		glVertex3f(asteroid.points[asteroid.faces[i].vtx[1]-1].x,asteroid.points[asteroid.faces[i].vtx[1]-1].y,asteroid.points[asteroid.faces[i].vtx[1]-1].z);
		glVertex3f(asteroid.points[asteroid.faces[i].vtx[2]-1].x,asteroid.points[asteroid.faces[i].vtx[2]-1].y,asteroid.points[asteroid.faces[i].vtx[2]-1].z);
		glNormal3f(asteroid.points[asteroid.faces[i].vtx[3]-1].vnx,asteroid.points[asteroid.faces[i].vtx[3]-1].vny,asteroid.points[asteroid.faces[i].vtx[3]-1].vnz);
		glNormal3f(asteroid.points[asteroid.faces[i].vtx[4]-1].vnx,asteroid.points[asteroid.faces[i].vtx[4]-1].vny,asteroid.points[asteroid.faces[i].vtx[4]-1].vnz);
		glNormal3f(asteroid.points[asteroid.faces[i].vtx[5]-1].vnx,asteroid.points[asteroid.faces[i].vtx[5]-1].vny,asteroid.points[asteroid.faces[i].vtx[5]-1].vnz);

	}

	glEnd();
	glPopMatrix();

}

void MenuSelect(int choice)
{
	switch (choice) {
		case MODEL1:
			 model1 = 1;
			 model2 = model3 = model4 = 0;
			 break;
		case MODEL2 : 
			 model2 = 1;
			 model1 = model3 = model4 = 0;
			 break;
		case MODEL3 : 
			model3 = 1;
			model1 = model2 = model4 = 0;
			break;	
		case MODEL4 :
			model4 = 1;
			model1 = model2 = model3 = 0;
	}

}

void text(const char *str,float size)
{

	glPushMatrix();
		glTranslatef(-65,40,50);
		glScalef(size,size,size);
		glColor3f(1,1,1);

		for (int i=0;i<strlen(str);i++)
		  glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
	glPopMatrix();

}
