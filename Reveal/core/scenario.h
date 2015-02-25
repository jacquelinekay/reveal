/*------------------------------------------------------------------------------
author: James R Taylor (jrt@gwu.edu)

scenario.h defines the scenario_c data-structure that contains scenario data.
A scenario is the priniciple set of data required to interact between client
and server
------------------------------------------------------------------------------*/

#ifndef _REVEAL_CORE_SCENARIO_H_
#define _REVEAL_CORE_SCENARIO_H_

//-----------------------------------------------------------------------------

#include <stdio.h>

#include "Reveal/core/pointers.h"
#include "Reveal/core/trial.h"
#include "Reveal/core/solution.h"

//-----------------------------------------------------------------------------

namespace Reveal {

//-----------------------------------------------------------------------------

namespace Core {

//-----------------------------------------------------------------------------

class scenario_c {
public:
  scenario_c( void ) {}
  virtual ~scenario_c( void ) {}
 
  std::string id;
  std::string description;
  unsigned trials;
  unsigned steps_per_trial;
  std::vector<std::string> uris;

  void print( void ) const {
    printf( "id[%s]", id.c_str() );
    printf( ", trials[%u]", trials );
    printf( ", steps_per_trial[%u]", steps_per_trial );
    printf( ", uris[" );
    for( unsigned i = 0; i < uris.size(); i++ ) {
      if( i > 0 ) printf( ", " );
      printf( "%s", uris.at(i).c_str() );
    }
    printf( "]\n" );
  }

  trial_ptr get_trial( unsigned trial_id ) {
    assert( trial_id < trials );

    trial_ptr trial = trial_ptr( new trial_c() );
    trial->scenario_id = id;
    trial->trial_id = trial_id;

    return trial;
  }

  solution_ptr get_solution( Reveal::Core::solution_c::type_e type, trial_ptr trial, double t ) {
    assert( trial->scenario_id == id );
    assert( trial->trial_id < trials );

    // TODO : temporary change of adding type into solution constructor.
    solution_ptr solution = solution_ptr( new solution_c( type ) );
    // !!

    solution->scenario_id = id;
    solution->trial_id = trial->trial_id;
    solution->t = t;

    return solution;
  }
};

//-----------------------------------------------------------------------------

}  // namespace Core

//-----------------------------------------------------------------------------

}  // namespace Reveal

//-----------------------------------------------------------------------------

#endif // _REVEAL_CORE_SCENARIO_H_