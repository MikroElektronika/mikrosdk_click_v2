
---
# Turbidity Click

> [Turbidity Click](https://www.mikroe.com/?pid_product=MIKROE-4276) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4276&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Turbidity Click driver.
> The demo application reads ADC value, ADC voltage and 
> Nephelometric Turbidity Units ( NTU ).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Turbidity

### Example Key Functions

- `turbidity_cfg_setup` Config Object Initialization function.
```c
void turbidity_cfg_setup ( turbidity_cfg_t *cfg );
```

- `turbidity_init` Initialization function.
```c
err_t turbidity_init ( turbidity_t *ctx, turbidity_cfg_t *cfg );
```

- `turbidity_default_cfg` Click Default Configuration function.
```c
err_t turbidity_default_cfg ( turbidity_t *ctx );
```

- `turbidity_get_ntu` Turbidity get NTU function.
```c
err_t turbidity_get_ntu ( turbidity_t *ctx, float *ntu );
```

- `turbidity_read_adc` Turbidity read ADC function.
```c
err_t turbidity_read_adc ( turbidity_t *ctx, uint16_t *adc_val );
```

- `turbidity_get_adc_voltage` Turbidity get voltage function.
```c
err_t turbidity_get_adc_voltage ( turbidity_t *ctx, float *voltage );
```

### Application Init

> nitialization of I2C module and log UART.
> After driver initialization, default settings turn on the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    turbidity_cfg_t turbidity_cfg;  /**< Click config object. */

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
    turbidity_cfg_setup( &turbidity_cfg );
    TURBIDITY_MAP_MIKROBUS( turbidity_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == turbidity_init( &turbidity, &turbidity_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TURBIDITY_ERROR == turbidity_default_cfg ( &turbidity ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Turbidity Click board&trade;.
> In this example, we monitor and display Nephelometric Turbidity Units ( NTU ).
> Results are being sent to the Usart Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static float ntu;
    
    turbidity_get_ntu( &turbidity, &ntu );
    log_printf( &logger, "\tNTU : %.2f\r\n", ntu );
    log_printf( &logger, "----------------------------\r\n" );
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
