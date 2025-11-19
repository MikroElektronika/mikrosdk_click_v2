
---
# CAN-LIN SBC Click

> [CAN-LIN SBC Click](https://www.mikroe.com/?pid_product=MIKROE-6530) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6530&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2025.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of an CAN-LIN SBC Click board by showing the communication between the two Click boards.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CANLINSBC

### Example Key Functions

- `canlinsbc_cfg_setup` Config Object Initialization function.
```c
void canlinsbc_cfg_setup ( canlinsbc_cfg_t *cfg );
```

- `canlinsbc_init` Initialization function.
```c
err_t canlinsbc_init ( canlinsbc_t *ctx, canlinsbc_cfg_t *cfg );
```

- `canlinsbc_default_cfg` Click Default Configuration function.
```c
err_t canlinsbc_default_cfg ( canlinsbc_t *ctx );
```

- `canlinsbc_generic_write` This function writes a specified number of bytes to the CAN LIN SBC device using UART communication.
```c
err_t canlinsbc_generic_write ( canlinsbc_t *ctx, uint8_t *data_in, uint16_t len );
```

- `canlinsbc_generic_read` This function reads a specified number of bytes from the CAN LIN SBC device using UART communication.
```c
err_t canlinsbc_generic_read ( canlinsbc_t *ctx, uint8_t *data_out, uint16_t len );
```

### Application Init

> Initializes the driver and logger, and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    canlinsbc_cfg_t canlinsbc_cfg;  /**< Click config object. */

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
    canlinsbc_cfg_setup( &canlinsbc_cfg );
    CANLINSBC_MAP_MIKROBUS( canlinsbc_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == canlinsbc_init( &canlinsbc, &canlinsbc_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CANLINSBC_ERROR == canlinsbc_default_cfg ( &canlinsbc ) )
    {
        log_error( &logger, " Default configuration." );
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

> Depending on the selected application mode, it reads all the received data or sends the desired message once per second.

```c
void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    canlinsbc_generic_write( &canlinsbc, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms( 1000 );
#else
    uint8_t rx_data = 0;
    if ( canlinsbc_generic_read( &canlinsbc, &rx_data, 1 ) > 0 )
    {
        log_printf( &logger, "%c", rx_data );
    }
#endif
}
```

### Note

> Ensure the two Click boards are connected properly using an RS232 cable and a 12V external power supply is provided to the VEXT pin.

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
