
---
# DAC 15 Click

> [DAC 15 Click](https://www.mikroe.com/?pid_product=MIKROE-5825) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5825&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2023.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of DAC 15 Click board&trade; 
> by changing the output voltage level on the VOUTA and VOUTB.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC15

### Example Key Functions

- `dac15_cfg_setup` Config Object Initialization function.
```c
void dac15_cfg_setup ( dac15_cfg_t *cfg );
```

- `dac15_init` Initialization function.
```c
err_t dac15_init ( dac15_t *ctx, dac15_cfg_t *cfg );
```

- `dac15_default_cfg` Click Default Configuration function.
```c
err_t dac15_default_cfg ( dac15_t *ctx );
```

- `dac15_set_dac_data` DAC 15 set DAC data function.
```c
err_t dac15_set_dac_data ( dac15_t *ctx, uint8_t dac_sel, uint16_t dac_data );
```

- `dac15_get_dac_data` DAC 15 get DAC data function.
```c
err_t dac15_get_dac_data ( dac15_t *ctx, uint8_t dac_sel, uint16_t *dac_data );
```

### Application Init

> Initialization of I2C or SPI module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac15_cfg_t dac15_cfg;  /**< Click config object. */

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
    dac15_cfg_setup( &dac15_cfg );
    DAC15_MAP_MIKROBUS( dac15_cfg, MIKROBUS_1 );
    err_t init_flag = dac15_init( &dac15, &dac15_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC15_ERROR == dac15_default_cfg ( &dac15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application changes the output voltage level on the VOUTA and VOUTB.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{   
    static uint16_t dac_data = 0;
    for ( uint16_t n_cnt = 0; n_cnt < 60000; n_cnt += 5000 )
    {
        dac_data = n_cnt;
        if ( DAC15_OK == dac15_set_dac_data( &dac15, DAC15_SET_DAC_A, dac_data ) )
        {
            log_printf( &logger, "VOUTA: %u -> %.2f V\r\n", 
                        dac_data, 
                        ( float ) dac_data * DAC15_VREF_3V3 / DAC15_MAX_DAC_DATA );
        }
        
        dac_data = DAC15_DAC_RES_16BIT - n_cnt;
        if ( DAC15_OK == dac15_set_dac_data( &dac15, DAC15_SET_DAC_B, dac_data ) )
        {
            log_printf( &logger, "VOUTB: %u -> %.2f V\r\n", 
                        dac_data, 
                        ( float ) dac_data * DAC15_VREF_3V3 / DAC15_MAX_DAC_DATA );
        }
        log_printf( &logger, " -------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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
