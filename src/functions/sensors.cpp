#include "config.h"

double getCurrentPosition(){

    double position = 0;
    position += acceleration.at(0);

    for (std::vector<double>::size_type i = 1; i != acceleration.size() - 1; i++)  {

        if(i % 2 == 1){

            position += ( 2 * acceleration.at(i) );

        }

        else {

            position += ( 4 * acceleration.at(i) );

        }

    }

    position += acceleration.at( acceleration.size() );
    position = pow(position * totalTime / ( 3 * 50 ), 2);

    return position;
}

/*
  Simpson's rule states that:
    The integral of the curve enclosed in the interval [a, b] can be denoted as such
      integral of f(x) from a to b = sn = (delta x)/3 * [f(x0) + 4f(x1) + 2f(x2) + 4f(x3) + 2f(x4) + 4f(xN-2) + 2f(xN-1) + f(xN)]

  We can apply this with getting the current position.
  Since the double integral of acceleration gives position and the initial position and velocity is always 0,
  we can use the formula once to get current velocity and twice to get current position.
*/
