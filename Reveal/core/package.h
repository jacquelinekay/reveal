#ifndef _REVEAL_CORE_PACKAGE_H_
#define _REVEAL_CORE_PACKAGE_H_

#include <string>

#include <boost/shared_ptr.hpp>

#include "Reveal/core/system.h"
#include "Reveal/core/manifest.h"

//-----------------------------------------------------------------------------
namespace Reveal {
//-----------------------------------------------------------------------------
namespace Core {
//-----------------------------------------------------------------------------

class child_exit_handler_c : public sighandler_c {
protected:
  static bool _quit;

public:
  child_exit_handler_c( void ); 
  ~child_exit_handler_c( void );

  static void handler( int signum );

  static bool quit( void ); 
  static void set( bool quit_ );
  static void reset( void );

  virtual void install( void );
  virtual void uninstall( void );

  static void trip( void );
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

class package_c;
typedef boost::shared_ptr<package_c> package_ptr;
//-----------------------------------------------------------------------------

class package_c {
public:
  package_c( std::string source_path, std::string build_path );
  virtual ~package_c( void );

  bool read( void );
  bool configure( void );
  bool make( void );

protected:
  std::string _source_path;
  std::string _build_path;
  std::vector<std::string> _build_products;

  Reveal::Core::manifest_c _manifest;

  static void* cmake_worker( void* args );
  static void* make_worker( void* args );

  bool cmake_package( char* const* args );
  bool cmake_package( std::string source_path, std::string build_path );
  bool make_package( char* const* args );
  bool make_package( std::string build_path, std::vector<std::string> build_products );

};

//-----------------------------------------------------------------------------
} // namespace Core
//-----------------------------------------------------------------------------
} // namespace Reveal
//-----------------------------------------------------------------------------

#endif // _REVEAL_CORE_PACKAGE_H_