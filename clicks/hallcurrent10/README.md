
---
# Hall Current 10 Click

> [Hall Current 10 Click](https://www.mikroe.com/?pid_product=MIKROE-4587) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4587&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for Hall Current 10 Click driver.
> The demo application reads ADC value, ADC voltage and current value.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent10

### Example Key Functions

- `hallcurrent10_cfg_setup` Config Object Initialization function.
```c
void hallcurrent10_cfg_setup ( hallcurrent10_cfg_t *cfg );
```

- `hallcurrent10_init` Initialization function.
```c
err_t hallcurrent10_init ( hallcurrent10_t *ctx, hallcurrent10_cfg_t *cfg );
```

- `hallcurrent10_default_cfg` Click Default Configuration function.
```c
void hallcurrent10_default_cfg ( hallcurrent10_t *ctx );
```

- `hallcurrent10_read_adc` Hall Current 10 I2C ADC reading function.
```c
err_t hallcurrent10_read_adc ( hallcurrent10_t *ctx, uint16_t *read_adc );
```

- `hallcurrent10_get_adc_volatge` Hall Current 10 get ADC voltage function.
```c
err_t hallcurrent10_get_adc_voltage ( hallcurrent10_t *ctx, float *adc_vtg );
```

- `hallcurrent10_get_current` Hall Current 10 get current function.
```c
err_t hallcurrent10_get_current ( hallcurrent10_t *ctx, float *current );
```

### Application Init

> Initializes I2C driver and log UART.
> After driver initialization the app set default settings.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                      /**< Logger config object. */
    hallcurrent10_cfg_t hallcurrent10_cfg;  /**< Click config object. */

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
    hallcurrent10_cfg_setup( &hallcurrent10_cfg );
    HALLCURRENT10_MAP_MIKROBUS( hallcurrent10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hallcurrent10_init( &hallcurrent10, &hallcurrent10_cfg ) ) 
    {
        log_info( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that demonstrates the use of the Hall Current 10 Click board&trade;.
> In this example, we read and display the ADC values and current ( mA ) data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    hallcurrent10_read_adc( &hallcurrent10, &adc_data );
    log_printf( &logger, " ADC Value   : %d \r\n", adc_data );
    Delay_ms ( 100 );
    
    hallcurrent10_get_adc_voltage( &hallcurrent10, &adc_voltage );
    log_printf( &logger, " ADC Voltage : %.2f mV \r\n", adc_voltage );
    log_printf( &logger, "- - - - - - - - - - -  - -\r\n" );
    Delay_ms ( 100 );
    
    hallcurrent10_get_current ( &hallcurrent10, &current );
    log_printf( &logger, " Current     : %.2f mA \r\n", current );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
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
