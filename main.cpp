/***************************************************************************/
/* Filename: PreTransformations.cpp                                        */
/* This application allows the user to generate a set of regular polygons, */
/* which the user can alter with respect to position, orientation, color,  */
/* and radius via various keyboard and mouse operations. All alterations   */
/* occur instantaneously.                                                  */
/***************************************************************************/

#include <GLUT/glut.h>			// Header File For Windows
#include <math.h>				// Header File For Math Library
#include <time.h>				// Header File For Accessing System Time
#include "SearchableStack.h"	// Header File For Searchable Stack Class
#include "RegularPolygon.h"		// Header File For Regular Polygon Class

#include "Graphics.h"

using namespace Graphics;


//////////////////////
// Global Constants //
//////////////////////
const GLint INIT_WINDOW_POSITION[2] = { 100, 100 };		// Original Window Offset. //
//const GLfloat PI_OVER_180           = 0.0174532925f;	// One Degree (In Radians). //
const GLfloat ROTATION_INCREMENT    = 30 * PI_OVER_180;	// Angle Associated With One Spin Keystroke. //

const int DEFAULT_NBR_VERTS = 3;						// Default Polygon = Triangle. //
const GLfloat DEFAULT_RADIUS = 0.3;						// Default Size = Medium. //
const GLfloat MIN_RADIUS = 0.05;						// Minimum Size = Tiny. //
const GLfloat MAX_RADIUS = 1.0;							// Maximum Size = Jumbo. //
const GLfloat RADIUS_INCREMENT = 0.1;					// Rate of Growth/Shrinkage. //
const GLfloat DEFAULT_POSITION[] = { 0.0, 0.0 };		// Default Location = Center. //
const GLfloat DEFAULT_ORIENTATION = 0.0;				// Default Spin = Zero. //
const GLfloat DEFAULT_COLOR[] = { 0.5, 0.5, 0.5 };		// Default Color = Dark Gray. //


/////////////////////////
// Function Prototypes //
/////////////////////////
void KeyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition);
void MouseClick(int btn, int btnState, int mouseXPosition, int mouseYPosition);
void MouseDrag(int mouseXPosition, int mouseYPosition);
void TimerFunction(int value);
void Display();
void ResizeWindow(GLsizei w, GLsizei h);

//////////////////////
// Global Variables //
//////////////////////
GLint currWindowSize[2] = { 700, 700 };		// Window size in pixels.   //
GLfloat windowWidth     = 2.0;				// Resized window width.    //
GLfloat windowHeight    = 2.0;				// Resized window height.   //

SearchableStack<Graphics::Polygon*> g_polygons;	// Current polygon list.    //
Graphics::Polygon* g_selected_polygon = NULL;
Point<> g_drag_offset;					// Offset between selected poly's center and mouse click position. //
Point<> g_clicked_point;


/* The main function: uses the OpenGL Utility Toolkit to set */
/* the window up to display the window and its contents.     */
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
	/* Set up the display window. */
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
    glutInitWindowPosition( INIT_WINDOW_POSITION[0], INIT_WINDOW_POSITION[1] );
	glutInitWindowSize( currWindowSize[0], currWindowSize[1] );
	glutCreateWindow( "INSTANTANEOUS VERSION >>> Create Polygons: 3-9; Spin: S/s; Resize: </>; Color: RGBCMY" );


	/* Specify the resizing, refreshing, and interactive routines. */
	glutReshapeFunc( ResizeWindow );
	glutDisplayFunc( Display );
	glutKeyboardFunc( KeyboardPress );
	glutMotionFunc( MouseDrag );
	glutMouseFunc( MouseClick );
	glutTimerFunc(50, TimerFunction, 1);
	glutMainLoop();
}


/* Function to react to the pressing of keyboard keys by the user: by     */
/* creating a new polygon with the same number of vertices as the pressed */
/* numerical value or by spinning/resizing/coloring the selected polygon. */
void KeyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition)
{
	//int newPolySize = 0;
	//GLfloat newColor[3];
  int sides = -1;
	switch(pressedKey)
	{
  case '3':
    sides = 3;
    break;

  case '4': 
    //sides = 4;
    g_polygons.getTop()->frontwards = false;
    break;

  case '5':
    //sides = 5;
    g_polygons.getTop()->frontwards = true;
    break;

  case '6':
    sides = 6;
    break;

  case '7':
    sides = 7;
    break;

  case '8':
    sides = 8;
    break;

  case '9':
    sides = 9;
    break;

  case 's':
    if( g_selected_polygon != NULL )
      g_selected_polygon->scale *= 1.1;
    break;

  case 'S':
    if( g_selected_polygon != NULL )
      g_selected_polygon->scale *= 0.9;
    break;
  }
		
  /*case 's': { 
					if (polySelected) 
						selectedPoly.setOrientation(selectedPoly.getOrientation() + ROTATION_INCREMENT); 
					break; 
				  }
		case 'S': { 
					if (polySelected) 
						selectedPoly.setOrientation(selectedPoly.getOrientation() - ROTATION_INCREMENT); 
					break;
				  }

		case 'b':
		case 'B': {newColor[0] = 0.1; newColor[1] = 0.1; newColor[2] = 0.9; selectedPoly.setColor(newColor); break;}
		case 'c':
		case 'C': {newColor[0] = 0.1; newColor[1] = 0.9; newColor[2] = 0.9; selectedPoly.setColor(newColor); break;}
		case 'g':
		case 'G': {newColor[0] = 0.1; newColor[1] = 0.9; newColor[2] = 0.1; selectedPoly.setColor(newColor); break;}
		case 'm':
		case 'M': {newColor[0] = 0.9; newColor[1] = 0.1; newColor[2] = 0.9; selectedPoly.setColor(newColor); break;}
		case 'r':
		case 'R': {newColor[0] = 0.9; newColor[1] = 0.1; newColor[2] = 0.1; selectedPoly.setColor(newColor); break;}
		case 'y':
		case 'Y': {newColor[0] = 0.9; newColor[1] = 0.9; newColor[2] = 0.1; selectedPoly.setColor(newColor); break;}
		case '<': {
					if (polySelected)
					{
						selectedPoly.setRadius(selectedPoly.getRadius() - RADIUS_INCREMENT);
						if (selectedPoly.getRadius() < MIN_RADIUS)
							selectedPoly.setRadius(MIN_RADIUS);
					}
					break;
				  }
		case '>': {
					if (polySelected)
					{
						selectedPoly.setRadius(selectedPoly.getRadius() + RADIUS_INCREMENT);
						if (selectedPoly.getRadius() > MAX_RADIUS)
							selectedPoly.setRadius(MAX_RADIUS);
					}
					break;
				  }
	}*/
	if (sides != -1)
    g_polygons.push( new Graphics::Polygon( sides ) );
}

bool polygon_click( Graphics::Polygon* polygon )
{
  if( polygon->hit_test( g_clicked_point ) )
  {
    // Removes the polygon from the stack
    g_polygons.removeCurrent();

    // Pushes the polygon onto the top of the stack
    g_polygons.push( polygon );

    // Creates a reference to the selected polygon
    g_selected_polygon = polygon;

    // Jumps out of the loop
    return( true );
  }

  return( false );
}

/* Function to react to the user's nouse-click by deselecting the selected polygon (if */
/* any) and selecting the front-most polygon (if any) that overlaps the clicked mouse  */
/* position. To prepare for possible polygon repositioning, the offset between the     */
/* selected polygon's center and the clicked mouse position is also calculated.        */
void MouseClick(int btn, int btnState, int mouse_x, int mouse_y)
{
  Point<> p;
  p.x = windowWidth * mouse_x / currWindowSize[0] - 0.5 * windowWidth;
	p.y = 0.5 * windowHeight - (windowHeight * mouse_y / currWindowSize[1]);

	if( (btn == GLUT_LEFT_BUTTON) && (btnState == GLUT_DOWN) )
	{
		g_selected_polygon = NULL;
    g_polygons.each( polygon_click );
	}

  if( g_selected_polygon != NULL )
	{
		//GLfloat currLocation[2];
		//selectedPoly.getPosition(currLocation);
		//selectedOffset[0] = currLocation[0] - x;
		//selectedOffset[1] = currLocation[1] - y;

    g_drag_offset = g_selected_polygon->location - p;
	}
}

/* In response to the user's dragging of the mouse, the selected */
/* polygon (if any) is placed in the mouse's current position.   */
void MouseDrag(int mouse_x, int mouse_y)
{
  Point<> p;
  p.x = windowWidth * mouse_x / currWindowSize[0] - 0.5 * windowWidth;
	p.y = 0.5 * windowHeight - (windowHeight * mouse_y / currWindowSize[1]);

  if ( g_selected_polygon != NULL )
	{
		//GLfloat newPosition[2];
		//newPosition[0] = selectedOffset[0] + x;
		//newPosition[1] = selectedOffset[1] + y;
		//selectedPoly.setPosition(newPosition);

    g_selected_polygon->location = g_drag_offset + p;
	}
}

/* Function to force a redisplay in a timed fashion, in order to ensure */
/* that any newly created or altered polygons are always on display.    */
void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}


/* Principal display routine: clears the frame buffer */
/* and draws the polygons within the window.          */

void draw_polygon( Graphics::Polygon* polygon )
{
  // If this polygon is the selected polygon,
  // pass true to the draw function, which draws
  // a border around the polygon
  polygon->draw( polygon == g_selected_polygon );
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

  g_polygons.each( draw_polygon, false );

	glutSwapBuffers();
	glFlush();
}


/* Window-reshaping routine, to scale the rendered scene according */
/* to the window dimensions, setting the global variables so the   */
/* mouse operations will correspond to mouse pointer positions.    */
void ResizeWindow(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	currWindowSize[0] = w;
	currWindowSize[1] = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
	{
		windowWidth = 2.0;
		windowHeight = 2.0 * (GLfloat)h / (GLfloat)w;
        glOrtho(-1.0, 1.0, -1.0 * (GLfloat)h / (GLfloat)w,
		         (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	}
    else
	{
		windowWidth = 2.0 * (GLfloat)w / (GLfloat)h;
		windowHeight = 2.0;
        glOrtho(-1.0 * (GLfloat)w / (GLfloat)h,
		         (GLfloat)w / (GLfloat)h, 
				-1.0, 1.0, -10.0, 10.0);
	}
    glMatrixMode(GL_MODELVIEW);
}