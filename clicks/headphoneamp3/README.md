
---
# Headphone AMP 3 Click

> [Headphone AMP 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5721) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5721&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Apr 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This library contains API for the Headphone AMP 3 Click driver.
  This demo application shows use of a Headphone AMP 3 Click board&trade;.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HeadphomeAMP3

### Example Key Functions

- `headphoneamp3_cfg_setup` Config Object Initialization function.
```c
void headphoneamp3_cfg_setup ( headphoneamp3_cfg_t *cfg );
```

- `headphoneamp3_init` Initialization function.
```c
err_t headphoneamp3_init ( headphoneamp3_t *ctx, headphoneamp3_cfg_t *cfg );
```

- `headphoneamp3_default_cfg` Click Default Configuration function.
```c
void headphoneamp3_default_cfg ( headphoneamp3_t *ctx );
```

- `headphoneamp3_enable_power` Headphone AMP 3 power pin setting function.
```c
void headphoneamp3_enable_power ( headphoneamp3_t *ctx, uint8_t state );
```

- `headphoneamp3_enable_amp` Headphone AMP 3 amp pin setting function.
```c
void headphoneamp3_enable_amp ( headphoneamp3_t *ctx, uint8_t state );
```

### Application Init

> Initialization of GPIO module and log UART.
  After driver initialization the app set default settings.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    headphoneamp3_cfg_t headphoneamp3_cfg;  /**< Click config object. */

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
    headphoneamp3_cfg_setup( &headphoneamp3_cfg );
    HEADPHONEAMP3_MAP_MIKROBUS( headphoneamp3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == headphoneamp3_init( &headphoneamp3, &headphoneamp3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    headphoneamp3_default_cfg ( &headphoneamp3 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the Headphone AMP 3 Click board&trade;.
  The app is enabling and disabling headphone output by changing ENA pin state every 10 seconds. 

```c
void application_task ( void ) 
{
    log_printf( &logger, " Enabling headphone output \r\n" );
    headphoneamp3_enable_amp( &headphoneamp3, HEADPHONEAMP3_ENABLE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Disabling headphone output \r\n" );
    headphoneamp3_enable_amp( &headphoneamp3, HEADPHONEAMP3_DISABLE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
