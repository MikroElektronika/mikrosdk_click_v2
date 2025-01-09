
---
# OBDII Click

> [OBDII Click](https://www.mikroe.com/?pid_product=MIKROE-2452) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2452&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of OBDII Click board by reading the engine RPM and vehicle speed and displaying results on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.OBDII

### Example Key Functions

- `obdii_cfg_setup` Config Object Initialization function.
```c
void obdii_cfg_setup ( obdii_cfg_t *cfg );
```

- `obdii_init` Initialization function.
```c
err_t obdii_init ( obdii_t *ctx, obdii_cfg_t *cfg );
```

- `obdii_send_command` This function sends command string by using UART serial interface.
```c
void obdii_send_command ( obdii_t *ctx, uint8_t *cmd );
```

- `obdii_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t obdii_generic_read ( obdii_t *ctx, uint8_t *data_out, uint16_t len );
```

- `obdii_reset_device` This function resets the device by toggling the RST pin.
```c
void obdii_reset_device ( obdii_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    obdii_cfg_t obdii_cfg;  /**< Click config object. */

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
    obdii_cfg_setup( &obdii_cfg );
    OBDII_MAP_MIKROBUS( obdii_cfg, MIKROBUS_1 );
    if ( UART_ERROR == obdii_init( &obdii, &obdii_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    obdii_reset_device ( &obdii );
    
    obdii_process ( &obdii );
    obdii_clear_app_buf ( );
    
    log_printf( &logger, "> Reset device\r\n" );
    obdii_send_command ( &obdii, OBDII_CMD_RESET_DEVICE );
    obdii_rsp_check ( &obdii, OBDII_RSP_PROMPT );
    obdii_log_app_buf ( );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Disable echo\r\n" );
    obdii_send_command ( &obdii, OBDII_CMD_DISABLE_ECHO );
    obdii_rsp_check ( &obdii, OBDII_RSP_PROMPT );
    obdii_log_app_buf ( );
    
    log_printf( &logger, " Remove spaces\r\n" );
    obdii_send_command ( &obdii, OBDII_CMD_SPACES_OFF );
    obdii_rsp_check ( &obdii, OBDII_RSP_PROMPT );
    obdii_log_app_buf ( );
}
```

### Application Task

> Reads and processes the engine RPM and vehicle speed and displays the results on the USB UART once per second.

```c
void application_task ( void )
{
    uint8_t * __generic_ptr start_ptr = NULL;
    uint8_t data_buf[ 5 ] = { 0 };
    uint16_t rpm = 0;
    uint8_t speed = 0;
    
    log_printf( &logger, " Get current RPM\r\n" );
    obdii_send_command ( &obdii, OBDII_CMD_GET_CURRENT_RPM );
    obdii_rsp_check ( &obdii, OBDII_RSP_PROMPT );
    start_ptr = strstr( app_buf, OBDII_RSP_CURRENT_RPM );
    if ( start_ptr )
    {
        memcpy ( data_buf, ( start_ptr + 4 ), 4 );
        data_buf[ 4 ] = 0;
        rpm = hex_to_uint16( data_buf ) / 4;
        log_printf( &logger, "RPM: %u\r\n\n>", rpm );
    }
    else
    {
        obdii_log_app_buf ( );
    }
    
    log_printf( &logger, " Get current speed\r\n" );
    obdii_send_command ( &obdii, OBDII_CMD_GET_CURRENT_SPEED );
    obdii_rsp_check ( &obdii, OBDII_RSP_PROMPT );
    start_ptr = strstr( app_buf, OBDII_RSP_CURRENT_SPEED );
    if ( start_ptr )
    {
        memcpy ( data_buf, ( start_ptr + 4 ), 2 );
        data_buf[ 2 ] = 0;
        speed = hex_to_uint8( data_buf );
        log_printf( &logger, "Speed: %u km/h\r\n\n>", ( uint16_t ) speed );
    }
    else
    {
        obdii_log_app_buf ( );
    }
    Delay_ms ( 1000 );
}
```

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
