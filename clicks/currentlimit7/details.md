
---
# Current Limit 7 click

> Current Limit 7 Click is a compact add-on board representing a current-limiting solution. This board features the MAX14575A, an adjustable current-limit switch from Analog Devices. This Click board™ features internal current limiting to prevent damage to host devices due to faulty load conditions, has a low 32mΩ on-resistance, and operates from a 2.3V to 5.5V input voltage range. Also, the current limit is adjustable from 250mA to 2.5A programmed through AD5272 digital rheostat and set via onboard range switch. This Click board™ is suitable for applications in portable equipment and condition monitoring or power supplies, protecting them in short circuits or other overload conditions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/currentlimit7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/current-limit-7-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Current Limit 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Current Limit 7 Click driver.

#### Standard key functions :

- `currentlimit7_cfg_setup` Config Object Initialization function.
```c
void currentlimit7_cfg_setup ( currentlimit7_cfg_t *cfg );
```

- `currentlimit7_init` Initialization function.
```c
err_t currentlimit7_init ( currentlimit7_t *ctx, currentlimit7_cfg_t *cfg );
```

- `currentlimit7_default_cfg` Click Default Configuration function.
```c
err_t currentlimit7_default_cfg ( currentlimit7_t *ctx );
```

#### Example key functions :

- `currentlimit7_set_current_limit` Current Limit 7 set current limit function.
```c
err_t currentlimit7_set_current_limit ( currentlimit7_t *ctx, uint8_t op_mode, uint16_t current_limit_ma );
```

- `currentlimit7_set_resistance` Current Limit 7 set resistance function.
```c
err_t currentlimit7_set_resistance ( currentlimit7_t *ctx, uint32_t res_ohm );
```

- `currentlimit7_get_fault` Current Limit 7 get fault function.
```c
uint8_t currentlimit7_get_fault ( currentlimit7_t *ctx );
```

## Example Description

> This library contains API for the Current Limit 7 Click driver.
> This driver provides the functions to set the current limiting conditions 
> in order to provide the threshold of the fault conditions.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, default settings turn on the device.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit7_cfg_t currentlimit7_cfg;  /**< Click config object. */

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
    currentlimit7_cfg_setup( &currentlimit7_cfg );
    CURRENTLIMIT7_MAP_MIKROBUS( currentlimit7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == currentlimit7_init( &currentlimit7, &currentlimit7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENTLIMIT7_ERROR == currentlimit7_default_cfg ( &currentlimit7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "   Current Limit 7 Click   \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
    
#ifdef CURRENTLIMIT_MODE_250_mA_500_mA
    currentlimit7_set_current_limit ( &currentlimit7, CURRENTLIMIT7_OP_MODE_250_mA_500_mA, limit_value_op[ 10 ] );
    log_printf( &logger, "  >>> Selected mode %d     \r\n", 0 );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " Current limit is %d mA    \r\n", limit_value_op[ 10 ] );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
#else
    currentlimit7_set_current_limit ( &currentlimit7, CURRENTLIMIT7_OP_MODE_500_mA_2500_mA, limit_value_op[ 0 ] );
    log_printf( &logger, "  >>> Selected mode %d     \r\n", 0 );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " Current limit is %d mA    \r\n", limit_value_op[ 0 ] );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
#endif
    
    display_selection( );
    Delay_ms ( 100 );
}

```

### Application Task

> This example demonstrates the use of the Current Limit 7 Click board™.
> Reading user's input from Usart Terminal and using it as an index 
> for an array of pre-calculated values that define the current limit level.
> Results are being sent to the Usart Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static char index;
    
    if ( CURRENTLIMIT7_ERROR != log_read( &logger, &index, 1 ) ) 
    {
    #ifdef CURRENTLIMIT_MODE_250_mA_500_mA
        if ( ( index >= '0' ) && ( index <= '3' ) )
        {
            currentlimit7_set_current_limit ( &currentlimit7, CURRENTLIMIT7_OP_MODE_250_mA_500_mA, limit_value_op[ index - 38 ] );
            log_printf( &logger, "  >>> Selected mode %d     \r\n", index - 48 );
            log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
            log_printf( &logger, "  Current limit is %d mA   \r\n", limit_value_op[ index - 38 ] );
            log_printf( &logger, "---------------------------\r\n" );
            Delay_ms ( 100 );
        }
    #else
        if ( ( index >= '0' ) && ( index <= '9' ) ) 
        {
            currentlimit7_set_current_limit ( &currentlimit7, CURRENTLIMIT7_OP_MODE_500_mA_2500_mA, limit_value_op[ index - 48 ] );
            log_printf( &logger, "  >>> Selected mode %d     \r\n", index - 48 );
            log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
            log_printf( &logger, "  Current limit is %d mA   \r\n", limit_value_op[ index - 48 ] );
            log_printf( &logger, "---------------------------\r\n" );
            Delay_ms ( 100 );
        }
    #endif
        else 
        { 
            log_printf( &logger, "    Data not in range!    \r\n" );
            log_printf( &logger, "---------------------------\r\n" );
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
- Click.CurrentLimit7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
