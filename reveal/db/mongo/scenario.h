#ifndef _REVEAL_DB_MONGO_SCENARIO_H_
#define _REVEAL_DB_MONGO_SCENARIO_H_

#include "reveal/core/pointers.h"
#include "reveal/core/scenario.h"
#include "reveal/db/mongo/mongo.h"
#include "reveal/db/database.h"

//-----------------------------------------------------------------------------
namespace Reveal {
//-----------------------------------------------------------------------------
namespace DB {
//-----------------------------------------------------------------------------
namespace Mongo {
//-----------------------------------------------------------------------------

class scenario_c {
public:

  /// count the number of scenarios in the database
  /// @param db the reveal/mongo database to count records in
  /// @return the total count of scenarios listed in the scenario table
  static unsigned count( database_ptr db );

  /// inserts an instance of a scenario structure into the database
  /// @param db the reveal/mongo database to insert into
  /// @param scenario the instance to insert
  /// @return true if the record was inserted OR false if insertion failed
  static bool insert( database_ptr db, Reveal::Core::scenario_ptr scenario );

  /// fetches an instance of the scenario specified from the database
  /// @param scenario instance populated with data on success
  /// @param db the reveal/mongo database to fetch the record from
  /// @param scenario_id the unique identifier to search the scenario table for
  /// @return true if the instance was populated OR false if fetch failed
  static bool fetch( Reveal::Core::scenario_ptr& scenario, database_ptr db, std::string scenario_id );

  /// maps the bson object into a new instance of a scenario
  /// @param scenario instance created and populated on success
  /// @param obj the bson object to map data from
  /// @return true if the instance was populated OR false if mapping failed
  static bool map( Reveal::Core::scenario_ptr& scenario, mongo::BSONObj obj );

  /// maps the scenario instance into a bson object 
  /// @param obj the bson object to map data into
  /// @param scenario the scenario pointer to map data from
  /// @return true if the instance was populated OR false if mapping failed
  static bool map( mongo::BSONObj& obj, Reveal::Core::scenario_ptr scenario );

};

//-----------------------------------------------------------------------------
} // namespace Mongo
//-----------------------------------------------------------------------------
} // namespace DB
//-----------------------------------------------------------------------------
} // namespace Reveal
//-----------------------------------------------------------------------------

#endif // _REVEAL_DB_MONGO_SCENARIO_H_
