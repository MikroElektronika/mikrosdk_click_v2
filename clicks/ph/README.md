
---
# pH Click

> [pH Click](https://www.mikroe.com/?pid_product=MIKROE-4297) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4297&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from pH Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.pH

### Example Key Functions

- `ph_cfg_setup` Config Object Initialization function.
```c
void ph_cfg_setup ( ph_cfg_t *cfg );
```

- `ph_init` Initialization function.
```c
err_t ph_init ( ph_t *ctx, ph_cfg_t *cfg );
```

- `ph_default_cfg` Click Default Configuration function.
```c
err_t ph_default_cfg ( ph_t *ctx );
```

- `ph_send_cmd` Send command function.
```c
void ph_send_cmd ( ph_t *ctx, char *p_cmd );
```

- `ph_get_cmd_resp` Send get response function.
```c
void ph_get_cmd_resp ( ph_t *ctx, char *p_cmd, char *p_resp );
```

- `ph_switch_led` Toggle LED function.
```c
void ph_switch_led ( ph_t *ctx, uint8_t state, char *p_resp );
```

### Application Init

> Initializes UART driver, performing a factory reset of the device, disabling continuous read, 
> and performing calibration at the midpoint on the pH scale.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ph_cfg_t ph_cfg;  /**< Click config object. */

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
    ph_cfg_setup( &ph_cfg );
    PH_MAP_MIKROBUS( ph_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ph_init( &ph, &ph_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    ph_factory_rst( &ph, app_buf );
    Delay_ms ( 1000 );
    
    ph_cont_read( &ph, 0, app_buf );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "   -- Initialized --   \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "  Place probe into pH  \r\n" );
    log_printf( &logger, " neutral substance for \r\n" );
    log_printf( &logger, " mid point calibration \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    for ( uint8_t n_cnt = 0; n_cnt < 20; n_cnt++ )
    {
        Delay_ms ( 1000 );
    }
    log_printf( &logger, " Starting calibration  \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    ph_perf_calib ( &ph, PH_CMD_CALIB_MID, 7.000, app_buf );
    Delay_ms ( 1000 );
    log_printf( &logger, " Calibration done!     \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    
    log_printf( &logger, " - Application  task -\r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    ph_send_cmd( &ph, PH_CMD_DIS_RSP_CODES );
    Delay_ms ( 1000 );
    ph_clr_log_buf( app_buf );
}
```

### Application Task

> This example shows the capabilities of the pH Click board by performing a reading of the 
> pH value of the substance in which the probe is submerged and displaying readings via the 
> USART terminal.

```c
void application_task ( void ) 
{
    ph_send_cmd ( &ph, PH_CMD_SET_SNGL_READ );
    ph_response( &ph, app_buf );
    log_printf( &logger, " pH value: %s ", app_buf );
    log_printf( &logger, "-----------------------\r\n" );
    ph_clr_log_buf( app_buf );
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
