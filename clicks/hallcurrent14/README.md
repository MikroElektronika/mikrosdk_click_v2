
---
# Hall Current 14 Click

> [Hall Current 14 Click](https://www.mikroe.com/?pid_product=MIKROE-5239) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5239&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2022.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of Hall Current 14 Click board by reading and displaying the input current measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent14

### Example Key Functions

- `hallcurrent14_cfg_setup` Config Object Initialization function.
```c
void hallcurrent14_cfg_setup ( hallcurrent14_cfg_t *cfg );
```

- `hallcurrent14_init` Initialization function.
```c
err_t hallcurrent14_init ( hallcurrent14_t *ctx, hallcurrent14_cfg_t *cfg );
```

- `hallcurrent14_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t hallcurrent14_read_voltage ( hallcurrent14_t *ctx, float *voltage );
```

- `hallcurrent14_set_vref` This function sets the voltage reference for Hall Current 14 Click driver.
```c
err_t hallcurrent14_set_vref ( hallcurrent14_t *ctx, float vref );
```

- `hallcurrent14_read_current` This function reads the input current level [A] based on @b HALLCURRENT14_NUM_CONVERSIONS of voltage measurements.
```c
err_t hallcurrent14_read_current ( hallcurrent14_t *ctx, float *current );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent14_cfg_t hallcurrent14_cfg;  /**< Click config object. */

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
    hallcurrent14_cfg_setup( &hallcurrent14_cfg );
    HALLCURRENT14_MAP_MIKROBUS( hallcurrent14_cfg, MIKROBUS_1 );
    err_t init_flag = hallcurrent14_init( &hallcurrent14, &hallcurrent14_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the input current measurements and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float current = 0;
    if ( HALLCURRENT14_OK == hallcurrent14_read_current ( &hallcurrent14, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f[A]\r\n\n", current );
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
