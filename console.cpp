
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
const std::unordered_map< std::string, std::function< void( core::console& c ) commands = 
{
{ "print assert",    print_assert_log },
{ "example command", print_assert_log }
};

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
    bool         debugModeOn, 
    uart_inst_t* uart_port 
    ) : 
    p_debugMode( debugModeOn ), 
    p_uart( uart_port )
{
p_logItr = log.begin();

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
*       core::console::assert
*
*   DESCRIPTION:
*       console class assert function
*
*********************************************************************/
void core::console::assert
    (
    const std::string          s, 
    const bool                 condition, 
    const std::source_location location = std::source_location::current() 
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
assert_string = location.file_name + ":" + location.line + " - " + s;
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
        c = '\n';
        new_line = true;
        }
        

    /*------------------------------------------------------
    Add to buffer & print back to user to show that input
    has been processed. 
    ------------------------------------------------------*/  
    p_buffer += c;
    uart_putc_raw( p_uart, c );
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
        itr->second( this );
        
    /*------------------------------------------------------
    clear buffer
    ------------------------------------------------------*/
    p_buffer = "";
    }

} /* console::console_runtime() */

void core::console::print_assert_log( void )
    {
    auto log_iterator = p_log.begin();

    std::cout << "ASSERT LOG:\n"
    while( log_iterator != p_logItr )
        {
        std::cout << *log_iterator << std::endl;
        log_iterator++;
        }

    }



/*--------------------------------------------------------------------
Command Functions
--------------------------------------------------------------------*/
static void print_assert_log
    ( 
    core::console& c
    )
{
return;
}