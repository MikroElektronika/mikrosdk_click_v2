
---
# OOK TX Click

> [OOK TX Click](https://www.mikroe.com/?pid_product=MIKROE-2903) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2903&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of OOK TX Click board by sending a predefined message to the receiver.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.OOKTX

### Example Key Functions

- `ooktx_cfg_setup` Config Object Initialization function.
```c
void ooktx_cfg_setup ( ooktx_cfg_t *cfg );
```

- `ooktx_init` Initialization function.
```c
err_t ooktx_init ( ooktx_t *ctx, ooktx_cfg_t *cfg );
```

- `ooktx_send_data` This function builds and sends a packet of data. The packet format is as follows (MSB first, manchester IEEE 802.3): OOKTX_TRAINING_BYTES, PREABMLE, LEN, DATA_IN, CRC16 (calculated from whole packet excluding training bytes).
```c
static void ooktx_send_data ( ooktx_t *ctx, uint16_t preamble, uint8_t *data_in, uint8_t len );
```

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

### Note

> The OOK RX Click board is a compatible receiver for the OOK TX Click.
Here are a few steps for troubleshooting if you are experiencing issues running this example:
> - Check the MCU clock configuration, use an external oscillator instead of the MCU's internal one for better accuracy on manchester data rate delay.
> - Measure the actual data rate on the data line and adjust the OOKTX_MAN_BIT_LEN_US value accordingly.

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
