
---
# RS485 8 Click

> RS485 8 Click is a compact add-on board that enables communication over an RS485 network. This board features the THVD1426, an RS485 transceiver with auto-direction control and ESD protection from Texas Instruments. The THVD1426 offers bus protection for contact discharge, air gap discharge, fast transient burst, and +/-16V bus fault protection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs4858_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rs485-8-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : UART type


# Software Support

We provide a library for the RS485 8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RS485 8 Click driver.

#### Standard key functions :

- `rs4858_cfg_setup` Config Object Initialization function.
```c
void rs4858_cfg_setup ( rs4858_cfg_t *cfg );
```

- `rs4858_init` Initialization function.
```c
err_t rs4858_init ( rs4858_t *ctx, rs4858_cfg_t *cfg );
```

- `rs4858_default_cfg` Click Default Configuration function.
```c
err_t rs4858_default_cfg ( rs4858_t *ctx );
```

#### Example key functions :

- `rs4858_generic_write` RS485 8 data writing function.
```c
err_t rs4858_generic_write ( rs4858_t *ctx, uint8_t *data_in, uint16_t len );
```

- `rs4858_generic_read` RS485 8 data reading function.
```c
err_t rs4858_generic_read ( rs4858_t *ctx, uint8_t *data_out, uint16_t len );
```

- `rs4858_enable_device` RS485 8 enable the device function.
```c
void rs4858_enable_device ( rs4858_t *ctx );
```

## Example Description

> This example reads and processes data from RS485 8 clicks.
  The library also includes a function for enabling/disabling 
  the receiver or driver and data writing or reading.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rs4858_cfg_t rs4858_cfg;  /**< Click config object. */

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
    rs4858_cfg_setup( &rs4858_cfg );
    RS4858_MAP_MIKROBUS( rs4858_cfg, MIKROBUS_2 );
    if ( UART_ERROR == rs4858_init( &rs4858, &rs4858_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    rs4858_default_cfg ( &rs4858 );
    
#ifdef DEMO_APP_TRANSMITTER
    log_info( &logger, "---- Transmitter mode ----" );
#else
    log_info( &logger, "---- Receiver mode ----" );
#endif 
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

```

### Application Task

> This example demonstrates the use of the RS485 8 Click board.
  The app sends a "MikroE" message, reads the received data and parses it.
  Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    rs4858_generic_write( &rs4858, data_buf, strlen( data_buf ) );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    rs4858_process( );
#endif 
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RS4858

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
