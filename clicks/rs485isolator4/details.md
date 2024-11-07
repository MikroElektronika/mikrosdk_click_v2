
---
# RS485 Isolator 4 Click

> RS485 Isolator 4 Click is a compact add-on board designed for robust RS-485 and RS-422 half-duplex communication with galvanic isolation. This board features the ISO1450, a 5kVRMS isolated RS-485 transceiver from Texas Instruments. The ISO1450 supports data rates up to 50Mbps and features advanced protection against electrostatic discharge (ESD) and electrical fast transients (EFT), ensuring reliable long-distance communication in industrial environments. It operates over a wide supply voltage range (3V to 5.5V), offering failsafe protection against open, short, and idle bus states.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs485isolator4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rs485-isolator-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : UART type


# Software Support

We provide a library for the RS485 Isolator 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RS485 Isolator 4 Click driver.

#### Standard key functions :

- `rs485isolator4_cfg_setup` Config Object Initialization function.
```c
void rs485isolator4_cfg_setup ( rs485isolator4_cfg_t *cfg );
```

- `rs485isolator4_init` Initialization function.
```c
err_t rs485isolator4_init ( rs485isolator4_t *ctx, rs485isolator4_cfg_t *cfg );
```

#### Example key functions :

- `rs485isolator4_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t rs485isolator4_generic_write ( rs485isolator4_t *ctx, uint8_t *data_in, uint16_t len );
```

- `rs485isolator4_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t rs485isolator4_generic_read ( rs485isolator4_t *ctx, uint8_t *data_out, uint16_t len );
```

- `rs485isolator4_driver_enable` This function enables the driver input by setting the DE pin to high logic state.
```c
void rs485isolator4_driver_enable ( rs485isolator4_t *ctx );
```

## Example Description

> This example demonstrates the use of an RS485 Isolator 4 Click board by showing
the communication between the two Click board configured as a receiver and transmitter.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and displays the selected application mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rs485isolator4_cfg_t rs485isolator4_cfg;  /**< Click config object. */

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
    rs485isolator4_cfg_setup( &rs485isolator4_cfg );
    RS485ISOLATOR4_MAP_MIKROBUS( rs485isolator4_cfg, MIKROBUS_1 );
    if ( UART_ERROR == rs485isolator4_init( &rs485isolator4, &rs485isolator4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
#ifdef DEMO_APP_TRANSMITTER
    rs485isolator4_driver_enable ( &rs485isolator4 );
    rs485isolator4_receiver_disable ( &rs485isolator4 );
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    rs485isolator4_driver_disable ( &rs485isolator4 );
    rs485isolator4_receiver_enable ( &rs485isolator4 );
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c
void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    rs485isolator4_generic_write( &rs485isolator4, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms( 1000 );
    Delay_ms( 1000 );
#else
    uint8_t rx_data = 0;
    if ( rs485isolator4_generic_read( &rs485isolator4, &rx_data, 1 ) > 0 )
    {
        log_printf( &logger, "%c", rx_data );
    }
#endif
}
```

## Note

> Make sure to provide a power supply voltage to isolated VCC_EXT and GND pins in a range from 3V to 5.5V.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RS485Isolator4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
