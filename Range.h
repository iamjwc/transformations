#ifndef RANGE_H
#define RANGE_H

namespace Graphics
{
  template< typename T = float >
  class Range
  {
  public:
    T min;
    T max;

    Range(){}

    Range( T min, T max )
    {
      if( min <= max )
      {
        this->min = min;
        this->max = max;
      }
      else
      {
        this->min = max;
        this->max = min;
      }
    }

    T size()
    {
      return( this->max - this->min );
    }
  };
}

#endif