////////////////////////////////////////////////////////////////////////////////
// The definition and implementation of a 2D regular polygon class, including //
// functionality for rendering it as a solid, rendering it as an outline, and //
// determining (approximately) whether a given point is within its borders.   //
////////////////////////////////////////////////////////////////////////////////

#ifndef REGULAR_POLYGON_H

const GLfloat ONE_DEGREE      = 0.0174532925f;	// One Degree (In Radians). //
const GLfloat BORDER_COLOR[3] = {1.0,1.0,1.0};	// Selected Polygon's Border Color. //

class RegularPolygon
{
	public:
		//Constructors
		RegularPolygon();
		RegularPolygon(const RegularPolygon &rp);
		RegularPolygon(int size, GLfloat rad, const GLfloat pos[], GLfloat orientation, const GLfloat hue[]);

		//Accessors
		int getNumberVertices() {return nbrVerts;}
		void setNumberVertices(int n) {nbrVerts = n;}
		void getColor(GLfloat c[]) {for (int i = 0; i <= 2; i++) c[i] = clr[i];}
		void setColor(GLfloat c[]) {for (int i = 0; i <= 2; i++) clr[i] = c[i];}
		GLfloat getRadius() {return radius;}
		void setRadius(GLfloat rad) {radius = rad;}
		void getPosition(GLfloat pos[]) {pos[0] = x; pos[1] = y;}
		void setPosition(GLfloat pos[]) {x = pos[0]; y = pos[1];}
		GLfloat getOrientation() {return spin;}
		void setOrientation(GLfloat orient) {spin = orient;}

		//Member Functions
		void draw();
		void drawBorder();
		bool isInteriorPoint(GLfloat ptX, GLfloat ptY);

	protected:
		//Data Members
		GLint   nbrVerts;
		GLfloat clr[3];
		GLfloat radius;
		GLfloat x;
		GLfloat y;
		GLfloat spin;
};

//Default Constructor (stationary triangle)
RegularPolygon::RegularPolygon()
{
	nbrVerts = 3;
	clr[0] = clr[1] = clr[2] = 0.0;
	radius = 0.0;
	x = y = 0.0;
	spin = 0.0;
}

//Copy Constructor
RegularPolygon::RegularPolygon(const RegularPolygon &rp)
{
	nbrVerts = rp.nbrVerts;
	for (int i = 0; i <= 2; i++)
		clr[i] = rp.clr[i];
	radius = rp.radius;
	x = rp.x;
	y = rp.y;
	spin = rp.spin;
}

//Initializing Constructor
RegularPolygon::RegularPolygon(int size, GLfloat rad, const GLfloat pos[], 
							   GLfloat orientation, const GLfloat hue[])
{
	nbrVerts = size;
	for (int i = 0; i <= 2; i++)
		clr[i] = hue[i];
	radius = rad;
	x = pos[0];
	y = pos[1];
	spin = orientation;
}

//Render the polygon as a solid.
void RegularPolygon::draw()
{
	GLfloat theta;	
	glColor3fv(clr);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y);
		for (int j = 0; j < nbrVerts; j++)
		{
			theta = spin + 360 * j *  ONE_DEGREE / nbrVerts;
			glVertex2f(x + radius * cos(theta), y + radius * sin(theta));
			theta = spin + 360 * (j + 1) * ONE_DEGREE / nbrVerts;
			glVertex2f(x + radius * cos(theta), y + radius * sin(theta));
		}
	glEnd();
}

// Render the outline of the polygon.
void RegularPolygon::drawBorder()
{
	GLfloat theta;
	glLineWidth(3);
	glColor3fv(BORDER_COLOR);
	glBegin(GL_LINE_LOOP);
		for (int j = 0; j < nbrVerts; j++)
		{
			theta = spin + 360 * j *  ONE_DEGREE / nbrVerts;
			glVertex2f(x + radius * cos(theta), y + radius * sin(theta));
			theta = spin + 360 * (j + 1) * ONE_DEGREE / nbrVerts;
			glVertex2f(x + radius * cos(theta), y + radius * sin(theta));
		}
	glEnd();			
}

// APPROXIMATELY determine whether the parameterized point is inside the
// polygon. To accomplish this, merely check if the distance between the
// point and the center of the polygon is less than the polygon's radius.
bool RegularPolygon::isInteriorPoint(GLfloat ptX, GLfloat ptY)
{
	return ( sqrt( pow(ptX - x, 2) + pow(ptY - y, 2) ) < radius );
}

#define REGULAR_POLYGON_H
#endif