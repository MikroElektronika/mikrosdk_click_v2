
---
# V to Hz 3 Click

> [V to Hz 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5250) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5250&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the V to Hz 3 Click board by calculating the estimated output frequency from the input voltage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.VtoHz3

### Example Key Functions

- `vtohz3_cfg_setup` Config Object Initialization function.
```c
void vtohz3_cfg_setup ( vtohz3_cfg_t *cfg );
```

- `vtohz3_init` Initialization function.
```c
err_t vtohz3_init ( vtohz3_t *ctx, vtohz3_cfg_t *cfg );
```

- `vtohz3_set_input_frequency` This function enables and sets output frequency of the programmable oscillator, which is the AD7740 input frequency.
```c
err_t vtohz3_set_input_frequency ( vtohz3_t *ctx, uint32_t freq );
```

- `vtohz3_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t vtohz3_read_an_pin_voltage ( vtohz3_t *ctx, float *data_out );
```

- `vtohz3_get_frequency` This function converts voltage to the estimated output frequency in Hz.
```c
uint32_t vtohz3_get_frequency ( vtohz3_t *ctx, float voltage, float vref_in );
```

### Application Init

> Initializes the driver and sets the input frequency.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;        /**< Logger config object. */
    vtohz3_cfg_t vtohz3_cfg;  /**< Click config object. */

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
    vtohz3_cfg_setup( &vtohz3_cfg );
    VTOHZ3_MAP_MIKROBUS( vtohz3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == vtohz3_init( &vtohz3, &vtohz3_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    vtohz3_set_input_frequency ( &vtohz3, VTOHZ3_DEFAULT_IN_FREQUENCY );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the input voltage from AN pin and calculates the output frequency from it. The results are being displayed on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float voltage;
    if ( VTOHZ3_OK == vtohz3_read_an_pin_voltage ( &vtohz3, &voltage ) ) 
    {
        log_printf( &logger, " Voltage : %.2f V\r\n", voltage );
        log_printf( &logger, " Output frequency : %lu Hz\r\n\n", 
                    vtohz3_get_frequency ( &vtohz3, voltage, VTOHZ3_VREF_INTERNAL_2V5 ) );
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
