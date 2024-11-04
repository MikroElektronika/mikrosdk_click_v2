\mainpage Main Page

---
# eFuse 7 Click

> eFuse 7 Click is a compact add-on board with a power path protection solution that limits circuit currents and voltages to safe levels during fault conditions. This board features the LS12052BD33, an eFuse with over-voltage protection and blocking FET control from Littelfuse. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/efuse7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/efuse-7-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the eFuse 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for eFuse 7 Click driver.

#### Standard key functions :

- `efuse7_cfg_setup` Config Object Initialization function.
```c
void efuse7_cfg_setup ( efuse7_cfg_t *cfg );
```

- `efuse7_init` Initialization function.
```c
err_t efuse7_init ( efuse7_t *ctx, efuse7_cfg_t *cfg );
```

- `efuse7_default_cfg` Click Default Configuration function.
```c
err_t efuse7_default_cfg ( efuse7_t *ctx );
```

#### Example key functions :

- `efuse7_enable_output` eFuse 7 output enable function.
```c
void efuse7_enable_output ( efuse7_t *ctx );
```

- `efuse7_wiper_inc` eFuse 7 wiper position increase function.
```c
void efuse7_wiper_inc ( efuse7_t *ctx, uint8_t inc_num );
```

- `efuse7_set_limit` eFuse 7 set current limit function.
```c
err_t efuse7_set_limit ( efuse7_t *ctx, uint8_t set_current );
```

## Example Description

> This library contains API for the eFuse 7 Click driver.
  This driver provides the functions to set the current limiting conditions 
  in order to provide the threshold of the fault conditions.

**The demo application is composed of two sections :**

### Application Init

> Initialization of Click module and UART log, then performing default 
  configuration and setting a current limit to 1A.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    efuse7_cfg_t efuse7_cfg;  /**< Click config object. */

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
    efuse7_cfg_setup( &efuse7_cfg );
    EFUSE7_MAP_MIKROBUS( efuse7_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == efuse7_init( &efuse7, &efuse7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EFUSE7_ERROR == efuse7_default_cfg ( &efuse7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    display_selection( );
    Delay_ms ( 100 );
}

```

### Application Task

> This example demonstrates the use of the eFuse 7 Click board.
  Reading user's input from UART Terminal and using it as an index 
  for an array of pre-calculated values that define the current limit level.
  Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static char index;
    
    if ( 1 == log_read( &logger, &index, 1 ) ) 
    {
        if ( ( index >= '0' ) && ( index <= '7' ) ) 
        {
            efuse7_set_limit ( &efuse7, limit_value_op[ index - 48 ] );
            log_printf( &logger, "  >>> Selected mode %c     \r\n", index );
            log_printf( &logger, "---------------------------\r\n" );
            Delay_ms ( 100 );
        }
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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.eFuse7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
