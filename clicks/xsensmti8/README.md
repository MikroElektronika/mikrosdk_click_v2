
---
# XSENS MTi-8 Click

> [XSENS MTi-8 Click](https://www.mikroe.com/?pid_product=MIKROE-6660) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6660&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2025.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the initialization and use of the XSENS MTi-8 Click board.
It performs device identification, configures the output data streams, and displays 
various sensor measurements such as orientation (quaternion and Euler angles), 
magnetic field, latitude and longitude, altitude, barometric pressure, temperature, 
and UTC time. The data is received in the MTData2 format and parsed accordingly.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.XSENSMTi8

### Example Key Functions

- `xsensmti8_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void xsensmti8_cfg_setup ( xsensmti8_cfg_t *cfg );
```

- `xsensmti8_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t xsensmti8_init ( xsensmti8_t *ctx, xsensmti8_cfg_t *cfg );
```

- `xsensmti8_send_message` This function sends a desired command message from the Click context object.
```c
err_t xsensmti8_send_message ( xsensmti8_t *ctx );
```

- `xsensmti8_read_message` This function reads response message from the ring buffer and stores it in the Click context object.
```c
err_t xsensmti8_read_message ( xsensmti8_t *ctx );
```

- `xsensmti8_wait_message` This function waits and checks for a specific message ID in the received response.
```c
err_t xsensmti8_wait_message ( xsensmti8_t *ctx, uint8_t msg_id );
```

### Application Init

> Initializes the logger and the XSENS MTi-8 Click driver, resets the device, 
retrieves the device and firmware information, and sets the desired output configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    xsensmti8_cfg_t xsensmti8_cfg;  /**< Click config object. */

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
    xsensmti8_cfg_setup( &xsensmti8_cfg );
    XSENSMTI8_MAP_MIKROBUS( xsensmti8_cfg, MIKROBUS_POSITION_XSENSMTI8 );
    if ( UART_ERROR == xsensmti8_init( &xsensmti8, &xsensmti8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, ">> Reset Device\r\n" );
    xsensmti8_reset_device ( &xsensmti8 );
    if ( XSENSMTI8_OK == xsensmti8_wait_message ( &xsensmti8, XSENSMTI8_MID_WAKE_UP ) )
    {
        xsensmti8_parse_message ( &xsensmti8 );
    }
    
    log_printf( &logger, ">> Get Device ID\r\n" );
    xsensmti8.cmd_msg.msg_id = XSENSMTI8_MID_DEVICE_ID;
    xsensmti8.cmd_msg.data_len = 0;
    xsensmti8_send_message ( &xsensmti8 );
    if ( XSENSMTI8_OK == xsensmti8_wait_message ( &xsensmti8, XSENSMTI8_MID_DEVICE_ID_ACK ) )
    {
        xsensmti8_parse_message ( &xsensmti8 );
    }
    
    log_printf( &logger, ">> Get Product Code\r\n" );
    xsensmti8.cmd_msg.msg_id = XSENSMTI8_MID_PRODUCT_CODE;
    xsensmti8.cmd_msg.data_len = 0;
    xsensmti8_send_message ( &xsensmti8 );
    if ( XSENSMTI8_OK == xsensmti8_wait_message ( &xsensmti8, XSENSMTI8_MID_PRODUCT_CODE_ACK ) )
    {
        xsensmti8_parse_message ( &xsensmti8 );
    }
    
    log_printf( &logger, ">> Get HW Version\r\n" );
    xsensmti8.cmd_msg.msg_id = XSENSMTI8_MID_HARDWARE_VERSION;
    xsensmti8.cmd_msg.data_len = 0;
    xsensmti8_send_message ( &xsensmti8 );
    if ( XSENSMTI8_OK == xsensmti8_wait_message ( &xsensmti8, XSENSMTI8_MID_HARDWARE_VERSION_ACK ) )
    {
        xsensmti8_parse_message ( &xsensmti8 );
    }
    
    log_printf( &logger, ">> Get FW Version\r\n" );
    xsensmti8.cmd_msg.msg_id = XSENSMTI8_MID_FW_REV;
    xsensmti8.cmd_msg.data_len = 0;
    xsensmti8_send_message ( &xsensmti8 );
    if ( XSENSMTI8_OK == xsensmti8_wait_message ( &xsensmti8, XSENSMTI8_MID_FW_REV_ACK ) )
    {
        xsensmti8_parse_message ( &xsensmti8 );
    }
    
    log_printf( &logger, ">> Set Output Configuration\r\n" );
    xsensmti8.cmd_msg.msg_id = XSENSMTI8_MID_OUTPUT_CONFIGURATION;
    xsensmti8.cmd_msg.data_len = 32;
    xsensmti8.cmd_msg.data_buf[ 0 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_QUARTERNION >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 1 ] = ( uint8_t ) ( XSENSMTI8_XDI_QUARTERNION & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 2 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_FREQUENCY_5HZ >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 3 ] = ( uint8_t ) ( XSENSMTI8_XDI_FREQUENCY_5HZ & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 4 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_EULER_ANGLES >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 5 ] = ( uint8_t ) ( XSENSMTI8_XDI_EULER_ANGLES & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 6 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_FREQUENCY_5HZ >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 7 ] = ( uint8_t ) ( XSENSMTI8_XDI_FREQUENCY_5HZ & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 8 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_MAGNETIC_FIELD >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 9 ] = ( uint8_t ) ( XSENSMTI8_XDI_MAGNETIC_FIELD & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 10 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_FREQUENCY_5HZ >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 11 ] = ( uint8_t ) ( XSENSMTI8_XDI_FREQUENCY_5HZ & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 12 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_LAT_LON >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 13 ] = ( uint8_t ) ( XSENSMTI8_XDI_LAT_LON & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 14 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_FREQUENCY_5HZ >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 15 ] = ( uint8_t ) ( XSENSMTI8_XDI_FREQUENCY_5HZ & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 16 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_ALTITUDE_ELLIPSOID >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 17 ] = ( uint8_t ) ( XSENSMTI8_XDI_ALTITUDE_ELLIPSOID & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 18 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_FREQUENCY_5HZ >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 19 ] = ( uint8_t ) ( XSENSMTI8_XDI_FREQUENCY_5HZ & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 20 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_BARO_PRESSURE >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 21 ] = ( uint8_t ) ( XSENSMTI8_XDI_BARO_PRESSURE & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 22 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_FREQUENCY_5HZ >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 23 ] = ( uint8_t ) ( XSENSMTI8_XDI_FREQUENCY_5HZ & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 24 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_TEMPERATURE >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 25 ] = ( uint8_t ) ( XSENSMTI8_XDI_TEMPERATURE & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 26 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_FREQUENCY_5HZ >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 27 ] = ( uint8_t ) ( XSENSMTI8_XDI_FREQUENCY_5HZ & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 28 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_UTC_TIME >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 29 ] = ( uint8_t ) ( XSENSMTI8_XDI_UTC_TIME & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 30 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_FREQUENCY_5HZ >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 31 ] = ( uint8_t ) ( XSENSMTI8_XDI_FREQUENCY_5HZ & 0xFF );
    xsensmti8_send_message ( &xsensmti8 );
    if ( XSENSMTI8_OK == xsensmti8_wait_message ( &xsensmti8, XSENSMTI8_MID_OUTPUT_CONFIGURATION_ACK ) )
    {
        xsensmti8_parse_message ( &xsensmti8 );
    }
    
    log_printf( &logger, ">> Go to Measurement\r\n" );
    xsensmti8.cmd_msg.msg_id = XSENSMTI8_MID_GO_TO_MEASUREMENT;
    xsensmti8.cmd_msg.data_len = 0;
    xsensmti8_send_message ( &xsensmti8 );
    if ( XSENSMTI8_OK == xsensmti8_wait_message ( &xsensmti8, XSENSMTI8_MID_GO_TO_MEASUREMENT_ACK ) )
    {
        xsensmti8_parse_message ( &xsensmti8 );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads and parses the incoming MTData2 messages and displays the decoded sensor data via the logger terminal.

```c
void application_task ( void )
{
    if ( XSENSMTI8_OK == xsensmti8_read_message( &xsensmti8 ) ) 
    {
        xsensmti8_parse_message ( &xsensmti8 );
    }
}
```

### Note

> For the GNSS functionality, make sure the GNSS RTK Click with a valid GNSS antenna is connected to the MTi-8 Click board.

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
