
---
# Hall Current 8 25A Click

> [Hall Current 8 25A Click](https://www.mikroe.com/?pid_product=MIKROE-4632) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4632&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : ADC type

# Software Support

## Example Description

> This library contains API for Hall Current 8 25A Click driver. The library initializes and defines the ADC drivers. The library also includes a function for calibration, current measurement and overcurrent detection.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent825A

### Example Key Functions

- `hallcurrent825a_cfg_setup` Config Object Initialization function.
```c
void hallcurrent825a_cfg_setup ( hallcurrent825a_cfg_t *cfg );
```

- `hallcurrent825a_init` Initialization function.
```c
err_t hallcurrent825a_init ( hallcurrent825a_t *ctx, hallcurrent825a_cfg_t *cfg );
```

- `hallcurrent825a_calibration` This function sets the calibration value into the offset data from context object of the TLI4971 high precision coreless current sensor on Hall Current 8 25A Click board.
```c
err_t hallcurrent825a_calibration ( hallcurrent825a_t *ctx );
```

- `hallcurrent825a_get_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t hallcurrent825a_get_voltage ( hallcurrent825a_t *ctx, float *avr_voltage );
```

- `hallcurrent825a_get_current` This function reads results of AD conversion of the AN pin and converts them to proportional current level.
```c
err_t hallcurrent825a_get_current ( hallcurrent825a_t *ctx, float *current );
```

### Application Init

> Initializes ADC driver, calibrate AD conversion of the AN pin and start to write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                            /**< Logger config object. */
    hallcurrent825a_cfg_t hallcurrent825a_cfg;  /**< Click config object. */

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

    hallcurrent825a_cfg_setup( &hallcurrent825a_cfg );
    HALLCURRENT825A_MAP_MIKROBUS( hallcurrent825a_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == hallcurrent825a_init( &hallcurrent825a, &hallcurrent825a_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, " Turn OFF the power supply \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "     Start Calibration     \r\n" );
    hallcurrent825a_calibration ( &hallcurrent825a );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------------------------\r\n");
    log_printf( &logger, " Turn ON the power supply  \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------------------------\r\n");
    log_printf( &logger, "    Start measurements :   \r\n");
    log_printf( &logger, "---------------------------\r\n");
}
```

### Application Task

> This is an example that demonstrates the use of the Hall Current 8 25A Click board. 
In this example, we read and display current data [A], AN pin voltage level [V]. 
Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    float current = 0;
    float avg_voltage = 0;
    
    if ( HALLCURRENT825A_OK == hallcurrent825a_get_current ( &hallcurrent825a, &current ) ) 
    {
        log_printf( &logger, " Current        : %.2f [A]\r\n", current );
    }
    
    if ( HALLCURRENT825A_OK == hallcurrent825a_get_voltage ( &hallcurrent825a, &avg_voltage ) ) 
    {
        log_printf( &logger, " AN pin voltage : %.2f [V]\r\n", avg_voltage );
    }
    log_printf( &logger, "---------------------------\r\n");
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
