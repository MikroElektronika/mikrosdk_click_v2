
---
# Force Cell Click

> [Force Cell Click](https://www.mikroe.com/?pid_product=MIKROE-6704) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6704&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2025.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Force Cell Click board by reading the applied force
in newtons (N) from a load cell sensor. The application initializes the driver, calibrates the
offset, and continuously measures and logs the force value to the USB UART terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ForceCell

### Example Key Functions

- `forcecell_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void forcecell_cfg_setup ( forcecell_cfg_t *cfg );
```

- `forcecell_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t forcecell_init ( forcecell_t *ctx, forcecell_cfg_t *cfg );
```

- `forcecell_calib_offset` This function calibrates the zero force offset value.
```c
err_t forcecell_calib_offset ( forcecell_t *ctx );
```

- `forcecell_read_force` This function reads the applied force level [N].
```c
err_t forcecell_read_force ( forcecell_t *ctx, float *force );
```

### Application Init

> Initializes the logger and the Click driver, performs offset calibration to null the load cell.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    forcecell_cfg_t forcecell_cfg;  /**< Click config object. */

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
    forcecell_cfg_setup( &forcecell_cfg );
    FORCECELL_MAP_MIKROBUS( forcecell_cfg, MIKROBUS_1 );
    err_t init_flag = forcecell_init( &forcecell, &forcecell_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( FORCECELL_ERROR == forcecell_calib_offset ( &forcecell ) )
    {
        log_error( &logger, " Offset calibration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads and displays the current force value in newtons every 100ms.

```c
void application_task ( void )
{
    float force = 0;
    if ( FORCECELL_OK == forcecell_read_force ( &forcecell, &force ) ) 
    {
        log_printf( &logger, " Force : %.3f N\r\n\n", force );
        Delay_ms ( 100 );
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
