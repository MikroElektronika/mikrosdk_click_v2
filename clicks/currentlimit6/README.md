\mainpage Main Page

---
# Current Limit 6 click

> Current Limit 6 Click is a compact add-on board representing a current-limiting solution. This board features the MAX17608, adjustable overvoltage, and overcurrent protection device from Maxim Integrated, now part of Analog Devices. This Click board™ is ideal for protecting systems with the flexible input overvoltage protection range from 4.5V to 60V, and the adjustable input undervoltage protection range is 4.5V to 59V. Also, the maximum current limit is 1A and can be programmed through a digital potentiometer MAX5401. When the device current reaches the programmed threshold, the device prevents further current increases by modulating the FET resistance.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/currentlimit6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/current-limit-6-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the CurrentLimit6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for CurrentLimit6 Click driver.

#### Standard key functions :

- `currentlimit6_cfg_setup` Config Object Initialization function.
```c
void currentlimit6_cfg_setup ( currentlimit6_cfg_t *cfg );
```

- `currentlimit6_init` Initialization function.
```c
err_t currentlimit6_init ( currentlimit6_t *ctx, currentlimit6_cfg_t *cfg );
```

- `currentlimit6_default_cfg` Click Default Configuration function.
```c
err_t currentlimit6_default_cfg ( currentlimit6_t *ctx );
```

#### Example key functions :

- `currentlimit6_set_current_limit` Current Limit 6 set current limit function.
```c
err_t currentlimit6_set_current_limit ( currentlimit6_t *ctx, float current_limit );
```

- `currentlimit6_power_mode` Current Limit 6 power mode function.
```c
err_t currentlimit6_power_mode ( currentlimit6_t *ctx, currentlimit6_pwr_mode_value_t pwr_mode );
```

- `currentlimit6_check_limit_exceeded` Current Limit 6 check limit exceeded function.
```c
uint8_t currentlimit6_check_limit_exceeded ( currentlimit6_t *ctx );
```

## Example Description

> This library contains API for the Current Limit 6 Click driver.
> This driver provides the functions to set the current limiting conditions 
> in order to provide the threshold of the fault conditions.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, default settings turn on the device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit6_cfg_t currentlimit6_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    currentlimit6_cfg_setup( &currentlimit6_cfg );
    CURRENTLIMIT6_MAP_MIKROBUS( currentlimit6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == currentlimit6_init( &currentlimit6, &currentlimit6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENTLIMIT6_ERROR == currentlimit6_default_cfg ( &currentlimit6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "  Current Limit 6 Click  \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    Delay_ms ( 100 );
    
    display_selection( );
    Delay_ms ( 100 );
}

```

### Application Task

> This example demonstrates the use of the Current Limit 6 Click board™.
> Reading user's input from Usart Terminal and using it as an index 
> for an array of pre-calculated values that define the current limit level.
> Results are being sent to the Usart Terminal, where you can track their changes.

```c

void application_task ( void )
{ 
    static char index;
    
    if ( log_read( &logger, &index, 1 ) != CURRENTLIMIT6_ERROR ) 
    {
        if ( ( index >= '1' ) && ( index <= '9' ) ) 
        {
            currentlimit6_set_current_limit ( &currentlimit6, limit_value[ index - 49 ] );
            log_printf( &logger, "  >>> Selected mode %d     \r\n", index - 48 );
            log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
            log_printf( &logger, " Current limit is %.3f A \r\n", limit_value[ index - 49 ] );
            log_printf( &logger, "--------------------------\r\n" );
            Delay_ms ( 100 );
        } 
        else 
        { 
            log_printf( &logger, "    Data not in range!    \r\n" );
            log_printf( &logger, "--------------------------\r\n" );
            display_selection( );
            Delay_ms ( 100 );
        }
    }
}

```

## Additional Function
- `display_selection` This function displays selection messages.
```c
static void display_selection ( void );
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.CurrentLimit6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
