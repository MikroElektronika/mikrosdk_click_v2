
---
# Boost 5 Click

> [Boost 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6549) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6549&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2025.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of the Boost 5 Click board by enabling the device
and continuously reading and logging the measured output voltage (VOUT).
If a failure is detected during voltage reading, the device is reset.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Boost5

### Example Key Functions

- `boost5_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void boost5_cfg_setup ( boost5_cfg_t *cfg );
```

- `boost5_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t boost5_init ( boost5_t *ctx, boost5_cfg_t *cfg );
```

- `boost5_enable_device` This function enables device by setting the EN pin to high logic state.
```c
void boost5_enable_device ( boost5_t *ctx );
```

- `boost5_reset_device` This function resets device by toggling the EN pin logic state.
```c
void boost5_reset_device ( boost5_t *ctx );
```

- `boost5_read_vout` This function reads the boost output voltage level.
```c
err_t boost5_read_vout ( boost5_t *ctx, float *vout );
```

### Application Init

> Initializes the logger and the Boost 5 Click board. Configures the ADC for voltage measurements and enables the device to prepare it for operation.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    boost5_cfg_t boost5_cfg;  /**< Click config object. */

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
    boost5_cfg_setup( &boost5_cfg );
    BOOST5_MAP_MIKROBUS( boost5_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == boost5_init( &boost5, &boost5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "\r\n Enable device\r\n\n" );
    boost5_enable_device ( &boost5 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the output voltage level and logs it on the USB UART. In case of an error during
the reading process, or the user changes VOUT using an on-board VOUT SEL switch,
the device is reset to recover from potential issues or to apply new settings.

```c
void application_task ( void )
{
    float vout = 0;
    if ( BOOST5_OK == boost5_read_vout ( &boost5, &vout ) ) 
    {
        log_printf( &logger, "\r\n VOUT : %.3f V\r\n", vout );
    }
    else
    {
        log_printf( &logger, "\r\n Reset device\r\n" );
        boost5_reset_device ( &boost5 );
    }
}
```

### Note

> The VOUT is configured using an on-board VOUT SEL 4-position switch.

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
