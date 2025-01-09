
---
# Hall Current 11 Click

> [Hall Current 11 Click](https://www.mikroe.com/?pid_product=MIKROE-4797) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4797&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for Hall Current 11 Click driver.
> The demo application reads ADC value and current ( A ).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent11

### Example Key Functions

- `hallcurrent11_cfg_setup` Config Object Initialization function.
```c
void hallcurrent11_cfg_setup ( hallcurrent11_cfg_t *cfg );
```

- `hallcurrent11_init` Initialization function.
```c
err_t hallcurrent11_init ( hallcurrent11_t *ctx, hallcurrent11_cfg_t *cfg );
```

- `hallcurrent11_default_cfg` Click Default Configuration function.
```c
err_t hallcurrent11_default_cfg ( hallcurrent11_t *ctx );
```

- `hallcurrent11_get_adc` Hall Current 11 ADC reading function.
```c
err_t hallcurrent11_get_adc ( hallcurrent11_t *ctx, uint16_t *data_out );
```

- `hallcurrent11_get_adc_voltage` Hall Current 11 get ADC voltage function.
```c
err_t hallcurrent11_get_adc_voltage ( hallcurrent11_t *ctx, float *adc_vtg );
```

- `hallcurrent11_get_current` Hall Current 11 get current function.
```c
err_t hallcurrent11_get_current ( hallcurrent11_t *ctx, float *current );
```

### Application Init

> Initializes I2C driver and log UART.
> After driver initialization the app set default settings.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                      /**< Logger config object. */
    hallcurrent11_cfg_t hallcurrent11_cfg;  /**< Click config object. */

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
    hallcurrent11_cfg_setup( &hallcurrent11_cfg );
    HALLCURRENT11_MAP_MIKROBUS( hallcurrent11_cfg, MIKROBUS_1 );
    err_t init_flag = hallcurrent11_init( &hallcurrent11, &hallcurrent11_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    hallcurrent11_default_cfg ( &hallcurrent11 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that demonstrates the use of the Hall Current 11 Click board&trade;.
> In this example, we read and display the ADC values and current ( A ) data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    static uint16_t adc_data;
    static float current;
    
    hallcurrent11_get_adc( &hallcurrent11, &adc_data );
    log_printf( &logger, " ADC Value   : %d \r\n", adc_data );
    log_printf( &logger, "- - - - - - - - - - -  - -\r\n" );
    Delay_ms ( 100 );

    hallcurrent11_get_current ( &hallcurrent11, &current );
    log_printf( &logger, " Current     : %.3f A \r\n", current );
    log_printf( &logger, "--------------------------\r\n" );
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
