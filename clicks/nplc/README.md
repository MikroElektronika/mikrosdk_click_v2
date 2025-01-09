
---
# N-PLC Click

> [N-PLC Click](https://www.mikroe.com/?pid_product=MIKROE-5502) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5502&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of an N-PLC Click boards by showing the communication between the two Click boards configured as a receiver and transmitter.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NPLC

### Example Key Functions

- `nplc_cfg_setup` Config Object Initialization function.
```c
void nplc_cfg_setup ( nplc_cfg_t *cfg );
```

- `nplc_init` Initialization function.
```c
err_t nplc_init ( nplc_t *ctx, nplc_cfg_t *cfg );
```

- `nplc_default_cfg` Click Default Configuration function.
```c
err_t nplc_default_cfg ( nplc_t *ctx );
```

- `nplc_set_mode` This function sets operation mode to command or data.
```c
void nplc_set_mode ( nplc_t *ctx, uint8_t mode );
```

- `nplc_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t nplc_generic_write ( nplc_t *ctx, char *data_in, uint16_t len );
```

- `nplc_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t nplc_generic_read ( nplc_t *ctx, char *data_out, uint16_t len );
```

### Application Init

> Initializes the driver, resets the Click board to default config, displays the firmware version and switches to data operation mode.
After that displays the selected application mode and sends an initial message in case of transmitter mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nplc_cfg_t nplc_cfg;  /**< Click config object. */

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
    nplc_cfg_setup( &nplc_cfg );
    NPLC_MAP_MIKROBUS( nplc_cfg, MIKROBUS_1 );
    if ( UART_ERROR == nplc_init( &nplc, &nplc_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    } 
    nplc_process( );
    nplc_clear_app_buf( );

    log_printf( &logger, " - HW reset -\r\n" );
    nplc_hw_reset ( &nplc );
    nplc_display_rsp ( );
    
    log_printf( &logger, " - Go to command mode -\r\n" );
    nplc_set_mode ( &nplc, NPLC_MODE_COMMAND );
    nplc_display_rsp ( );
    
    log_printf( &logger, " - Factory reset -\r\n" );
    nplc_factory_reset ( &nplc );
    nplc_display_rsp ( );
    
    log_printf( &logger, " - Reboot -\r\n" );
    nplc_sw_reset ( &nplc );
    nplc_display_rsp ( );
    
    log_printf( &logger, " - Go to command mode -\r\n" );
    nplc_set_mode ( &nplc, NPLC_MODE_COMMAND );
    nplc_display_rsp ( );
    
    log_printf( &logger, " - Show firmware version -\r\n" );
    nplc_firmware_version ( &nplc );
    nplc_display_rsp ( );
    
    log_printf( &logger, " - Go to data mode -\r\n" );
    nplc_set_mode ( &nplc, NPLC_MODE_DATA );

#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
    
    log_printf( &logger, " Sending initial message: %s", ( char * ) DEMO_TEXT_MESSAGE );
    nplc_generic_write( &nplc, DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "\r\n--------------------------------\r\n" );
    Delay_ms ( 1000 ); 
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif   
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads all the received data and echoes them back to the transmitter. The received and echoed messages will be displayed on the USB UART.

```c
void application_task ( void )
{
    nplc_process ( );
    if ( app_buf_len > 0 ) 
    {
        Delay_ms ( 500 );
        nplc_process( );
        log_printf( &logger, " Received message: %s", app_buf );
        log_printf( &logger, "\r\n--------------------------------\r\n" );
        Delay_ms ( 500 );
        log_printf( &logger, " Sending echo response: %s", app_buf );
        nplc_generic_write( &nplc, app_buf, app_buf_len );
        log_printf( &logger, "\r\n--------------------------------\r\n\n" );
        nplc_clear_app_buf( );
        Delay_ms ( 1000 ); 
    }
}
```

### Note

> Once both devices are programmed, one as a receiver and the other as a transmitter, you will need to reset the transmitter board in order
to start the communication by sending an initial message.

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
