
---
# DAQ 3 Click

> [DAQ 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4486) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4486&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> The demo application reads ADC value, calculate and display voltage ( mV ).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Daq3

### Example Key Functions

- `daq3_cfg_setup` Config Object Initialization function.
```c
void daq3_cfg_setup ( daq3_cfg_t *cfg );
```

- `daq3_init` Initialization function.
```c
err_t daq3_init ( daq3_t *ctx, daq3_cfg_t *cfg );
```

- `daq3_default_cfg` Click Default Configuration function.
```c
void daq3_default_cfg ( daq3_t *ctx );
```

- `daq3_get_voltage` DAQ 3 get voltage function.
```c
float daq3_get_voltage ( daq3_t *ctx );
```

- `daq3_get_conversion_result` DAQ 3 get conversion result function.
```c
int32_t daq3_get_conversion_result ( daq3_t *ctx, daq3_reg_cfg_t cfg_data );
```

- `daq3_generic_read` DAQ 3 data reading function.
```c
err_t daq3_generic_read ( daq3_t *ctx, uint8_t reg, uint8_t *data_out );
```

### Application Init

> Initializes SPI driver and start to write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;    /**< Logger config object. */
    daq3_cfg_t daq3_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    daq3_cfg_setup( &daq3_cfg );
    DAQ3_MAP_MIKROBUS( daq3_cfg, MIKROBUS_1 );
    err_t init_flag  = daq3_init( &daq3, &daq3_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    daq3_default_cfg ( &daq3 );
    log_info( &logger, " Application Task \r\n" );
    Delay_ms ( 100 );
    daq3_get_voltage( &daq3 );
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "         DAQ 3 Click       \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
}
```

### Application Task

> This is an example that demonstrates the use of the DAQ 3 Click board.
In this example, we read ADC value, calculate and display the voltage ( mV ) data.
The maximum output voltage ( Vout ) is 4V and 
depends on the gain that is set at the Click.
The formula used to calculate is Vin = Vout / gain. 
Keep in mind that Vout should not exceed 4V.
For example, if the gain is set to 2 the maximum Vin is 2V ( 2V = 4V / 2 ). 
Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{   
    float voltage = daq3_get_voltage( &daq3 );
    log_printf( &logger, "   Voltage : %.3f mV       \r\n", voltage );
    log_printf( &logger, "---------------------------\r\n" );
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
