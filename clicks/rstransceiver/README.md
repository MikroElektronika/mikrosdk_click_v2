\mainpage Main Page

---
# RS Transceiver Click

> RS Transceiver is a compact add-on board that offers an interface between the TTL level UART and 
> RS-232/RS-422/RS-485 communication buses. This board features the XR34350, 
> an RS-232/RS-422/RS-485 serial transceiver with internal termination and wide output swing from MaxLinear. 
> Integrated cable termination and four configuration modes allow all three protocols 
> to be used interchangeably over a single cable over the DE-9 connector. 
> All transmitter outputs and receiver inputs feature robust ESD protection and HBM up to ±15kV.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rstransceiver_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rs-transceiver-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the RS Transceiver Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RS Transceiver Click driver.

#### Standard key functions :

- `rstransceiver_cfg_setup` Config Object Initialization function.
```c
void rstransceiver_cfg_setup ( rstransceiver_cfg_t *cfg );
```

- `rstransceiver_init` Initialization function.
```c
err_t rstransceiver_init ( rstransceiver_t *ctx, rstransceiver_cfg_t *cfg );
```

- `rstransceiver_default_cfg` Click Default Configuration function.
```c
err_t rstransceiver_default_cfg ( rstransceiver_t *ctx );
```

#### Example key functions :

- `rstransceiver_set_op_mode` RS Transceiver sets the operating mode function.
```c
err_t rstransceiver_set_op_mode ( rstransceiver_t *ctx, uint8_t op_mode );
```

- `rstransceiver_mode_full_duplex` RS Transceiver sets the Full-Duplex mode function.
```c
err_t rstransceiver_mode_full_duplex ( rstransceiver_t *ctx, uint8_t slew, uint8_t dir1, uint8_t term );
```

- `rstransceiver_device_enable` RS Transceiver enables the device function.
```c
void rstransceiver_device_enable ( rstransceiver_t *ctx );
```

## Example Description

> This example reads and processes data from RS Transceiver Click board™.
> The library also includes a function for selecting the desired operating mode, 
> enabling/disabling the receiver or driver and data writing or reading.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C and UART module and log UART.
> After driver initialization, default settings turn on the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rstransceiver_cfg_t rstransceiver_cfg;  /**< Click config object. */

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
    rstransceiver_cfg_setup( &rstransceiver_cfg );
    RSTRANSCEIVER_MAP_MIKROBUS( rstransceiver_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rstransceiver_init( &rstransceiver, &rstransceiver_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( RSTRANSCEIVER_ERROR == rstransceiver_default_cfg ( &rstransceiver ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the RS Transceiver Click board™.
> The app shows the device configured in loopback mode,
> sends a "MikroE" message, reads the received data and parses it.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( rstransceiver_generic_write( &rstransceiver, DEMO_MESSAGE, strlen( DEMO_MESSAGE ) ) )
    {
        if ( rstransceiver_generic_read( &rstransceiver, app_buf, strlen( DEMO_MESSAGE ) ) )
        {
            log_printf( &logger, "%s", app_buf );
            memset( app_buf, 0, PROCESS_BUFFER_SIZE );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RSTransceiver

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
