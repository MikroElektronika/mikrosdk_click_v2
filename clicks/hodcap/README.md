
---
# HOD CAP Click

> [HOD CAP Click](https://www.mikroe.com/?pid_product=MIKROE-5719) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5719&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for the HOD CAP Click driver. 
> The demo application sets the sensor configuration 
> and detects the changes in capacity by measuring 
> the relative change of the impedance for each channel.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HODCAP

### Example Key Functions

- `hodcap_cfg_setup` Config Object Initialization function.
```c
void hodcap_cfg_setup ( hodcap_cfg_t *cfg );
```

- `hodcap_init` Initialization function.
```c
err_t hodcap_init ( hodcap_t *ctx, hodcap_cfg_t *cfg );
```

- `hodcap_default_cfg` Click Default Configuration function.
```c
err_t hodcap_default_cfg ( hodcap_t *ctx );
```

- `hodcap_get_i_q_data` HOD CAP gets the I and Q data function.
```c
err_t hodcap_get_i_q_data ( hodcap_t *ctx, uint16_t *i_data, uint16_t *q_data );
```

- `hodcap_mux_channel_selection` HOD CAP MUX channel selection function.
```c
err_t hodcap_mux_channel_selection ( hodcap_t *ctx, uint8_t sen_pos );
```

- `hodcap_wait_adc_data_ready` HOD CAP wait ADC data ready function.
```c
err_t hodcap_wait_adc_data_ready ( hodcap_t *ctx );
```

### Application Init

> Initialization of SPI module and log UART.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hodcap_cfg_t hodcap_cfg;  /**< Click config object. */

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
    hodcap_cfg_setup( &hodcap_cfg );
    HODCAP_MAP_MIKROBUS( hodcap_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hodcap_init( &hodcap, &hodcap_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HODCAP_ERROR == hodcap_default_cfg ( &hodcap ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "________________________\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the HOD CAP Click board&trade;.
> The demo application measures the relative change of the impedance 
> and displays I and Q data per channel.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{ 
    static uint16_t i_data, q_data;
    log_printf( &logger, " \tI/Q data \r\n" );
    for ( uint8_t sen_num = 0; sen_num < HODCAP_TOTAL_NUMBER_OF_CHANNELS; sen_num++ )
    {
        if ( HODCAP_OK == hodcap_mux_channel_selection ( &hodcap, sen_num ) )
        {
            if ( ( HODCAP_OK == hodcap_wait_adc_data_ready( &hodcap ) ) &&
                 ( HODCAP_OK == hodcap_get_i_q_data( &hodcap, &i_data, &q_data ) ) )
            {
                log_printf( &logger, " SEN%d -> ", ( uint16_t ) sen_num );
                log_printf( &logger, " I : %u |", i_data );
                log_printf( &logger, " Q : %u \r\n", q_data );       
                Delay_ms ( 100 );
            }
        }
    }
    log_printf( &logger, "________________________\r\n" );
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
