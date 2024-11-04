\mainpage Main Page

---
# RS485 Isolator 3 Click

> RS485 Isolator 3 Click is a compact add-on board that provides electrical isolation and signal conditioning for RS485 communication systems. This board features the ADM2763E, a 500kbps, 5.7kV RMS, signal-isolated RS-485 transceiver from Analog Devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs485isolator3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rs485-isolator-3-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Mar 2023.
- **Type**          : UART type


# Software Support

We provide a library for the RS485 Isolator 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RS485 Isolator 3 Click driver.

#### Standard key functions :

- `rs485isolator3_cfg_setup` Config Object Initialization function.
```c
void rs485isolator3_cfg_setup ( rs485isolator3_cfg_t *cfg );
```

- `rs485isolator3_init` Initialization function.
```c
err_t rs485isolator3_init ( rs485isolator3_t *ctx, rs485isolator3_cfg_t *cfg );
```

- `rs485isolator3_default_cfg` Click Default Configuration function.
```c
void rs485isolator3_default_cfg ( rs485isolator3_t *ctx );
```

#### Example key functions :

- `rs485isolator3_enable_receiver_input` RS485 Isolator 3 enable receiver input function.
```c
void rs485isolator3_enable_receiver_input ( rs485isolator3_t *ctx );
```

- `rs485isolator3_disable_receiver_input` RS485 Isolator 3 disable receiver input function.
```c
void rs485isolator3_disable_receiver_input ( rs485isolator3_t *ctx );
```

- `rs485isolator3_disable_output` RS485 Isolator 3 disable output function.
```c
void rs485isolator3_disable_output ( rs485isolator3_t *ctx );
```

## Example Description

> This example reads and processes data from RS485 Isolator 3 clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables the selected mode.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rs485isolator3_cfg_t rs485isolator3_cfg;  /**< Click config object. */

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
    rs485isolator3_cfg_setup( &rs485isolator3_cfg );
    RS485ISOLATOR3_MAP_MIKROBUS( rs485isolator3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == rs485isolator3_init( &rs485isolator3, &rs485isolator3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    rs485isolator3_default_cfg ( &rs485isolator3 );
    
#ifdef DEMO_APP_RECEIVER
    rs485isolator3_enable_receiver_input( &rs485isolator3 );
    rs485isolator3_disable_output( &rs485isolator3 );
    log_info( &logger, "---- Receiver mode ----" );
#endif 
#ifdef DEMO_APP_TRANSMITTER
    rs485isolator3_disable_receiver_input( &rs485isolator3 );
    rs485isolator3_enable_output( &rs485isolator3 );    
    log_info( &logger, "---- Transmitter mode ----" );
#endif
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message
 every 2 seconds.

```c
void application_task ( void ) 
{
#ifdef DEMO_APP_RECEIVER
    rs485isolator3_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    rs485isolator3_generic_write( &rs485isolator3, data_buf, strlen( data_buf ) );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif    

}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RS485Isolator3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
