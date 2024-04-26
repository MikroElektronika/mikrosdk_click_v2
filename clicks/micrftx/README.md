\mainpage Main Page

---
# MICRF TX click

> MICRF TX Click is a compact add-on board designed as a powerful RF transmitter for data transmission over the 315MHz frequency band. This board features the MICRF112, a high-performance RF transmitter IC from Microchip, renowned for its efficiency in operation. This Click board™ stands out for its ease of use, requiring only a simple crystal oscillator to set the frequency, and supports both ASK and FSK modulation types with a Phase-Locked Loop (PLL) for stable frequency.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/micrftx_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/micrf-tx-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the MICRF TX Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for MICRF TX Click driver.

#### Standard key functions :

- `micrftx_cfg_setup` Config Object Initialization function.
```c
void micrftx_cfg_setup ( micrftx_cfg_t *cfg );
```

- `micrftx_init` Initialization function.
```c
err_t micrftx_init ( micrftx_t *ctx, micrftx_cfg_t *cfg );
```

#### Example key functions :

- `micrftx_send_data` This function builds and sends a packet of data. The packet format is as follows (MSB first, manchester IEEE 802.3): MICRFTX_TRAINING_BYTES, PREABMLE, LEN, DATA_IN, CRC16 (calculated from whole packet excluding training bytes).
```c
static void micrftx_send_data ( micrftx_t *ctx, uint16_t preamble, uint8_t *data_in, uint8_t len );
```

## Example Description

> This example demonstrates the use of MICRF TX click board by sending a predefined message to the receiver.

**The demo application is composed of two sections :**

### Application Init

> Initialized the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    micrftx_cfg_t micrftx_cfg;  /**< Click config object. */

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
    micrftx_cfg_setup( &micrftx_cfg );
    MICRFTX_MAP_MIKROBUS( micrftx_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == micrftx_init( &micrftx, &micrftx_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Sends a predefined message every 3 seconds and displays it on the USB UART.

```c
void application_task ( void )
{
    log_printf ( &logger, " Sending data: %s\r\n\n", ( char * ) MICRFTX_MESSAGE );
    micrftx_send_data ( &micrftx, MICRFTX_PREAMBLE, MICRFTX_MESSAGE, strlen ( MICRFTX_MESSAGE ) );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Note

> The MICRF RX click board is a compatible receiver for the MICRF TX click.
Here are a few steps for troubleshooting if you are experiencing issues running this example:
> - Make sure the MICRF TX click is set to ASK mode with on-board jumpers.
> - Check the MCU clock configuration, use an external oscillator instead of the MCU's internal one for better accuracy on manchester data rate delay.
> - Measure the actual data rate on the data line and adjust the MICRFTX_MAN_BIT_LEN_US value accordingly.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MICRFTX

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
