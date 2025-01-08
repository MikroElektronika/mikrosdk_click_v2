
---
# Buck 18 Click

> [Buck 18 Click](https://www.mikroe.com/?pid_product=MIKROE-6071) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6071&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Buck 18 Click board by changing the output voltage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck18

### Example Key Functions

- `buck18_cfg_setup` Config Object Initialization function.
```c
void buck18_cfg_setup ( buck18_cfg_t *cfg );
```

- `buck18_init` Initialization function.
```c
err_t buck18_init ( buck18_t *ctx, buck18_cfg_t *cfg );
```

- `buck18_default_cfg` Click Default Configuration function.
```c
err_t buck18_default_cfg ( buck18_t *ctx );
```

- `buck18_set_vout` This function sets the voltage output level.
```c
err_t buck18_set_vout ( buck18_t *ctx, buck18_vout_t vout );
```

- `buck18_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t buck18_read_voltage ( buck18_t *ctx, float *voltage );
```

- `buck18_enable` This function turns on the power switch and enables the buck mode.
```c
void buck18_enable ( buck18_t *ctx );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck18_cfg_t buck18_cfg;  /**< Click config object. */

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
    buck18_cfg_setup( &buck18_cfg );
    BUCK18_MAP_MIKROBUS( buck18_cfg, MIKROBUS_1 );
    err_t init_flag = buck18_init( &buck18, &buck18_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCK18_ERROR == buck18_default_cfg ( &buck18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application changes the output voltage and displays the current voltage output value.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    for ( buck18_vout_t vout = BUCK18_VOUT_3V3; vout <= BUCK18_VOUT_0V9; vout++ )
    {
        if ( BUCK18_OK == buck18_set_vout( &buck18, vout ) )
        {
            float voltage = 0;
            if ( BUCK18_OK == buck18_read_voltage( &buck18, &voltage ) ) 
            {
                log_printf( &logger, " Voltage : %.3f[V]\r\n\n", voltage );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
            }
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
