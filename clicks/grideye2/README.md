
---
# Grid-EYE 2 Click

> [Grid-EYE 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6208) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6208&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Grid-EYE 2 Click by reading and displaying the temperature measurements as an 8x8 pixels grid.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GridEYE2

### Example Key Functions

- `grideye2_cfg_setup` Config Object Initialization function.
```c
void grideye2_cfg_setup ( grideye2_cfg_t *cfg );
```

- `grideye2_init` Initialization function.
```c
err_t grideye2_init ( grideye2_t *ctx, grideye2_cfg_t *cfg );
```

- `grideye2_default_cfg` Click Default Configuration function.
```c
err_t grideye2_default_cfg ( grideye2_t *ctx );
```

- `grideye2_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t grideye2_get_int_pin ( grideye2_t *ctx );
```

- `grideye2_read_grid` This function reads the temperature measurement of an 8x8 pixels grid and stores it in the ctx->grid_temp array.
```c
err_t grideye2_read_grid ( grideye2_t *ctx );
```

- `grideye2_clear_status` This function clears the interrupt status flags.
```c
err_t grideye2_clear_status ( grideye2_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration which enables the data ready interrupt and sets data measurement to 10 frames per second.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    grideye2_cfg_t grideye2_cfg;  /**< Click config object. */

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
    grideye2_cfg_setup( &grideye2_cfg );
    GRIDEYE2_MAP_MIKROBUS( grideye2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == grideye2_init( &grideye2, &grideye2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( GRIDEYE2_ERROR == grideye2_default_cfg ( &grideye2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for a data ready interrupt and then reads the grid temperature measurements and displays the results on the USB UART in a form of an 8x8 pixels grid.

```c
void application_task ( void )
{
    // Wait for data ready interrupt
    while ( grideye2_get_int_pin ( &grideye2 ) );
    
    if ( GRIDEYE2_OK == grideye2_read_grid ( &grideye2 ) )
    {
        grideye2_clear_status ( &grideye2 );
        for ( uint8_t cnt = 0; cnt < GRIDEYE2_NUM_PIXELS; cnt++ )
        {
            if ( 0 == ( cnt % 8 ) )
            {
                log_printf( &logger, "\r\n" );
            }
            log_printf( &logger, "%.2f ", grideye2.grid_temp[ cnt ] );
        }
        log_printf( &logger, "\r\n" );
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
