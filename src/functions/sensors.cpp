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

    position = position + acceleration.at( acceleration.size() );
    position = position * totalTime / ( 3 * 50 );

    return position;
}
