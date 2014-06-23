/*-----------------------------------------------------------------------------
James R Taylor:jrt@gwu.edu

-----------------------------------------------------------------------------*/

#ifndef _REVEAL_CORE_SCENARIO_H_
#define _REVEAL_CORE_SCENARIO_H_

//-----------------------------------------------------------------------------

#include <stdio.h>

#include <Reveal/pointers.h>
#include <Reveal/trial.h>
#include <Reveal/solution.h>

//-----------------------------------------------------------------------------

namespace Reveal {

//-----------------------------------------------------------------------------

namespace Core {

//-----------------------------------------------------------------------------

class scenario_c {
public:
  scenario_c( void ) {}
  virtual ~scenario_c( void ) {}
 
  unsigned id;
  std::string name;
  std::string description;
  unsigned trials;
  std::vector<std::string> uris;

  void print( void ) const {
    printf( "id[%u]", id );
    printf( ", name[%s]", name.c_str() );
    printf( ", trials[%u]", trials );
    printf( ", uris[" );
    for( unsigned i = 0; i < uris.size(); i++ ) {
      if( i > 0 ) printf( ", " );
      printf( "%s", uris.at(i).c_str() );
    }
    printf( "]\n" );
  }

  trial_ptr get_trial( int trial_id ) {
    assert( trial_id < trials );

    trial_ptr trial = trial_ptr( new trial_c() );
    trial->scenario_id = id;
    trial->trial_id = trial_id;

    return trial;
  }

  solution_ptr get_solution( trial_ptr trial, double t ) {
    assert( trial->scenario_id == id );
    assert( trial->trial_id < trials );

    solution_ptr solution = solution_ptr( new solution_c() );
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
