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

#include "pico/mutex.h"
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
        console( uart_inst_t* uart_port );
        ~console();
        void add_assert( const std::string s, const bool condition = true, const std::source_location location = std::source_location::current() );
        void log( const std::string s, const std::source_location location = std::source_location::current() );
        void console_runtime();
        std::array<std::string,100>& get_log_ref( void );
        std::array<std::string,100>::iterator get_log_itr( void );
        std::array<std::string,100>::iterator& get_log_itr_ref( void );
        mutex_t& get_itr_mutex( void );

    private:
      uart_inst_t* p_uart;
      std::string p_buffer; //TODO: convert this to size limited char array
      // std::array<char, 100> p_buffer;
      std::array<std::string, 100> p_log;
      std::array<std::string,100>::iterator p_logItr;
      mutex_t p_itrMutex;
    };


} /* core namespace */
#endif
