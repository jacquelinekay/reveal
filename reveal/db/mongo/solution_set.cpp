#include "reveal/db/mongo/solution_set.h"

#include <mongo/client/dbclient.h>

#include "reveal/core/experiment.h"
#include "reveal/core/scenario.h"
#include "reveal/core/trial.h"
#include "reveal/core/solution.h"
#include "reveal/core/model.h"

#include "reveal/db/mongo/scenario.h"
#include "reveal/db/mongo/experiment.h"
#include "reveal/db/mongo/trial.h"
#include "reveal/db/mongo/solution.h"

//-----------------------------------------------------------------------------
namespace Reveal {
//-----------------------------------------------------------------------------
namespace DB {
//-----------------------------------------------------------------------------
namespace Mongo {
//-----------------------------------------------------------------------------

bool solution_set_c::fetch( Reveal::Core::solution_set_ptr& solution_set, Reveal::DB::database_ptr db, std::string experiment_id ) {

  // NOTE: may need to order queries such that indices match up in each query

  Reveal::Core::experiment_ptr experiment;
  Reveal::Core::scenario_ptr scenario;
  Reveal::Core::trial_ptr trial;
  Reveal::Core::solution_ptr solution, model;
  bool result;

  // get mongo service and verify
  mongo_ptr mongo = mongo_c::service( db );
  if( !mongo ) return false;

  solution_set = Reveal::Core::solution_set_ptr( new Reveal::Core::solution_set_c() );

  result = experiment_c::fetch( experiment, db, experiment_id );
  if( !result ) return false;

  std::string scenario_id = experiment->scenario_id;

  result = scenario_c::fetch( scenario, db, scenario_id );
  if( !result ) return false;

  //solution_set->scenario = scenario;
  solution_set->experiment = experiment;

  //TODO:
/*
  for( unsigned i = 0; i < scenario->trials; i++ ) {
    result = trial_c::fetch( trial, db, scenario_id, i );
    if( !result ) return false;
    solution_set->add_trial( trial );

    result = solution_c::fetch( solution, db, experiment->experiment_id, scenario_id, i );
    if( !result ) return false;
    solution_set->add_solution( solution );

    result = solution_c::fetch( model, db, Reveal::Core::solution_c::MODEL, scenario_id, i );
    if( !result ) return false;
    solution_set->add_model( model );
  }
*/
  return true;
}

//-----------------------------------------------------------------------------
bool solution_set_c::fetch( Reveal::Core::solution_set_ptr& solution_set, Reveal::DB::database_ptr db, std::string experiment_id, double t, double epsilon ) {

  // NOTE: may need to order queries such that indices match up in each query

  Reveal::Core::experiment_ptr experiment;
  Reveal::Core::scenario_ptr scenario;
  Reveal::Core::trial_ptr trial;
  Reveal::Core::solution_ptr solution, model;
  bool result;

  // get mongo service and verify
  mongo_ptr mongo = mongo_c::service( db );
  if( !mongo ) return false;

  solution_set = Reveal::Core::solution_set_ptr( new Reveal::Core::solution_set_c() );

  result = experiment_c::fetch( experiment, db, experiment_id );
  if( !result ) return false;

  std::string scenario_id = experiment->scenario_id;

  result = scenario_c::fetch( scenario, db, scenario_id );
  if( !result ) return false;

  //solution_set->scenario = scenario;
  solution_set->experiment = experiment;

  //TODO:
  result = trial_c::fetch( trial, db, scenario_id, t, epsilon );
  if( !result ) return false;
  solution_set->add_trial( trial );

  result = solution_c::fetch( solution, db, experiment->experiment_id, scenario_id, t, epsilon );
  if( !result ) return false;
  solution_set->add_solution( solution );

  result = solution_c::fetch( model, db, Reveal::Core::solution_c::MODEL, scenario_id, t, epsilon );
  if( !result ) return false;
  solution_set->add_model( model );

  return true;
}

//-----------------------------------------------------------------------------
bool solution_set_c::fetch( Reveal::Core::solution_set_ptr& solution_set, Reveal::DB::database_ptr db, std::string experiment_id, double trial_time, double solution_time, double epsilon ) {

  // NOTE: may need to order queries such that indices match up in each query

  Reveal::Core::experiment_ptr experiment;
  Reveal::Core::scenario_ptr scenario;
  Reveal::Core::trial_ptr trial;
  Reveal::Core::solution_ptr solution, model;
  bool result;

  // get mongo service and verify
  mongo_ptr mongo = mongo_c::service( db );
  if( !mongo ) return false;

  solution_set = Reveal::Core::solution_set_ptr( new Reveal::Core::solution_set_c() );

  result = experiment_c::fetch( experiment, db, experiment_id );
  if( !result ) return false;
  //printf( "found experiment\n" );

  std::string scenario_id = experiment->scenario_id;

  result = scenario_c::fetch( scenario, db, scenario_id );
  if( !result ) return false;
  //printf( "found scenario\n" );

  //solution_set->scenario = scenario;
  solution_set->experiment = experiment;

  //printf( "querying for trial[%f] and solutions[%f]\n", trial_time, solution_time );
  //TODO:
  result = trial_c::fetch( trial, db, scenario_id, trial_time, epsilon );
  if( !result ) return false;
  solution_set->add_trial( trial );
  //printf( "found trial[%f]\n", trial_time );

  result = solution_c::fetch( solution, db, experiment->experiment_id, scenario_id, solution_time, epsilon );
  if( !result ) return false;
  solution_set->add_solution( solution );
  //printf( "found solution t[%f]\n", solution_time );

  result = solution_c::fetch( model, db, Reveal::Core::solution_c::MODEL, scenario_id, solution_time, epsilon );
  if( !result ) return false;
  solution_set->add_model( model );
  //printf( "found model t[%f]\n", solution_time );

  return true;
}

//-----------------------------------------------------------------------------
} // namespace Mongo
//-----------------------------------------------------------------------------
} // namespace DB
//-----------------------------------------------------------------------------
} // namespace Reveal
//-----------------------------------------------------------------------------


