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
#include "pico/stdlib.h"

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
        console( bool debugModeOn, uart_inst_t* uart_port );
        ~console();
        // override >> operator?
        void add_assert( const std::string s, const bool condition, const std::source_location location = std::source_location::current() );
        void log( const std::string s, const std::source_location location = std::source_location::current() );
        void console_runtime();
        std::array<std::string,100>& get_log_ref( void );
        std::array<std::string,100>::iterator get_log_itr( void );

    private:
      uart_inst_t* p_uart;
      std::string p_buffer;
      // void command_handler( std::string& command );
      // std::array < std::function<void(void)>, static_cast<size_t>(NUM_COMMANDS) > p_command_list;
      std::array<std::string, 100> p_log;
      std::array<std::string,100>::iterator p_logItr;
      bool p_debugMode;
    };


} /* core namespace */
#endif
