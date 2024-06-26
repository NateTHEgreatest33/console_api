
/*********************************************************************
*
*   NAME:
*       console_commands.cpp
*
*   DESCRIPTION:
*       API for interfacing with the big red button
*
*   Copyright 2023 Nate Lenze
*
*********************************************************************/

/*--------------------------------------------------------------------
                              INCLUDES
--------------------------------------------------------------------*/
#include "console_commands.hpp"
#include "mutex_lock.hpp"

#include "pico/mutex.h"
#include "pico/bootrom.h"

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
                                EXTERNS
--------------------------------------------------------------------*/
extern bool g_test_mode_enable;

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/
/*********************************************************************
*
*   PROCEDURE NAME:
*       print_assert_log
*
*   DESCRIPTION:
*       print assert log function
*
*********************************************************************/
void print_assert_log
    ( 
    core::console& c                            /* console refrence */
    )
{
/*----------------------------------------------------------
local variables
----------------------------------------------------------*/
auto log_iterator     = c.get_log_ref().begin();
auto log_end_iterator = c.get_log_itr();

/*----------------------------------------------------------
loop through asserts
----------------------------------------------------------*/
std::cout << "ASSERT LOG:\r\n";

while( log_iterator != log_end_iterator ) 
    {
    std::cout << *log_iterator << std::endl;
    log_iterator++;
    }

} /* core::console::print_assert_log() */


/*********************************************************************
*
*   PROCEDURE NAME:
*       help
*
*   DESCRIPTION:
*       prints list of functions
*
*********************************************************************/
void help
    ( 
    core::console& c                            /* console refrence */
    )
{
/*----------------------------------------------------------
local variables
----------------------------------------------------------*/
auto idx = commands.begin();           /* index interator */

/*----------------------------------------------------------
loop through and print avialable commands (key of unordered map)
----------------------------------------------------------*/
std::cout << "LIST OF COMMANDS:" << std::endl;
while( idx != commands.end() )
    {
    std::cout << " - " << (*idx).first << std::endl;
    idx++;
    }

} /* help() */


/*********************************************************************
*
*   PROCEDURE NAME:
*       help
*
*   DESCRIPTION:
*       prints list of functions
*
*********************************************************************/
void clear_screen
    ( 
    core::console& c                            /* console refrence */
    )
{
/*----------------------------------------------------------
Send the clear screen command to minicom:
    Esc     the ASCII Escape character, value 0x1B.  
    [       the ASCII left square brace character, value 0x5B.  
    2       the ASCII character for numeral 2, value 0x32.  
    J       the ASCII character for the letter J, value 0x4A.  
----------------------------------------------------------*/
printf("%c[2J", 0x1b);
printf("%c[0;0H", 0x1b);
} /* clear_screen() */


/*********************************************************************
*
*   PROCEDURE NAME:
*       toggle_test_mode
*
*   DESCRIPTION:
*       toggles test mode global
*
*********************************************************************/
void toggle_test_mode
    ( 
    core::console& c                            /* console refrence */
    )
{
/*----------------------------------------------------------
local variables
----------------------------------------------------------*/
std::string enabled;

/*----------------------------------------------------------
toggle global and update string
----------------------------------------------------------*/
g_test_mode_enable = !g_test_mode_enable;
enabled = ( g_test_mode_enable == true ? "enabled" : "disabled" );

/*----------------------------------------------------------
report to user test mode status
----------------------------------------------------------*/
std::cout << "Test Mode: " << enabled << std::endl;
}



/*********************************************************************
*
*   PROCEDURE NAME:
*       clear_log
*
*   DESCRIPTION:
*       clear assert log function
*
*********************************************************************/
void clear_log
    ( 
    core::console& c                            /* console refrence */
    )
{
/*----------------------------------------------------------
Get log references
----------------------------------------------------------*/
std::array<std::string,100>::iterator& log_itr_ref = c.get_log_itr_ref();
std::array<std::string,100>& log_ref               = c.get_log_ref();
mutex_t& mutex_ref                                 = c.get_itr_mutex();

/*----------------------------------------------------------
Reset iterator in thread safe way
----------------------------------------------------------*/
    {
    utl::mutex_lock lock( mutex_ref );
    log_itr_ref = log_ref.begin();
    }

/*----------------------------------------------------------
Add cleared assert
----------------------------------------------------------*/
c.add_assert( "assert log cleared");

/*----------------------------------------------------------
report to user log cleared
----------------------------------------------------------*/
std::cout << "log cleared" << std::endl;
}

/*********************************************************************
*
*   PROCEDURE NAME:
*       boot_sel_mode
*
*   DESCRIPTION:
*       reboots the pico into BOOTSEL
*
*********************************************************************/
void boot_sel_mode
    ( 
    core::console& c                            /* console refrence */
    )
{
/*----------------------------------------------------------
WARNING: this is an reboot causing function!

This will reboot the pico into BOOTSEL mode so that elf files,
can be loaded!

The Two Arguments passed in are:
A) 0 - no pin selected for activity LED
B) 0- to enable both interfaces (as per a cold boot)
----------------------------------------------------------*/
c.add_assert( "Rebooting into bootsel" );
reset_usb_boot( 0, 0 );

}

