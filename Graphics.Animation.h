#include <cmath>
#include <iostream>

using namespace std;

namespace Graphics
{
  template< typename T = float >
  class Animation
  {
  public:

    static bool tween( T &value, int &i, int n, T start, T change )
    {
      if( i >= n ) return(false);

      value = start + ( (T(i)/n) * change );
      i++;

      return( true );
    }

    class Quadratic
    {
    public:

/*// quadratic easing out - decelerating to zero velocity
Math.easeOutQuad = function (t, b, c, d) {
	return -c *(t/=d)*(t-2) + b;
};

// quadratic easing in/out - acceleration until halfway, then deceleration
Math.easeInOutQuad = function (t, b, c, d) {
	if ((t/=d/2) < 1) return c/2*t*t + b;
	return -c/2 * ((--t)*(t-2) - 1) + b;
};*/


      static bool ease_in( T &value, int &i, int n, T start, T change )
      {
        if( i >= n ) return(false);

        value = ( pow( ( T(i)/n ), 2) * change ) + start;
        i++;

        return( true );
      }

      static T easeInQuad( int i, T starting_value, T change, int count) {

        return (change * pow( T(i)/count, 3 ) + starting_value);
      }

      static bool ease_out( T &value, int &i, int n, T start, T change )
      {
        if( i >= n ) return(false);

        value = ( pow( ( 1 - T(i)/n ), 2) * -change ) + start;
        i++;

        return( true );
      }

      static bool ease_in_out( T &value, int &i, int n, T start, T change )
      {
        if( i >= n ) return(false);

        if( i < n/2)
          ease_in( value, i, n/2, start, change/2);
        else
          ease_out( value, i, n, start, change/2);

        cout << value << endl;

        i++;

        return( true );
      }

      static bool dunno( T &value, T start, T change, T factor )
      {
        value += (value/(start+change)) * factor;

        return( Animation::value_checker( value, start, change ) );
      }

      static bool dunno_backwards( T &value, T start, T change, T factor )
      {
        value -= (1-(value/(start+change))) * factor;

        return( Animation::value_checker( value, start, change ) );
      }

      static bool dunno2( T &value, T start, T change, T factor )
      {
        value += pow((value/(start+change)), 2) * factor;

        return( Animation::value_checker( value, start, change ) );
      }

      static bool dunno2_backwards( T &value, T start, T change, T factor )
      {
        value += pow((1-(value/(start+change))), 2) * factor;

        return( Animation::value_checker( value, start, change ) );
      }

    };

    static bool value_checker( T &value, T start, T change )
    {
      if( value > start+change )
      {
        value = start+change;
        return(false);
      }
      else
      {
        return( true );
      }
    }

  };
}