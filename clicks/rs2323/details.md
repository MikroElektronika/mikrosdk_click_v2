
---
# RS232 3 Click

> RS232 3 Click is a compact add-on board representing a universal usable RS232 transceiver. This board features the SP3221E, a low-power RS232 transceiver from MaxLinear. The SP3221E uses an internal high-efficiency, charge-pump power supply and is compliant with EIA/TIA-232-F standards when powered by any of the mikroBUS™ power rails. The AUTO ON-LINE® feature allows the SP3221E to automatically "Wake-Up" from a Shutdown state when an RS232 cable is connected and a peripheral device is turned on. When not connected or not in use, the SP3221E will automatically shut down, drawing less supply current.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs2323_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rs232-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : UART type


# Software Support

We provide a library for the RS232 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RS232 3 Click driver.

#### Standard key functions :

- `rs2323_cfg_setup` Config Object Initialization function.
```c
void rs2323_cfg_setup ( rs2323_cfg_t *cfg );
```

- `rs2323_init` Initialization function.
```c
err_t rs2323_init ( rs2323_t *ctx, rs2323_cfg_t *cfg );
```

#### Example key functions :

- `rs2323_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t rs2323_generic_write ( rs2323_t *ctx, char *data_buf, uint16_t len );
```

- `rs2323_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t rs2323_generic_read ( rs2323_t *ctx, char *data_buf, uint16_t max_len );
```

## Example Description

> This example demonstrates the use of an RS232 3 Click board by showing the communication between the two Click board configured as a receiver and transmitter.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and displays the selected application mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rs2323_cfg_t rs2323_cfg;  /**< Click config object. */

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
    rs2323_cfg_setup( &rs2323_cfg );
    RS2323_MAP_MIKROBUS( rs2323_cfg, MIKROBUS_1 );
    if ( UART_ERROR == rs2323_init( &rs2323, &rs2323_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif   
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 3 seconds.

```c
void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    rs2323_generic_write( &rs2323, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 ); 
#else
    uint8_t rx_data;
    if ( rs2323_generic_read( &rs2323, &rx_data, 1 ) > 0 )
    {
        log_printf( &logger, "%c", rx_data );
    }
#endif
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RS2323

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
