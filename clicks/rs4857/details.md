
---
# RS485 7 click

> RS485 7 Click is a compact add-on board that enables communication over an RS485 network. 
> This board features the THVD1424, a full duplex RS485 transceiver 
> with a selectable data rate from Texas Instruments. 
> The THVD1424 offers several pin-controlled features, including an on-chip 120Ω termination resistor, 
> slew rate control, and the ability to switch between half and full duplex mode. 
> With its high immunity to IEC Contact Discharge ESD events, 
> the bus pins require no additional system-level protection components. 
> Additionally, the chip is known for its low power consumption and 
> glitch-free power-up/power-down functionality, which enables hot plug-in capability.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs4857_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rs485-7-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2023.
- **Type**          : UART type


# Software Support

We provide a library for the RS485 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RS485 7 Click driver.

#### Standard key functions :

- `rs4857_cfg_setup` Config Object Initialization function.
```c
void rs4857_cfg_setup ( rs4857_cfg_t *cfg );
```

- `rs4857_init` Initialization function.
```c
err_t rs4857_init ( rs4857_t *ctx, rs4857_cfg_t *cfg );
```

#### Example key functions :

- `rs4857_receiver_enable` RS485 7 enables the receiver function.
```c
void rs4857_receiver_enable ( rs4857_t *ctx );
```

- `rs4857_driver_enable` RS485 7 enables the driver function.
```c
void rs4857_driver_enable ( rs4857_t *ctx );
```

## Example Description

> This example reads and processes data from RS485 7 clicks.
> The library also includes a function for enabling/disabling 
> the receiver or driver and data writing or reading.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver performs wake-up module and enables the selected mode.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rs4857_cfg_t rs4857_cfg;  /**< Click config object. */

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
    rs4857_cfg_setup( &rs4857_cfg );
    RS4857_MAP_MIKROBUS( rs4857_cfg, MIKROBUS_1 );
    if ( UART_ERROR == rs4857_init( &rs4857, &rs4857_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    app_buf_len = 0;
    
    rs4857_termination_xy_enable( &rs4857 );
    rs4857_termination_ab_enable( &rs4857 );
    
    rs4857_receiver_enable( &rs4857 );
    rs4857_driver_enable( &rs4857 );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the RS485 7 Click board™.
> The app sends a "MikroE" message, reads the received data and parses it.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{  
    if ( rs4857_generic_write( &rs4857, DEMO_MESSAGE, 10 ) )
    {
        rs4857_process( );
        if ( app_buf_len > 0 )
        {
            log_printf( &logger, "%s", app_buf );
            rs4857_clear_app_buf( );
        }
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Note

> Operation Mode: Full duplex. 
> Transmitter: Y and Z.
> Receiver: A and B.
> Wire connection: Y-A, Z-B.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RS4857

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
