\mainpage Main Page

---
# OOK RX Click

> OOK RX Click is a wireless receiver that operates at the frequency of 433MHz (sub-GHz). This device allows realization of a simple, low-speed wireless ad hoc communication network between a receiver and compatible transmitter.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ookrx_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ook-rx-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the OOK RX Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for OOK RX Click driver.

#### Standard key functions :

- `ookrx_cfg_setup` Config Object Initialization function.
```c
void ookrx_cfg_setup ( ookrx_cfg_t *cfg );
```

- `ookrx_init` Initialization function.
```c
err_t ookrx_init ( ookrx_t *ctx, ookrx_cfg_t *cfg );
```

#### Example key functions :

- `ookrx_enable_device` This function enables device by setting the EN pin to high logic state.
```c
void ookrx_enable_device ( ookrx_t *ctx );
```

- `ookrx_wait_ready` This function waits for all training bytes to arrive which indicates data ready.
```c
static void ookrx_wait_ready ( ookrx_t *ctx );
```

- `ookrx_read_packet` This function reads data packet and stores it in a packet_buf only if the OOKRX_PREAMBLE bytes are received successfully.
```c
static uint8_t ookrx_read_packet ( ookrx_t *ctx );
```

## Example Description

> This example demonstrates the use of OOK RX Click board by reading and parsing packet messages received from the transmitter.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables the device and squelch mode. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ookrx_cfg_t ookrx_cfg;  /**< Click config object. */

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
    ookrx_cfg_setup( &ookrx_cfg );
    OOKRX_MAP_MIKROBUS( ookrx_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == ookrx_init( &ookrx, &ookrx_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    ookrx_enable_squelch ( &ookrx );
    ookrx_enable_device ( &ookrx );

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
    ookrx_wait_ready ( &ookrx );
    packet_len = ookrx_read_packet ( &ookrx );
    if ( packet_len )
    {
        ookrx_read_rssi_voltage ( &ookrx, &rssi_v );
        crc = ( ( uint16_t ) packet_buf[ packet_len - 2 ] << 8 ) | packet_buf[ packet_len - 1 ];
        if ( crc == micrftx2_calculate_crc16 ( packet_buf, packet_len - 2 ) )
        {
            log_printf( &logger, " Received message: " );
            for ( msg_cnt = 0; msg_cnt < packet_buf[ 2 ]; msg_cnt++ )
            {
                log_printf( &logger, "%c", ( uint16_t ) packet_buf[ msg_cnt + 3 ] );
            }
            log_printf( &logger, "\r\n RSSI: %.1f dBm\r\n", OOKRX_RSSI_V_TO_DBM ( rssi_v ) );
        }
    }
    Delay_ms ( 100 );
}
```

## Note

> The OOK TX Click board is a compatible transmitter for the OOK RX Click.
Here are a few steps for troubleshooting if you are experiencing issues running this example:
> - Check the MCU clock configuration, use an external oscillator instead of the MCU's internal one for better accuracy on manchester data rate delay.
> - Measure the actual data rate on the data line and adjust the OOKRX_MAN_BIT_LEN_US value accordingly.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.OOKRX

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
