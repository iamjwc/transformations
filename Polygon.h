////////////////////////////////////////////////////////////////////////////////
// The definition and implementation of a 2D regular polygon class, including //
// functionality for rendering it as a solid, rendering it as an outline, and //
// determining (approximately) whether a given point is within its borders.   //
////////////////////////////////////////////////////////////////////////////////

#ifndef POLYGON_H

namespace Graphics
{
  class Polygon
  {
  public:
    int      sides;
    Point<>* points;
    Point<>  location;
    Vector2<float> spin;

    float    color[3];
    float    radius;
    float    scale;

    Polygon( int sides = 3 )
    {
      this->sides  = sides;

      this->radius = 1.0;
      this->scale  = 0;

      this->color[0] = 1;
      this->color[1] = 1;
      this->color[2] = 1;

      this->generate_shape();

      this->times = 100;
      this->scale_start = 0;
      this->counter = 0;

      this->frontwards = true;
    }

    bool frontwards;

    void draw( bool show_border = false)
    {
      //resize( Graphics::Animation<>::Quadratic::ease_in );

      //if(this->counter!= 175)
        this->scale = Graphics::Animation<>::Quadratic::dunno( this->scale, 1.0, 0.1, 1.0 );
//float t, T b, T c, int d

      // Move/rotate the canvas
      glTranslatef( this->location.x, this->location.y, 0 );
      glScalef( this->scale, this->scale, 0 );
      //glRotatef( this->rotation, 0, 0, 1);

      // Draw the black background first
      glColor3f( 0.5, 0.5, 0.5 );
      this->draw_points( GL_POLYGON );

      if( show_border )
      {
        glColor3fv( this->color );
        this->draw_points( GL_LINE_LOOP );
      }

      // Move back to origin
      glLoadIdentity();
    }

    void resize( void (*f)( float &current, float factor, float start, float end ) )
    {
      f( this->scale, 0.01, 1.0, 2.0 );
    }

    int times;
    float scale_start;
    int counter;

    /*void resize( bool (*f)( T &value, int &i, int n, T start, T change ) )
    {
      f( this->scale, this->counter, 100, 0.1, 1.0 );

      //if( this->counter < 100 )
      //{
      //  this->scale = f( this->counter, 0.5, 1.0, 100 );
      //  this->counter++;
      //}
    }*/

    void draw_points( GLenum mode = GL_LINE_LOOP )
    {
      glBegin( mode );
        for( int i = 0, n = this->sides; i < n; i++ )
          glVertex2f( this->points[i].x, this->points[i].y );
      glEnd();
    }

    bool hit_test( Point<> p )
    {
      return( true );
    }

    virtual void generate_shape()
    {
      float theta;
      this->points = new Point<>[this->sides];
      Vector2<float> v;

      for( int i = 0, n = this->sides; i < n; i++ )
      {
        theta           = (360 / sides) * i * PI_OVER_180;
        v               = Vector2<float>::from_magnitude_and_direction( this->radius, theta);
        this->points[i] = v.p;
      }
    }

  };
}
/*
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
*/
#define POLYGON_H
#endif