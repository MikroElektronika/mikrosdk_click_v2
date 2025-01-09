
---
# VCT Monitor Click

> [VCT Monitor Click](https://www.mikroe.com/?pid_product=MIKROE-4353) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4353&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This is an example which demonstrates the use of VCT Monitor Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.VCTMonitor

### Example Key Functions

- `vctmonitor_cfg_setup` Config Object Initialization function.
```c
void vctmonitor_cfg_setup ( vctmonitor_cfg_t *cfg );
```

- `vctmonitor_init` Initialization function.
```c
err_t vctmonitor_init ( vctmonitor_t *ctx, vctmonitor_cfg_t *cfg );
```

- `vctmonitor_get_status` Gets status value.
```c
uint8_t vctmonitor_get_status ( vctmonitor_t *ctx );
```

- `vctmonitor_read_temperature` Get temperature function
```c
float vctmonitor_read_temperature ( vctmonitor_t *ctx );
```

- `vctmonitor_read_current` Current function
```c
float vctmonitor_read_current ( vctmonitor_t *ctx );
```

### Application Init

> Initialization driver enables the USB uart terminal and I2C. 

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vctmonitor_cfg_t vctmonitor_cfg;  /**< Click config object. */

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
    vctmonitor_cfg_setup( &vctmonitor_cfg );
    VCTMONITOR_MAP_MIKROBUS( vctmonitor_cfg, MIKROBUS_1 );
    err_t init_flag = vctmonitor_init( &vctmonitor, &vctmonitor_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads temperature, current value, and differential voltage every 4 seconds.

```c
void application_task ( void ) 
{
    float temperature;
    float voltage;
    float current;
    
    voltage = vctmonitor_read_voltage_differential( &vctmonitor );
    log_printf( &logger, " Voltage    : %.2f mV \r\n", voltage );

    current = vctmonitor_read_current( &vctmonitor );
    log_printf( &logger, " Current    : %.2f mA \r\n", current );

    temperature = vctmonitor_read_temperature( &vctmonitor );
    log_printf( &logger, " Temperature: %.2f C \r\n", temperature );

    log_printf( &logger, "- - - - - - - - - - - -\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );     
}
```

### Note

> We used the next sets for the test:
>       - Power supply - 4V
>       - Current (Load) - 0A to 3A
>       - The temperature reads from the external MMBT3904 sensor

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
