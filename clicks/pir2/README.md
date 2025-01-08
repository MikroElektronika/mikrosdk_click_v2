
---
# PIR 2 Click

> [PIR 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6052) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6052&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of PIR 2 Click boards.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PIR2

### Example Key Functions

- `pir2_cfg_setup` Config Object Initialization function.
```c
void pir2_cfg_setup ( pir2_cfg_t *cfg );
```

- `pir2_init` Initialization function.
```c
err_t pir2_init ( pir2_t *ctx, pir2_cfg_t *cfg );
```

- `pir2_read_raw_adc` This function reads raw ADC value.
```c
err_t pir2_read_raw_adc ( pir2_t *ctx, uint16_t *raw_adc );
```

- `pir2_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t pir2_read_voltage ( pir2_t *ctx, float *voltage );
```

- `pir2_set_vref` This function sets the voltage reference for PIR 2 Click driver.
```c
err_t pir2_set_vref ( pir2_t *ctx, float vref );
```

### Application Init

> Initializes the driver and selects the driver interface.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    pir2_cfg_t pir2_cfg;    /**< Click config object. */

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

    pir2_drv_interface_sel( &pir2_cfg, PIR2_DRV_SEL_I2C );

    // Click initialization.
    pir2_cfg_setup( &pir2_cfg );
    PIR2_MAP_MIKROBUS( pir2_cfg, MIKROBUS_1 );
    err_t init_flag = pir2_init( &pir2, &pir2_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> It checks if the sensor has detected movement and displays message on the USB UART.

```c
void application_task ( void ) 
{
    float voltage = 0;
    pir2_read_voltage ( &pir2, &voltage );
    if ( voltage > PIR2_VOLTAGE_TRESHOLD )
    {
        log_printf( &logger, " Motion detected \r\n" );
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
