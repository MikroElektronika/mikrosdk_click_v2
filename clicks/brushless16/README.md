\mainpage Main Page

---
# Brushless 16 click

> Brushless 16 Click is a compact add-on board suitable for controlling BLDC motors with any MCU. This board features the LB11685AV, a three-phase full-wave current-linear-drive motor driver from ON Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless_16_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/brushless-16-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the Brushless16 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless16 Click driver.

#### Standard key functions :

- `brushless16_cfg_setup` Config Object Initialization function.
```c
void brushless16_cfg_setup ( brushless16_cfg_t *cfg );
```

- `brushless16_init` Initialization function.
```c
BRUSHLESS16_RETVAL brushless16_init ( brushless16_t *ctx, brushless16_cfg_t *cfg );
```

#### Example key functions :

- `brushless16_set_en` Set en pin state
```c
void brushless16_set_en ( brushless16_t *ctx, uint8_t state );
```

- `brushless16_get_rd` Get rd pin state.
```c
uint8_t brushless16_get_rd ( brushless16_t *ctx );
```

- `brushless16_get_fg` Get fg pin state.
```c
uint8_t brushless16_get_fg ( brushless16_t *ctx );
```

## Example Description

> This example showcases ability to enable and disable motor output,
and check the status pins.

**The demo application is composed of two sections :**

### Application Init

> Initializon of UART module for log and pins for motor control.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless16_cfg_t brushless16_cfg;  /**< Click config object. */

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
    brushless16_cfg_setup( &brushless16_cfg );
    BRUSHLESS16_MAP_MIKROBUS( brushless16_cfg, MIKROBUS_1 );
    if ( brushless16_init( &brushless16, &brushless16_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms( 500 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Checks state of information pins every ms, and stop and start motor
output every second.

```c

void application_task ( void ) 
{
    static uint16_t timer = 5000;
    static uint8_t state = 1;
    
    if ( brushless16_get_rd( &brushless16 ) )
    {
        log_info( &logger, " Motor Lock" );
        Delay_ms( 500 );
    }
    
    if ( brushless16_get_fg( &brushless16 ) )
    {
        log_info( &logger, " FG" );
        Delay_ms( 500 );
    }
    
    if ( !( timer-- ) )
    {
        timer = 5000;
        
        if ( state )
        {
            log_info( &logger, " Motor stop" );
        }
        else
        {
            log_info( &logger, " Motor rotating" );
        }
        
        brushless16_set_en( &brushless16, state );
        state = !state;
    }
    
    Delay_ms( 1 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless16

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
