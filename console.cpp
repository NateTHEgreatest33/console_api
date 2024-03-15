
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
#include "console_commands.hpp"

#include "time.h"
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
core::console::console
    (      
    uart_inst_t* uart_port                /* uart port for console */
    ) : 
    p_uart( uart_port )
{
uart_init( p_uart, 115200 );

p_logItr = p_log.begin();

} /* console::console() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       core::~console (deconstructor)
*
*   DESCRIPTION:
*       console class deconstructor
*
*********************************************************************/
core::console::~console
    (
    void
    )
{

} /* console::~console() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       core::console::add_assert
*
*   DESCRIPTION:
*       console class assert function
*
*********************************************************************/
void core::console::add_assert
    (
    const std::string          s,            /*      assert string */
    const bool                 condition,    /*   condition to add */
    const std::source_location location      /* location of assert */
    )
{
/*----------------------------------------------------------
local variables
----------------------------------------------------------*/
std::string assert_string; /* temporary assert string */

/*----------------------------------------------------------
Verify if condition is met
----------------------------------------------------------*/
if( !condition )
    return;

/*----------------------------------------------------------
build assert string and add to array
----------------------------------------------------------*/
assert_string = std::string( location.file_name() ) + ":" + std::to_string( location.line() ) + " " + std::to_string( to_ms_since_boot( get_absolute_time() ) ) + " - " + s;
*p_logItr = assert_string;

/*----------------------------------------------------------
Update iterator
----------------------------------------------------------*/
p_logItr++;

/*----------------------------------------------------------
Loop if we are at the end of array
----------------------------------------------------------*/
if( p_logItr == p_log.end() )
    p_logItr = p_log.begin();

} /* console::assert() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       core::console::console_runtime()
*
*   DESCRIPTION:
*       console runtime function
*
*********************************************************************/
void core::console::console_runtime
    (
    void   
    )
{
/*----------------------------------------------------------
local variables
----------------------------------------------------------*/
char c        = 0x00;             /*  temporary character */
bool new_line = false;            /* new line rx'ed (Y/N) */
auto itr      = commands.end();   /* iterator for command */  

/*----------------------------------------------------------
Check if console is clean
----------------------------------------------------------*/
if( uart_is_readable( p_uart ) )    
    {
    c = uart_getc( p_uart );
    /*------------------------------------------------------
    clean \r command if rx'ed
    ------------------------------------------------------*/
    if( c == '\r')
        {
        uart_putc_raw( p_uart, '\r' );
        uart_putc_raw( p_uart, '\n' );
        new_line = true;
        }
    else
        {
        /*--------------------------------------------------
        Add to buffer & print back to user to show that 
        input has been processed. 
        --------------------------------------------------*/
        p_buffer += c;
        uart_putc_raw( p_uart, c );
        }  

    /*------------------------------------------------------
    Don't allow p_buffer to grow exponentially. Reset
    console window and buffer
    ------------------------------------------------------*/
    if ( p_buffer.length() > MAX_CMD_STR_SIZE )
        {
        uart_putc_raw( p_uart, '\r' );
        uart_putc_raw( p_uart, '\n' );
        p_buffer="";
        }

    }

/*----------------------------------------------------------
Handle a new line char meaning a full command has been sent
----------------------------------------------------------*/
if( new_line )
    {
    /*------------------------------------------------------
    search for and run command if found
    ------------------------------------------------------*/
    itr = commands.find( p_buffer );
    if( itr != commands.end() )
        itr->second( *this );
    else
        std::cout << "command not found" << std::endl;
    /*------------------------------------------------------
    clear buffer
    ------------------------------------------------------*/
    p_buffer = "";
    }

} /* console::console_runtime() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       core::console::get_log_ref
*
*   DESCRIPTION:
*       returns a refrence to the private log variable
*
*********************************************************************/
std::array<std::string,100>& core::console::get_log_ref
    ( 
    void 
    )
{
return p_log;
} /* console::get_log_ref() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       core::console::get_log_itr
*
*   DESCRIPTION:
*       returns a refrence to the log iterator
*
*********************************************************************/
std::array<std::string,100>::iterator core::console::get_log_itr
    ( 
    void 
    )
{
return p_logItr;
} /* console::get_log_itr() */
