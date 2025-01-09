
---
# MUX 4 Click

> [MUX 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4754) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4754&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of MUX 4 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MUX4

### Example Key Functions

- `mux4_cfg_setup` Config Object Initialization function.
```c
void mux4_cfg_setup ( mux4_cfg_t *cfg );
```

- `mux4_init` Initialization function.
```c
err_t mux4_init ( mux4_t *ctx, mux4_cfg_t *cfg );
```

- `mux4_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t mux4_read_an_pin_voltage ( mux4_t *ctx, float *data_out );
```

- `mux4_enable_input` This function enable or disables analog inputs.
```c
void mux4_enable_input ( mux4_t *ctx, uint8_t en_state );
```

- `mux4_select_input` This function selects which input channel signal is being forwarded to the AN/EXT pin.
```c
void mux4_select_input ( mux4_t *ctx, uint8_t input );
```

### Application Init

> Initializes the driver and enables analog inputs.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;    /**< Logger config object. */
    mux4_cfg_t mux4_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    mux4_cfg_setup( &mux4_cfg );
    MUX4_MAP_MIKROBUS( mux4_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == mux4_init( &mux4, &mux4_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    mux4_enable_input( &mux4, MUX4_ENABLE_INPUT );
}
```

### Application Task

> Reads the voltage from all input channels and displays the values of each channel on the USB UART approximately every second.

```c
void application_task ( void )
{
    float mux4_an_voltage = 0;

    for ( uint8_t cnt = MUX4_SELECT_INPUT_1; cnt <= MUX4_SELECT_INPUT_8; cnt++ )
    {
        mux4_select_input( &mux4, cnt );
        Delay_ms ( 10 );
        if ( ADC_ERROR != mux4_read_an_pin_voltage ( &mux4, &mux4_an_voltage ) ) 
        {
            log_printf( &logger, " CH%u Voltage : %.3f V\r\n", ( uint16_t ) cnt, mux4_an_voltage );
        }
    }
    log_printf( &logger, " ----------------------------\r\n" );
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
