#include "reveal/core/console.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <limits>
#include <cmath>

#define TEXT_COLOR_RED_BRIGHT     "\033[1;31m"
#define TEXT_COLOR_RED            "\033[31m"
#define TEXT_COLOR_GREEN_BRIGHT   "\033[1;32m"
#define TEXT_COLOR_GREEN          "\033[32m"
#define TEXT_COLOR_BLUE_BRIGHT    "\033[1;34m"
#define TEXT_COLOR_BLUE           "\033[34m"
#define TEXT_COLOR_DEFAULT        "\033[0m"


//-----------------------------------------------------------------------------
namespace Reveal {
//-----------------------------------------------------------------------------
namespace Core {
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void console_c::print( std::string msg ) {
  //std::cout << TEXT_COLOR_BLUE_BRIGHT << msg << TEXT_COLOR_DEFAULT;
  std::cout << msg;
}

//-----------------------------------------------------------------------------
void console_c::print( const std::stringstream& msg ) {
  //std::cout << TEXT_COLOR_BLUE_BRIGHT << msg.str() << TEXT_COLOR_DEFAULT;
  std::cout << msg.str();
}

//-----------------------------------------------------------------------------
void console_c::printline( std::string msg ) {
  //std::cout << TEXT_COLOR_BLUE_BRIGHT << msg << TEXT_COLOR_DEFAULT << std::endl;
  std::cout << msg << std::endl;
}

//-----------------------------------------------------------------------------
void console_c::printline( const std::stringstream& msg ) {
  //std::cout << TEXT_COLOR_BLUE_BRIGHT << msg.str() << TEXT_COLOR_DEFAULT << std::endl;
  std::cout << msg.str() << std::endl;
}

//-----------------------------------------------------------------------------
void console_c::error( std::string err ) {
  std::cerr << "ERROR: " << err << std::endl;
}

//-----------------------------------------------------------------------------
void console_c::error( const std::stringstream& err ) {
  std::cerr << "ERROR: " << err.str() << std::endl;
}

//-----------------------------------------------------------------------------
void console_c::print( std::vector<std::string> data ) {
  for( std::vector<std::string>::iterator it = data.begin(); it != data.end(); it++ )
    std::cout << *it << std::endl;
    //printf( "%s\n", it->c_str() );
}

//-----------------------------------------------------------------------------
void console_c::print_param_array( char* const* array ) {
  for( char* const* ptr = (char* const*)array; *ptr != NULL; ptr++ )
    std::cout << *ptr << std::endl;
    //printf( "%s\n", *ptr );
}

//-----------------------------------------------------------------------------
bool console_c::prompt_yes_no( std::string prompt ) {
  std::string input, err;
  
  do {
    std::cout << prompt << " ";
    std::cin.clear();
    std::getline( std::cin, input );

    if( input == "y" || input == "Y" ) {
      return true;
    } else if( input == "n" || input == "N" ) {
      return false;
    }

    err = "ERROR: Invalid Input. Enter y or n";
    std::cerr << err << std::endl;

  } while( true );

  return false;
}

//-----------------------------------------------------------------------------
unsigned console_c::prompt_unsigned( std::string prompt, bool allow_zero ) {
  std::string input, err;
  
  // infinite validation loop.  only way out is for the user to enter a valid
  // unsigned value
  do {
    // print the prompt to the console
    std::cout << prompt << ": ";
    // clear the input stream
    std::cin.clear();
    // get input from standard in
    std::getline( std::cin, input );

    // assume input is valid and invalidate if erroneous values
    bool valid = true;
    // iterate over the input buffer
    for( unsigned i = 0; i < input.size(); i++ ) {
      // read the current character
      char c = input[i];
      // if EOF and not first character then pass
      if( i > 0 && c == 0 ) break;
      // if not allow_zero zero is only character then fail
      if( !allow_zero && i == 0 && c == '0' && input.size() == 1 ) {
        valid = false;
        break;
      }
      // if not numeric, invalidate and fail
      if( c < '0' || c > '9' ) {
        valid = false;
        break;
      }
    }

    // if valid, return numeric value of input
    if( valid ) return (unsigned)atoi( input.c_str() );
    
    // if not valid, report and recycle
    err = "ERROR: Invalid Input. Enter an unsigned integer";
    std::cerr << err << std::endl;

  } while( true );

  return 0; // unreachable. suppresses warning on return statement 
}

//-----------------------------------------------------------------------------
float console_c::prompt_float( std::string prompt, float& epsilon, bool allow_negative ) {
  std::string input, err;
  float value;
  float machine_epsilon = std::numeric_limits<float>::epsilon();
  
  // infinite validation loop.  only way out is for the user to enter a valid
  // float value
  do {
    // print the prompt to the console
    std::cout << prompt << ": ";
    // clear the input stream
    std::cin.clear();
    // get input from standard in
    std::getline( std::cin, input );

    // send the input to an input stream for validation
    std::istringstream ss(input);

    if( ss >> value ) {
      // if valid conversion of input to value
      if( !allow_negative && value < 0.0 ) {
        // if negatives are invalid and input was negative, error and recycle
        err = "ERROR: Invalid Input. Enter a floating point number";
        std::cerr << err << std::endl;
      } else {
        // if otherwise valid, compute epsilon and return value
        if( value > 10.0)
          epsilon = machine_epsilon * pow( 10.0, (int)log10( value ) );
        else
          epsilon = machine_epsilon * 10.0;
        return value;
      }
    } else {
      // the user entered invalid input
      err = "ERROR: Invalid Input. Enter an unsigned floating point number";
      std::cerr << err << std::endl;
    }
  } while( true );

  return 0.0; // unreachable. suppresses warning on return statement 
}

//-----------------------------------------------------------------------------
double console_c::prompt_double( std::string prompt, double& epsilon, bool allow_negative ) {
  std::string input, err;
  double value;
  double machine_epsilon = std::numeric_limits<double>::epsilon();
  
  // infinite validation loop.  only way out is for the user to enter a valid
  // double value
  do {
    // print the prompt to the console
    std::cout << prompt << ": ";
    //printf( "%s: ", prompt.c_str() );
    // clear the input stream
    std::cin.clear();
    // get input from standard in
    std::getline( std::cin, input );

    // send the input to an input stream for validation
    std::istringstream ss(input);

    if( ss >> value ) {
      // if valid conversion of input to value
      if( !allow_negative && value < 0.0 ) {
        // if negatives are invalid and input was negative, error and recycle
        err = "ERROR: Invalid Input. Enter a floating point number";
        std::cerr << err << std::endl;
      } else {
        // if otherwise valid, compute epsilon and return value
        if( value > 10.0)
          epsilon = machine_epsilon * pow( 10.0, (int)log10( value ) );
        else
          epsilon = machine_epsilon * 10.0;
        return value;
      }
    } else {
      // the user entered invalid input
      err = "ERROR: Invalid Input. Enter an unsigned floating point number";
      std::cerr << err << std::endl;
    }
  } while( true );

  return 0.0; // unreachable. suppresses warning on return statement 
}

//-----------------------------------------------------------------------------
std::string console_c::prompt( std::string prompt ) {
  std::string input;

  // print the prompt to the console
  std::cout << prompt << " ";
  // clear the input stream
  std::cin.clear();
  // get input from standard in
  std::getline( std::cin, input );

  return input;
}

//-----------------------------------------------------------------------------
// Note: the 1-base offset in choice exists because stringstream(input) sets 
// choice to 0 if an invalid value, e.g. a string of characters, is entered via
// cin.
unsigned console_c::menu( std::string title, std::string prompt, std::vector< std::string > list ) {
  unsigned choice;
  unsigned range = list.size();
  std::string input;
  std::stringstream err;  

  std::cout << title << std::endl;

  for( unsigned i = 0; i < list.size(); i++ )
    std::cout << i+1 << ": " << list[i] << std::endl;

  do {
    std::cout << prompt << ": ";
    std::cin.clear();
    std::getline( std::cin, input );

    std::stringstream( input ) >> choice;

    if( choice == 0 || choice > range ) {
      err << "ERROR: Invalid Input. Enter a value in the range [1," << range << "]";
      std::cerr << err.str() << std::endl;
    }

  } while( choice == 0 || choice > range );

  choice--;  // to fix the 1-base offset back to 0-base
  return choice;
}


//-----------------------------------------------------------------------------
} // namespace Reveal
//-----------------------------------------------------------------------------
} // namespace Core
//-----------------------------------------------------------------------------

