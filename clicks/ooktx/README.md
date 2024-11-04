\mainpage Main Page

---
# OOK TX Click

> OOK TX Click is a simple wireless transmitter that operates at the frequency of 433MHz (sub-GHz). This device allows realization of a simple, low-speed wireless ad-hoc communication network between a transmitter and compatible receiver, such as the OOK RX Click.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ooktx_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ook-tx-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the OOK TX Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for OOK TX Click driver.

#### Standard key functions :

- `ooktx_cfg_setup` Config Object Initialization function.
```c
void ooktx_cfg_setup ( ooktx_cfg_t *cfg );
```

- `ooktx_init` Initialization function.
```c
err_t ooktx_init ( ooktx_t *ctx, ooktx_cfg_t *cfg );
```

#### Example key functions :

- `ooktx_send_data` This function builds and sends a packet of data. The packet format is as follows (MSB first, manchester IEEE 802.3): OOKTX_TRAINING_BYTES, PREABMLE, LEN, DATA_IN, CRC16 (calculated from whole packet excluding training bytes).
```c
static void ooktx_send_data ( ooktx_t *ctx, uint16_t preamble, uint8_t *data_in, uint8_t len );
```

## Example Description

> This example demonstrates the use of OOK TX Click board by sending a predefined message to the receiver.

**The demo application is composed of two sections :**

### Application Init

> Initialized the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    ooktx_cfg_t ooktx_cfg;      /**< Click config object. */

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
    ooktx_cfg_setup( &ooktx_cfg );
    OOKTX_MAP_MIKROBUS( ooktx_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == ooktx_init( &ooktx, &ooktx_cfg ) ) 
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
    log_printf ( &logger, " Sending data: %s\r\n\n", ( char * ) OOKTX_MESSAGE );
    ooktx_send_data ( &ooktx, OOKTX_PREAMBLE, OOKTX_MESSAGE, strlen ( OOKTX_MESSAGE ) );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Note

> The OOK RX Click board is a compatible receiver for the OOK TX Click.
Here are a few steps for troubleshooting if you are experiencing issues running this example:
> - Check the MCU clock configuration, use an external oscillator instead of the MCU's internal one for better accuracy on manchester data rate delay.
> - Measure the actual data rate on the data line and adjust the OOKTX_MAN_BIT_LEN_US value accordingly.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.OOKTX

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
