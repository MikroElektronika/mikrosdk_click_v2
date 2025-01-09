
---
# DAC 18 Click

> [DAC 18 Click](https://www.mikroe.com/?pid_product=MIKROE-6137) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6137&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the DAC 18 Click board 
> by configuring the waveform signals from a function generator on the OUT0 
> and voltage level on the OUT1.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC18

### Example Key Functions

- `dac18_cfg_setup` Config Object Initialization function.
```c
void dac18_cfg_setup ( dac18_cfg_t *cfg );
```

- `dac18_init` Initialization function.
```c
err_t dac18_init ( dac18_t *ctx, dac18_cfg_t *cfg );
```

- `dac18_default_cfg` Click Default Configuration function.
```c
err_t dac18_default_cfg ( dac18_t *ctx );
```

- `dac18_cfg_pwm_out` This function configures PWM output (OUT0) for the function generator by using the I2C serial interface.
```c
err_t dac18_cfg_pwm_out ( dac18_t *ctx, uint8_t f_sel, uint8_t c_step, uint8_t t_step );
```

- `dac18_set_mode` This function selects between programming and standalone modes by toggling the digital output state of the MOD pin.
```c
void dac18_set_mode ( dac18_t *ctx, uint8_t mode );
```

- `dac18_get_gpi_status` This function gets GPI status by reading the states of the GP0, GP1 and GP2 pins.
```c
void dac18_get_gpi_status ( dac18_t *ctx, uint8_t *gpi_status );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration (configuration mode).

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac18_cfg_t dac18_cfg;  /**< Click config object. */

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
    dac18_cfg_setup( &dac18_cfg );
    DAC18_MAP_MIKROBUS( dac18_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dac18_init( &dac18, &dac18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC18_ERROR == dac18_default_cfg ( &dac18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, " Use the GP0, GP1 and GP2 switch to change the outputs\r\n\n" );
}
```

### Application Task

> The demo application operated in standalone mode and displayed the voltage level on OUT1.
> The GP0, GP1, and GP2 switches on the DAC 18 Click board 
> are used to change the output voltage level and waveform signals.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    dac18_get_gpi_status( &dac18, &gpi_status );
    if ( gpi_status != new_gpi_status )
    {
        new_gpi_status = gpi_status;
        dac18_display_out_status( );
    }
    Delay_ms ( 100 );
}
```

### Note

> Set GP0, GP1, and GP2 switches to position "1" for the configuration modes.

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
