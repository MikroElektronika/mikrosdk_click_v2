
---
# Hall Current 12 Click

> [Hall Current 12 Click](https://www.mikroe.com/?pid_product=MIKROE-4798) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4798&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2021.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This library contains API for Hall Current 12 Click driver. The demo application reads ADC voltage ( V ) and current ( A ).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent12

### Example Key Functions

- `hallcurrent12_cfg_setup` Config Object Initialization function.
```c
void hallcurrent12_cfg_setup ( hallcurrent12_cfg_t *cfg );
```

- `hallcurrent12_init` Initialization function.
```c
err_t hallcurrent12_init ( hallcurrent12_t *ctx, hallcurrent12_cfg_t *cfg );
```

- `hallcurrent12_calibration` Hall Current 12 calibration function.
```c
err_t hallcurrent12_calibration ( hallcurrent12_t *ctx )
```

- `hallcurrent12_get_adc` Hall Current 12 get ADC function.
```c
err_t hallcurrent12_get_adc ( hallcurrent12_t *ctx, float *adc_vtg );
```

- `hallcurrent12_get_current` Hall Current 12 get current function.
```c
err_t hallcurrent12_get_current ( hallcurrent12_t *ctx, float *current );
```

### Application Init

> Initializes the driver and logger and calibrates the device offset.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                      /**< Logger config object. */
    hallcurrent12_cfg_t hallcurrent12_cfg;  /**< Click config object. */

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
    hallcurrent12_cfg_setup( &hallcurrent12_cfg );
    HALLCURRENT12_MAP_MIKROBUS( hallcurrent12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hallcurrent12_init( &hallcurrent12, &hallcurrent12_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    log_info( &logger, " Calibrating device, remove input current in the next 5 seconds..." );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    if ( I2C_MASTER_ERROR == hallcurrent12_calibration ( &hallcurrent12 ) )
    {
        log_error( &logger, " Calibration Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    log_info( &logger, " Calibration done!" );

    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that demonstrates the use of the Hall Current 12 Click board&trade;.
> In this example, we read and display the ADC voltage ( V ) and current ( A ) data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    static float adc_voltage = 0;
    static float current = 0;
    if ( HALLCURRENT12_OK == hallcurrent12_get_adc( &hallcurrent12, &adc_voltage ) )
    {
        log_printf( &logger, " ADC voltage : %.3f V \r\n", adc_voltage );
    }
    if ( HALLCURRENT12_OK == hallcurrent12_get_current ( &hallcurrent12, &current ) )
    {
        log_printf( &logger, " Current     : %.3f A \r\n", current );
        log_printf( &logger, "--------------------------\r\n" );
    }
    Delay_ms ( 1000 );
}
```

### Note

> Switches: 
>    Sensitivity : Low ( GAIN = 1 ),
>    Vout_Sel    : AN  ( Analog interface ),
>    Vref_Sel    : VCC/2 ( bidirectional measurement ).

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
