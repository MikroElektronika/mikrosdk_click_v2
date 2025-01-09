
---
# POT 5 Click

> [POT 5 Click](https://www.mikroe.com/?pid_product=MIKROE-5445) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5445&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of POT 5 Click board by reading and displaying the potentiometer position.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.POT5

### Example Key Functions

- `pot5_cfg_setup` Config Object Initialization function.
```c
void pot5_cfg_setup ( pot5_cfg_t *cfg );
```

- `pot5_init` Initialization function.
```c
err_t pot5_init ( pot5_t *ctx, pot5_cfg_t *cfg );
```

- `pot5_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t pot5_read_voltage ( pot5_t *ctx, float *voltage );
```

- `pot5_convert_voltage_to_percents` This function converts analog voltage to potentiometer position in percents.
```c
uint8_t pot5_convert_voltage_to_percents ( pot5_t *ctx, float voltage );
```

- `pot5_set_vref` This function sets the voltage reference for POT 5 Click driver.
```c
err_t pot5_set_vref ( pot5_t *ctx, float vref );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pot5_cfg_t pot5_cfg;  /**< Click config object. */

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
    pot5_cfg_setup( &pot5_cfg );
    POT5_MAP_MIKROBUS( pot5_cfg, MIKROBUS_1 );
    err_t init_flag = pot5_init( &pot5, &pot5_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays on the USB UART the potentiometer position in forms of voltage and percents once per second.

```c
void application_task ( void )
{
    float voltage = 0;
    if ( POT5_OK == pot5_read_voltage ( &pot5, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage : %.3f V\r\n", voltage );
        log_printf( &logger, " Potentiometer : %u %%\r\n\n", 
                    ( uint16_t ) pot5_convert_voltage_to_percents ( &pot5, voltage ) );
        Delay_ms ( 1000 );
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
