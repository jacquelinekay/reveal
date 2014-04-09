/*-----------------------------------------------------------------------------
James R Taylor:jrt@gwu.edu

-----------------------------------------------------------------------------*/

#ifndef _REVEAL_CORE_SOLUTION_H_
#define _REVEAL_CORE_SOLUTION_H_

//-----------------------------------------------------------------------------

#include <vector>

#include <Reveal/state.h>

//-----------------------------------------------------------------------------

namespace Reveal {

//-----------------------------------------------------------------------------

namespace Core {

//-----------------------------------------------------------------------------

class solution_c {
public:
  solution_c( void ) {}
  virtual ~solution_c( void ) {}

  std::string scenario;
  unsigned index;
  double t;
  state_c state;

  void print( void ) {
    printf( "scenario[%s]", scenario.c_str() );
    printf( ", index[%u]", index );
    printf( ", t[%f]", t );

    // State 
    printf( ", state[" );
    printf( " q[" );
    for( unsigned i = 0; i < state.size_q(); i++ ) {
      if( i > 0 ) printf( ", " );
      printf( "%f", state.q(i) );
    }
    printf( "]" );
    printf( ", dq[" );
    for( unsigned i = 0; i < state.size_dq(); i++ ) {
      if( i > 0 ) printf( ", " );
      printf( "%f", state.dq(i) );
    }
    printf( "] " );
    printf( "]" );
  }
 
};

//-----------------------------------------------------------------------------

}  // namespace Core

//-----------------------------------------------------------------------------

}  // namespace Reveal

//-----------------------------------------------------------------------------

#endif // _REVEAL_CORE_SOLUTION_H_
