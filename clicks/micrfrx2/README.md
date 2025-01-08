
---
# MICRF RX 2 Click

> [MICRF RX 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6015) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6015&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of MICRF RX 2 Click board by reading and parsing packet messages received from the transmitter.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MICRFRX2

### Example Key Functions

- `micrfrx2_cfg_setup` Config Object Initialization function.
```c
void micrfrx2_cfg_setup ( micrfrx2_cfg_t *cfg );
```

- `micrfrx2_init` Initialization function.
```c
err_t micrfrx2_init ( micrfrx2_t *ctx, micrfrx2_cfg_t *cfg );
```

- `micrfrx2_enable_device` This function enables device by setting the SHD pin to low logic state.
```c
void micrfrx2_enable_device ( micrfrx2_t *ctx );
```

- `micrfrx2_wait_ready` This function waits for all training bytes to arrive which indicates data ready.
```c
static void micrfrx2_wait_ready ( micrfrx2_t *ctx );
```

- `micrfrx2_read_packet` This function reads data packet and stores it in a packet_buf only if the MICRFRX2_PREAMBLE bytes are received successfully.
```c
static uint8_t micrfrx2_read_packet ( micrfrx2_t *ctx );
```

### Application Init

> Initializes the driver and enables the device. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    micrfrx2_cfg_t micrfrx2_cfg;  /**< Click config object. */

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
    micrfrx2_cfg_setup( &micrfrx2_cfg );
    MICRFRX2_MAP_MIKROBUS( micrfrx2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == micrfrx2_init( &micrfrx2, &micrfrx2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    micrfrx2_enable_device ( &micrfrx2 );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for a data ready indication, then reads all packet data, verifies the CRC bytes in a packet, and displays its data as well as the RSSI value on the USB UART.

```c
void application_task ( void )
{
    static float rssi_v = 0;
    static uint8_t packet_len = 0;
    static uint8_t msg_cnt = 0;
    static uint16_t crc = 0;

    log_printf( &logger, "\r\n Waiting for data ready...\r\n" );
    micrfrx2_wait_ready ( &micrfrx2 );
    packet_len = micrfrx2_read_packet ( &micrfrx2 );
    if ( packet_len )
    {
        micrfrx2_read_rssi_voltage ( &micrfrx2, &rssi_v );
        crc = ( ( uint16_t ) packet_buf[ packet_len - 2 ] << 8 ) | packet_buf[ packet_len - 1 ];
        if ( crc == micrftx2_calculate_crc16 ( packet_buf, packet_len - 2 ) )
        {
            log_printf( &logger, " Received message: " );
            for ( msg_cnt = 0; msg_cnt < packet_buf[ 2 ]; msg_cnt++ )
            {
                log_printf( &logger, "%c", ( uint16_t ) packet_buf[ msg_cnt + 3 ] );
            }
            log_printf( &logger, "\r\n RSSI: %.1f dBm\r\n", MICRFRX2_RSSI_V_TO_DBM ( rssi_v ) );
        }
    }
    Delay_ms ( 100 );
}
```

### Note

> The OOK TX Click board is a compatible transmitter for the MICRF RX 2 Click.
Here are a few steps for troubleshooting if you are experiencing issues running this example:
> - Check the MCU clock configuration, use an external oscillator instead of the MCU's internal one for better accuracy on manchester data rate delay.
> - Measure the actual data rate on the data line and adjust the MICRFRX2_MAN_BIT_LEN_US value accordingly.

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
