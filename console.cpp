
/*********************************************************************
*
*   NAME:
*       console.cpp
*
*   DESCRIPTION:
*       API for interfacing over UART serial
*
*   Copyright 2023 Nate Lenze
*
*********************************************************************/

/*--------------------------------------------------------------------
                              INCLUDES
--------------------------------------------------------------------*/
#include "console.hpp"

/*--------------------------------------------------------------------
                          GLOBAL NAMESPACES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                TYPES
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
core::console() 
--------------------------------------------------------------------*/
/*********************************************************************
*
*   PROCEDURE NAME:
*       core::console (constructor)
*
*   DESCRIPTION:
*       console class constructor
*
*********************************************************************/
core::console::console( bool debugModeOn ) : debugMode( debugModeOn ) 
    {
    logItr = log.begin();
    }

core::console::~console(){}

void core::console::assert_stop( const std::string s, const bool condition, const std::source_location location = std::source_location::current() ){}

void core::console::assert_continue( const std::string s, const bool condition, const std::source_location location = std::source_location::current() ){}

void core::console::assert_debug( const std::string s, const bool condition, const std::source_location location = std::source_location::current() ){}

void core::console::assert_debug( const std::string s, const bool condition, const std::source_location location = std::source_location::current() ){}

void core::console::console_runtime(){}

void core::console::print_assert_log( void ){}