
---
# ATA663211 Click

> [ATA663211 Click](https://www.mikroe.com/?pid_product=MIKROE-2335) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2335&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : feb 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of an ATA663211 Click board by showing the communication between the two Click boards.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ata663211

### Example Key Functions

- `ata663211_cfg_setup` Config Object Initialization function.
```c
void ata663211_cfg_setup ( ata663211_cfg_t *cfg );
```
 
- `ata663211_init` Initialization function.
```c
err_t ata663211_init ( ata663211_t *ctx, ata663211_cfg_t *cfg );
```

- `ata663211_generic_write` Generic write function.
```c
err_t ata663211_generic_write ( ata663211_t *ctx, uint8_t *data_buf, uint16_t len );
```

- `ata663211_generic_read` Generic read function.
```c
err_t ata663211_generic_read ( ata663211_t *ctx, uint8_t *data_buf, uint16_t len );
```

### Application Init

> Initalizes device and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ata663211_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.
    ata663211_cfg_setup( &cfg );
    ATA663211_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ata663211_init( &ata663211, &cfg );
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
}
```

### Application Task

> Depending on the selected application mode, it reads all the received data or sends the desired text message with the message counter once per second.

```c
void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    ata663211_generic_write( &ata663211, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms ( 1000 ); 
#else
    uint8_t rx_byte = 0;
    if ( 1 == ata663211_generic_read( &ata663211, &rx_byte, 1 ) )
    {
       log_printf( &logger, "%c", rx_byte );
    }
#endif
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
