#ifndef _REVEAL_DB_MONGO_ANALYSIS_H_
#define _REVEAL_DB_MONGO_ANALYSIS_H_

#include "Reveal/core/pointers.h"
#include "Reveal/core/analysis.h"
#include "Reveal/db/mongo/mongo.h"
#include "Reveal/db/database.h"

//-----------------------------------------------------------------------------
namespace Reveal {
//-----------------------------------------------------------------------------
namespace DB {
//-----------------------------------------------------------------------------
namespace Mongo {
//-----------------------------------------------------------------------------

class analysis_c {
public:

  /// inserts an instance of a analysis structure into the database
  /// @param db the reveal/mongo database to insert into
  /// @param analysis the instance to insert
  /// @return true if the record was inserted OR false if insertion failed
  static bool insert( database_ptr db, Reveal::Core::analysis_ptr analysis );
};

//-----------------------------------------------------------------------------
} // namespace Mongo
//-----------------------------------------------------------------------------
} // namespace DB
//-----------------------------------------------------------------------------
} // namespace Reveal
//-----------------------------------------------------------------------------

#endif // _REVEAL_DB_MONGO_ANALYSIS_H_
