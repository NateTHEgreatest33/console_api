#ifndef CONSOLE_HPP
#define CONSOLE_HPP
/*********************************************************************
*
*   HEADER:
*       header file for Console API
*
*   Copyright 2023 Nate Lenze
*
****************a*****************************************************/
/*--------------------------------------------------------------------
                              INCLUDES
--------------------------------------------------------------------*/
#include <source_location>
#include <iostream>
#include <array>
// #include <unordered_map>
#include <functional>

/*--------------------------------------------------------------------
                          GLOBAL NAMESPACES
--------------------------------------------------------------------*/


/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                            TYPES/ENUMS
--------------------------------------------------------------------*/

enum class commands : int {
  HELP = 0,
  NUM_COMMANDS
};
/*--------------------------------------------------------------------
                           MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              VARIABLES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                               CLASSES
--------------------------------------------------------------------*/
namespace core {
class console 
    {
    public:
        console(bool debugMode );
        ~console();
        // override >> operator?
        void assert_stop( const std::string s, const bool condition, const std::source_location location = std::source_location::current() );
        void assert_continue( const std::string s, const bool condition, const std::source_location location = std::source_location::current() );
        void assert_debug( const std::string s, const bool condition, const std::source_location location = std::source_location::current() );
        void log(  const std::string s, const std::source_location location = std::source_location::current() );
        void console_runtime();

    private:

      void print_assert_log( void );
      std::array< std::function<void()>, static_cast<size_t>(commands::NUM_COMMANDS) > command_list;
      std::array<std::string, 100> log;
      std::array<std::string,100>::iterator logItr;
      bool debugMode;
    };


} /* core namespace */
#endif
