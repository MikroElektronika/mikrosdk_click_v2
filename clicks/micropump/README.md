
---
# Micro Pump Click

> [Micro Pump Click](https://www.mikroe.com/?pid_product=MIKROE-6529) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6529&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2025.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of the Micro Pump Click board. It initializes the Click module, 
calibrates the offset for accurate current measurements, and then controls the motor in different states 
while measuring and logging the output current in milliamps (mA).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MicroPump

### Example Key Functions

- `micropump_cfg_setup` Config Object Initialization function.
```c
void micropump_cfg_setup ( micropump_cfg_t *cfg );
```

- `micropump_init` Initialization function.
```c
err_t micropump_init ( micropump_t *ctx, micropump_cfg_t *cfg );
```

- `micropump_drive_motor` This function drives the micro pump motor in the selected state.
```c
void micropump_drive_motor ( micropump_t *ctx, uint8_t state );
```

- `micropump_calib_offset` This function calibrates the zero current offset value.
```c
err_t micropump_calib_offset ( micropump_t *ctx );
```

- `micropump_get_out_current` This function reads the current output measurement in mA.
```c
err_t micropump_get_out_current ( micropump_t *ctx, float *current );
```

### Application Init

> Initializes the logger and the Micro Pump Click driver and performs offset calibration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    micropump_cfg_t micropump_cfg;  /**< Click config object. */

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
    micropump_cfg_setup( &micropump_cfg );
    MICROPUMP_MAP_MIKROBUS( micropump_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == micropump_init( &micropump, &micropump_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MICROPUMP_ERROR == micropump_calib_offset ( &micropump ) )
    {
        log_error( &logger, " Offset calibration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Alternates the motor's operational states between COAST and FORWARD. For each state, it logs the motor's current consumption.

```c
void application_task ( void )
{
    float current = 0;
    log_printf( &logger, " Motor state : COAST\r\n" );
    micropump_drive_motor ( &micropump, MICROPUMP_MOTOR_COAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( MICROPUMP_OK == micropump_get_out_current ( &micropump, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
    }

    log_printf( &logger, " Motor state : FORWARD\r\n" );
    micropump_drive_motor ( &micropump, MICROPUMP_MOTOR_FORWARD );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( MICROPUMP_OK == micropump_get_out_current ( &micropump, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
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
