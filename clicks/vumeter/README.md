
---
# VU Meter Click

> [VU Meter Click](https://www.mikroe.com/?pid_product=MIKROE-5111) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5111&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of VU Meter Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.VUMeter

### Example Key Functions

- `vumeter_cfg_setup` Config Object Initialization function.
```c
void vumeter_cfg_setup ( vumeter_cfg_t *cfg );
```

- `vumeter_init` Initialization function.
```c
err_t vumeter_init ( vumeter_t *ctx, vumeter_cfg_t *cfg );
```

- `vumeter_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t vumeter_read_an_pin_voltage ( vumeter_t *ctx, float *data_out );
```

- `vumeter_set_gain_level` This function sets the input signal gain level (the microphone sensitivity).
```c
err_t vumeter_set_gain_level ( vumeter_t *ctx, uint8_t gain_lvl );
```

- `vumeter_calculate_vu_level` This function calculates VU level from the analog voltage input.
```c
float vumeter_calculate_vu_level ( vumeter_t *ctx, uint16_t sample_rate_ms );
```

### Application Init

> Initializes the driver and sets the gain level (the microphone sensitivity) to maximum.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    vumeter_cfg_t vumeter_cfg;  /**< Click config object. */

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

    vumeter_cfg_setup( &vumeter_cfg );
    VUMETER_MAP_MIKROBUS( vumeter_cfg, MIKROBUS_1 );
    err_t init_flag  = vumeter_init( &vumeter, &vumeter_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    vumeter_set_gain_level ( &vumeter, VUMETER_GAIN_LEVEL_MAX );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Calculates VU level from the analog voltage read from AN pin, and displays the results on the USB UART approximately every 100ms.

```c
void application_task ( void )
{
    log_printf( &logger, " VU level: %.3f VU\r\n", vumeter_calculate_vu_level ( &vumeter, 100 ) );
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
