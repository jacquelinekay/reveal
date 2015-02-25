/*------------------------------------------------------------------------------
author: James R Taylor (jrt@gwu.edu)

solution.h defines the solution_c data-structure that contains data produced by
a client upon completion of a trial within a scenario
------------------------------------------------------------------------------*/

#ifndef _REVEAL_CORE_SOLUTION_H_
#define _REVEAL_CORE_SOLUTION_H_

//-----------------------------------------------------------------------------

#include <string>
#include <vector>
#include <stdio.h>

#include "Reveal/core/pointers.h"
#include "Reveal/core/model.h"

//-----------------------------------------------------------------------------

namespace Reveal {

//-----------------------------------------------------------------------------

namespace Core {

//-----------------------------------------------------------------------------

class solution_c {
public:
  enum type_e {
    MODEL,
    CLIENT
  };  

  solution_c( type_e type ) { this->type = type; }
  virtual ~solution_c( void ) {}

  std::string scenario_id;
  unsigned trial_id;
  double t;
  double dt;
  // session identifier

  std::vector<model_ptr> models;
  type_e type;

  void print( void ) {
    printf( "scenario_id[%s]", scenario_id.c_str() );
    printf( ", trial_id[%u]", trial_id );
    printf( ", t[%f]", t );
    printf( ", dt[%f]", dt );

    printf( ", models { " );
    for( unsigned i = 0; i < models.size(); i++ ) {
      if( i > 0 ) printf( ", " );
      models[i]->print();
    }
    printf( " }\n" );
  }

};

//-----------------------------------------------------------------------------

}  // namespace Core

//-----------------------------------------------------------------------------

}  // namespace Reveal

//-----------------------------------------------------------------------------

#endif // _REVEAL_CORE_SOLUTION_H_