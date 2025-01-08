
---
# UV Click

> [UV Click](https://www.mikroe.com/?pid_product=MIKROE-1677) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1677&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This is a example which demonstrates the use of UV Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Uv

### Example Key Functions

- `uv_cfg_setup` Config Object Initialization function.
```c
void uv_cfg_setup ( uv_cfg_t *cfg ); 
```

- `uv_init` Initialization function.
```c
err_t uv_init ( uv_t *ctx, uv_cfg_t *cfg );
```

- `uv_read_adc_voltage` ADC Voltage Reading function.
```c
err_t uv_read_adc_voltage ( uv_t *ctx, float *data_out );
```

- `uv_calc_index` UV Index Calculation function.
```c
void uv_calc_index ( uv_t *ctx, float data_in, uint8_t *data_out );
```

### Application Init

> Configuration of the Click and log objects.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    uv_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    // Click initialization.
    uv_cfg_setup( &cfg );
    UV_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == uv_init( &uv, &cfg ) )
    {
        log_info( &logger, "---- Application Init Error ----" );
        log_info( &logger, "---- Please, run program again ----" );
        for ( ; ; );
    }
    uv_set_callback_handler( &uv, application_callback );
    uv_device_enable( &uv );
    Delay_ms ( 1000 );
    uv_voltage = 0;
    uv_index = 0;
    log_info( &logger, "---- Application Init Done ----\r\n" );
}
```

### Application Task

> Reads the result of AD conversion once per second and calculates the UV index based on that. Results are being sent to the USB UART where you can track their changes.

```c
void application_task ( void )
{
    if ( SPI_MASTER_ERROR != uv_read_adc_voltage( &uv, &uv_voltage ) )
    {
        uv_calc_index( &uv, uv_voltage, &uv_index );

        log_printf( &logger, " UV Index [0-15] : %u\r\n", ( uint16_t ) uv_index );
        log_printf( &logger, " UV ADC Voltage [V] : %.2f\r\n", uv_voltage );
        log_printf( &logger, "------------------------------\r\n" );
    }

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
