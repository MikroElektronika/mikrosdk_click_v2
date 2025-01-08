
---
# RS485 Isolator 4 Click

> [RS485 Isolator 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6316) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6316&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of an RS485 Isolator 4 Click board by showing
the communication between the two Click board configured as a receiver and transmitter.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RS485Isolator4

### Example Key Functions

- `rs485isolator4_cfg_setup` Config Object Initialization function.
```c
void rs485isolator4_cfg_setup ( rs485isolator4_cfg_t *cfg );
```

- `rs485isolator4_init` Initialization function.
```c
err_t rs485isolator4_init ( rs485isolator4_t *ctx, rs485isolator4_cfg_t *cfg );
```

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

### Note

> Make sure to provide a power supply voltage to isolated VCC_EXT and GND pins in a range from 3V to 5.5V.

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
