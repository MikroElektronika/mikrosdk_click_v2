
---
# MICRF RX Click

> MICRF RX Click is a compact add-on board for high-sensitivity applications, including remote keyless entry, tire pressure monitoring systems, and remote actuation systems. This board features the MICRF220, an ASK/OOK 315MHz receiver with RSSI and squelch capabilities from Microchip to offer top-notch RF performance. This super-heterodyne, image-reject RF receiver provides a -110dBm sensitivity at 1kbps and a 0.1% Bit Error Rate (BER), supporting adjustable demodulator filter bandwidths for bit rates up to 14.4kbps.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/micrfrx_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/micrf-rx-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the MICRF RX Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for MICRF RX Click driver.

#### Standard key functions :

- `micrfrx_cfg_setup` Config Object Initialization function.
```c
void micrfrx_cfg_setup ( micrfrx_cfg_t *cfg );
```

- `micrfrx_init` Initialization function.
```c
err_t micrfrx_init ( micrfrx_t *ctx, micrfrx_cfg_t *cfg );
```

#### Example key functions :

- `micrfrx_enable_device` This function enables device by setting the SHD pin to low logic state.
```c
void micrfrx_enable_device ( micrfrx_t *ctx );
```

- `micrfrx_wait_ready` This function waits for all training bytes to arrive which indicates data ready.
```c
static void micrfrx_wait_ready ( micrfrx_t *ctx );
```

- `micrfrx_read_packet` This function reads data packet and stores it in a packet_buf only if the MICRFRX_PREAMBLE bytes are received successfully.
```c
static uint8_t micrfrx_read_packet ( micrfrx_t *ctx );
```

## Example Description

> This example demonstrates the use of MICRF RX Click board by reading and parsing packet messages received from the transmitter.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables the device and squelch mode. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    micrfrx_cfg_t micrfrx_cfg;  /**< Click config object. */

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
    micrfrx_cfg_setup( &micrfrx_cfg );
    MICRFRX_MAP_MIKROBUS( micrfrx_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == micrfrx_init( &micrfrx, &micrfrx_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    micrfrx_enable_squelch ( &micrfrx );
    micrfrx_enable_device ( &micrfrx );

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
    micrfrx_wait_ready ( &micrfrx );
    packet_len = micrfrx_read_packet ( &micrfrx );
    if ( packet_len )
    {
        micrfrx_read_rssi_voltage ( &micrfrx, &rssi_v );
        crc = ( ( uint16_t ) packet_buf[ packet_len - 2 ] << 8 ) | packet_buf[ packet_len - 1 ];
        if ( crc == micrftx2_calculate_crc16 ( packet_buf, packet_len - 2 ) )
        {
            log_printf( &logger, " Received message: " );
            for ( msg_cnt = 0; msg_cnt < packet_buf[ 2 ]; msg_cnt++ )
            {
                log_printf( &logger, "%c", ( uint16_t ) packet_buf[ msg_cnt + 3 ] );
            }
            log_printf( &logger, "\r\n RSSI: %.1f dBm\r\n", MICRFRX_RSSI_V_TO_DBM ( rssi_v ) );
        }
    }
    Delay_ms ( 100 );
}
```

## Note

> The MICRF TX Click board is a compatible transmitter for the MICRF RX Click.
Here are a few steps for troubleshooting if you are experiencing issues running this example:
> - Make sure the MICRF TX Click is set to ASK mode with on-board jumpers.
> - Check the MCU clock configuration, use an external oscillator instead of the MCU's internal one for better accuracy on manchester data rate delay.
> - Measure the actual data rate on the data line and adjust the MICRFRX_MAN_BIT_LEN_US value accordingly.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MICRFRX

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
