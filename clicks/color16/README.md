
---
# Color 16 Click

> [Color 16 Click](https://www.mikroe.com/?pid_product=MIKROE-5421) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5421&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Color 16 Click by reading and displaying the values from all 14 channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Color16

### Example Key Functions

- `color16_cfg_setup` Config Object Initialization function.
```c
void color16_cfg_setup ( color16_cfg_t *cfg );
```

- `color16_init` Initialization function.
```c
err_t color16_init ( color16_t *ctx, color16_cfg_t *cfg );
```

- `color16_default_cfg` Click Default Configuration function.
```c
err_t color16_default_cfg ( color16_t *ctx );
```

- `color16_read_data` This function checks if the spectral measurement data is ready and then reads data from all channels along with the STATUS and ASTATUS bytes.
```c
err_t color16_read_data ( color16_t *ctx, color16_data_t *data_out );
```

- `color16_set_wait_time_ms` This function sets the wait time in milliseconds by setting the WTIME register.
```c
err_t color16_set_wait_time_ms ( color16_t *ctx, float wait_time_ms );
```

- `color16_set_integration_time_ms` This function sets the integration time in milliseconds by setting the ATIME and ASTEP registers.
```c
err_t color16_set_integration_time_ms ( color16_t *ctx, float int_time_ms );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color16_cfg_t color16_cfg;  /**< Click config object. */

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
#ifdef INTERFACE_LOGGER_UART
    log_cfg.is_interrupt = false;
#endif
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    color16_cfg_setup( &color16_cfg );
    COLOR16_MAP_MIKROBUS( color16_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color16_init( &color16, &color16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR16_ERROR == color16_default_cfg ( &color16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the spectral measurement complete flag and then reads data from all 14 channels
in 3 cycles, and displays the results on the USB UART every 300ms approximately.

```c
void application_task ( void )
{
    color16_data_t color_data;
    if ( COLOR16_OK == color16_read_data ( &color16, &color_data ) )
    {
        log_printf ( &logger, " STATUS:          0x%.2X\r\n", ( uint16_t ) color_data.status );
        log_printf ( &logger, " ASTATUS:         0x%.2X\r\n", ( uint16_t ) color_data.astatus );
        log_printf ( &logger, " ------- Cycle 1 -------\r\n" );
        log_printf ( &logger, " Channel FZ:      %u\r\n", color_data.ch_fz );
        log_printf ( &logger, " Channel FY:      %u\r\n", color_data.ch_fy );
        log_printf ( &logger, " Channel FXL:     %u\r\n", color_data.ch_fxl );
        log_printf ( &logger, " Channel NIR:     %u\r\n", color_data.ch_nir );
        log_printf ( &logger, " Channel 2xVIS_1: %u\r\n", color_data.ch_2x_vis_1 );
        log_printf ( &logger, " Channel FD_1:    %u\r\n", color_data.ch_fd_1 );
        log_printf ( &logger, " ------- Cycle 2 -------\r\n" );
        log_printf ( &logger, " Channel F2:      %u\r\n", color_data.ch_f2 );
        log_printf ( &logger, " Channel F3:      %u\r\n", color_data.ch_f3 );
        log_printf ( &logger, " Channel F4:      %u\r\n", color_data.ch_f4 );
        log_printf ( &logger, " Channel F6:      %u\r\n", color_data.ch_f6 );
        log_printf ( &logger, " Channel 2xVIS_2: %u\r\n", color_data.ch_2x_vis_2 );
        log_printf ( &logger, " Channel FD_2:    %u\r\n", color_data.ch_fd_2 );
        log_printf ( &logger, " ------- Cycle 3 -------\r\n" );
        log_printf ( &logger, " Channel F1:      %u\r\n", color_data.ch_f1 );
        log_printf ( &logger, " Channel F5:      %u\r\n", color_data.ch_f5 );
        log_printf ( &logger, " Channel F7:      %u\r\n", color_data.ch_f7 );
        log_printf ( &logger, " Channel F8:      %u\r\n", color_data.ch_f8 );
        log_printf ( &logger, " Channel 2xVIS_3: %u\r\n", color_data.ch_2x_vis_3 );
        log_printf ( &logger, " Channel FD_3:    %u\r\n", color_data.ch_fd_3 );
        log_printf ( &logger, " -----------------------\r\n\n" );
        Delay_ms ( 300 );
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
