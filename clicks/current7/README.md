
---
# Current 7 Click

> [Current 7 Click](https://www.mikroe.com/?pid_product=MIKROE-4976) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4976&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for Current 7 Click driver.
> The demo application reads current ( A ).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Current7

### Example Key Functions

- `current7_cfg_setup` Config Object Initialization function.
```c
void current7_cfg_setup ( current7_cfg_t *cfg );
```

- `current7_init` Initialization function.
```c
err_t current7_init ( current7_t *ctx, current7_cfg_t *cfg );
```

- `current7_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t current7_read_voltage ( current7_t *ctx, float *voltage );
```

- `current7_get_current` This function reads the input current level [A] based on CURRENT7_NUM_CONVERSIONS of voltage measurements.
```c
err_t current7_get_current ( current7_t *ctx, float *current );
```

- `current7_set_vref` This function sets the voltage reference for Current 7 Click driver.
```c
err_t current7_set_vref ( current7_t *ctx, float vref );
```

### Application Init

> Initializes I2C or AN driver and log UART.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    current7_cfg_t current7_cfg;  /**< Click config object. */

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
    current7_cfg_setup( &current7_cfg );
    CURRENT7_MAP_MIKROBUS( current7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == current7_init( &current7, &current7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This is an example that demonstrates the use of the Current 7 Click board&trade;.
> In this example, we read and display the current ( A ) data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    float current = 0;
    current7_get_current( &current7, &current );
    log_printf( &logger, " Current : %.3f A\r\n", current );
    log_printf( &logger, "--------------------\r\n" );
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
