
---
# Smart Mic Click

> [Smart Mic Click](https://www.mikroe.com/?pid_product=MIKROE-4158) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4158&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Smart Mic Click board by programming it with 4 different keywords, and then waiting for a keyword event,
parsing it and displaying on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartMic

### Example Key Functions

- `smartmic_cfg_setup` Config Object Initialization function.
```c
void smartmic_cfg_setup ( smartmic_cfg_t *cfg );
```

- `smartmic_init` Initialization function.
```c
err_t smartmic_init ( smartmic_t *ctx, smartmic_cfg_t *cfg );
```

- `smartmic_default_cfg` Click Default Configuration function.
```c
err_t smartmic_default_cfg ( smartmic_t *ctx );
```

- `smartmic_wait_keyword` This function waits for a keyword event and then reads it and returns the keyword ID number.
```c
err_t smartmic_wait_keyword ( smartmic_t *ctx );
```

- `smartmic_download_keyword` This function downloads keyword models to the module.
```c
err_t smartmic_download_keyword ( smartmic_t *ctx, uint16_t *data_in, uint16_t len );
```

- `smartmic_voice_make` This function performs voice make feature. It stops the route, then sets digital gain to 20db, sample rate to 16K, frame size to 16 ms, and finally it selects route 6 and configures algorithm parameters.
```c
err_t smartmic_voice_make ( smartmic_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration which programs the device with system config, firmware, and 4 keywords
("Hello VoiceQ","Switch The Light","Next Song","Baidu Yixia") binaries.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartmic_cfg_t smartmic_cfg;  /**< Click config object. */

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
    smartmic_cfg_setup( &smartmic_cfg );
    SMARTMIC_MAP_MIKROBUS( smartmic_cfg, MIKROBUS_1 );
    if ( SMARTMIC_OK != smartmic_init( &smartmic, &smartmic_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Configuring device... \r\n" );
    
    if ( SMARTMIC_OK != smartmic_default_cfg ( &smartmic ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for a keyword event, parses it and displays on the USB UART an appropriate message for the detected keyword.

```c
void application_task ( void )
{
    switch ( smartmic_wait_keyword ( &smartmic ) )
    {
        case SMARTMIC_OEM1_KWD_DETECTED:
        {
            log_printf ( &logger, " Hello VoiceQ keyword detected!\r\n" );
            break;
        }
        case SMARTMIC_OEM2_KWD_DETECTED:
        {
            log_printf ( &logger, " Switch The Light keyword detected!\r\n" );
            break;
        }
        case SMARTMIC_OEM3_KWD_DETECTED:
        {
            log_printf ( &logger, " Next Song keyword detected!\r\n" );
            break;
        }
        case SMARTMIC_OEM4_KWD_DETECTED:
        {
            log_printf ( &logger, " Baidu YiXia keyword detected!\r\n" );
            break;
        } 
    }
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
