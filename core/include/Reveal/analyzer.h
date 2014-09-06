#ifndef _REVEAL_CORE_ANALYZER_H_
#define _REVEAL_CORE_ANALYZER_H_

//-----------------------------------------------------------------------------

#include <Reveal/solution.h>
#include <Reveal/trial.h>
#include <Reveal/scenario.h>

//-----------------------------------------------------------------------------

namespace Reveal {

//-----------------------------------------------------------------------------

namespace Core {

//-----------------------------------------------------------------------------

class analyzer_c;
typedef boost::shared_ptr<Reveal::Core::analyzer_c> analyzer_ptr;

//-----------------------------------------------------------------------------

class analyzer_c {
public:
  enum type_e {
    PLUGIN,
    SCRIPT
  };

  analyzer_c( void ) { }
  virtual ~analyzer_c( void ) { }

  int                    scenario_id;
  std::string            filename;
  type_e 	         type;
};

//-----------------------------------------------------------------------------

} // namespace Core

//-----------------------------------------------------------------------------

} // namespace Reveal

//-----------------------------------------------------------------------------

#endif // _REVEAL_CORE_ANALYZER_H_