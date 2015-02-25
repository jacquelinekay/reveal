#include "Reveal/db/query.h"

#include <assert.h>
#include <sstream>

//-----------------------------------------------------------------------------
namespace Reveal {
//-----------------------------------------------------------------------------
namespace DB {
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
query_c::query_c( void ) {

}

//-----------------------------------------------------------------------------
query_c::~query_c( void ) {

}

//-----------------------------------------------------------------------------
mongo::Query query_c::operator()( void ) {
  return _query;
}

//-----------------------------------------------------------------------------
void query_c::operator()( mongo::Query query ) {
  _query = query;
}

//-----------------------------------------------------------------------------
void query_c::user( const std::string& user_id ) {
  _query = QUERY( "user_id" << user_id );
}

//-----------------------------------------------------------------------------
void query_c::session( const std::string& session_id ) {
/*
  std::stringstream ss;
  ss << session_id;
  std::string key = ss.str();
*/
  _query = QUERY( "session_id" << session_id );
}

//-----------------------------------------------------------------------------
void query_c::experiment( const std::string& experiment_id ) {
  _query = QUERY( "experiment_id" << experiment_id );
}

//-----------------------------------------------------------------------------
void query_c::digest( void ) {
  //_query = QUERY( "name" << name );
  // TODO: SQL equivalent 'scenario *'
}

//-----------------------------------------------------------------------------
/*
void query_c::scenario( int scenario_id ) {
  _query = QUERY( "id" << scenario_id );
}
*/

//-----------------------------------------------------------------------------
void query_c::scenario( const std::string& scenario_id ) {
  _query = QUERY( "scenario_id" << scenario_id );
}

//-----------------------------------------------------------------------------
void query_c::trial( const std::string& scenario_id, int trial_id ) {
  _query = QUERY( "scenario_id" << scenario_id << "trial_id" << trial_id);
}
/*
//-----------------------------------------------------------------------------
void query_c::solution( const std::string& scenario ) {
  _query = QUERY( "scenario" << scenario );
}
*/
//-----------------------------------------------------------------------------
void query_c::solution( const std::string& scenario_id, int trial_id ) {
  _query = QUERY( "scenario_id" << scenario_id << "trial_id" << trial_id );
}
/*
//-----------------------------------------------------------------------------
void query_c::model_solution( unsigned scenario_id ) {
  _query = QUERY( "scenario_id" << scenario_id );
}
*/
/*
//-----------------------------------------------------------------------------
void query_c::model_solution( int scenario_id, int trial_id ) {
  _query = QUERY( "scenario_id" << scenario_id << "trial_id" << trial_id );
}
*/
//-----------------------------------------------------------------------------
void query_c::analyzer( const std::string& scenario_id ) {
  _query = QUERY( "scenario_id" << scenario_id );
}

//-----------------------------------------------------------------------------
void query_c::solution_set( const std::string& scenario_id, const std::string& session_id ) {
  _query = QUERY( "scenario_id" << scenario_id << "session_id" << session_id );
}

//-----------------------------------------------------------------------------
} // namespace DB
//-----------------------------------------------------------------------------
} // namespace Reveal
//-----------------------------------------------------------------------------