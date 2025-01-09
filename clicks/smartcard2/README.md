
---
# Smart Card 2 Click

> [Smart Card 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5492) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5492&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2022.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of Smart Card 2 Click board by checking the SIM card presence and activating the card on insert. The card should respond with an ATR (Answer to Reset) message.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartCard2

### Example Key Functions

- `smartcard2_cfg_setup` Config Object Initialization function.
```c
void smartcard2_cfg_setup ( smartcard2_cfg_t *cfg );
```

- `smartcard2_init` Initialization function.
```c
err_t smartcard2_init ( smartcard2_t *ctx, smartcard2_cfg_t *cfg );
```

- `smartcard2_send_ccid` This function sends the CCID command message by using UART serial interface.
```c
err_t smartcard2_send_ccid ( smartcard2_t *ctx, smartcard2_ccid_t *data_in );
```

- `smartcard2_read_ccid` This function reads a CCID response or event message by using UART serial interface.
```c
err_t smartcard2_read_ccid ( smartcard2_t *ctx, smartcard2_ccid_t *data_out );
```

- `smartcard2_icc_power_on` This function activates the card by performing an ICC power ON command. The device will respond with a data block containing ICC ATR (Answer to Reset) message.
```c
err_t smartcard2_icc_power_on ( smartcard2_t *ctx, uint8_t power_sel );
```

### Application Init

> Initializes the driver and enables the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartcard2_cfg_t smartcard2_cfg;  /**< Click config object. */

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
    smartcard2_cfg_setup( &smartcard2_cfg );
    SMARTCARD2_MAP_MIKROBUS( smartcard2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == smartcard2_init( &smartcard2, &smartcard2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and parses all CCID messages received from the device. Checks the SIM card presence
and activates it if it's inserted. The card should respond with an ATR (Answer to Reset) message.
All data is being logged on the USB UART where you can track their changes.

```c
void application_task ( void )
{
    smartcard2_ccid_t ccid = { 0 };
    if ( SMARTCARD2_OK == smartcard2_read_ccid ( &smartcard2, &ccid ) )
    {
        smartcard2_display_ccid_message ( ccid );
    }
    if ( SMARTCARD2_ICC_PRESENT == icc_status )
    {
        log_printf( &logger, " Activating card... \r\n" );
        smartcard2_icc_power_on ( &smartcard2, SMARTCARD2_POWER_SEL_3V );
        Delay_ms ( 100 );
    }
}
```

### Note

> This example doesn't parse ATR messages.
There are some online ATR parsers which could be used for decoding those messages.
For example: https://smartcard-atr.apdu.fr/

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
