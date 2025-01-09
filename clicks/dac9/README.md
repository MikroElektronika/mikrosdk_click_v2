
---
# DAC 9 Click

> [DAC 9 Click](https://www.mikroe.com/?pid_product=MIKROE-4332) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4332&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the DAC 9 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC9

### Example Key Functions

- `dac9_cfg_setup` Config Object Initialization function.
```c
void dac9_cfg_setup ( dac9_cfg_t *cfg );
```

- `dac9_init` Initialization function.
```c
err_t dac9_init ( dac9_t *ctx, dac9_cfg_t *cfg );
```

- `dac9_set_config` Set config function.
```c
err_t dac9_set_config ( dac9_t *ctx, uint16_t en_ref_pwdwn, uint16_t en_dac_pwdwn );
```

- `dac9_set_gain` Set gain function.
```c
err_t dac9_set_gain ( dac9_t *ctx, uint16_t en_ref_div, uint16_t en_buff_gain );
```

- `dac9_set_vout` Set Vout function.
```c
err_t dac9_set_vout ( dac9_t *ctx, uint16_t vout_mv );
```

### Application Init

> Initalizes SPI or I2C driver and applies default settings.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac9_cfg_t dac9_cfg;  /**< Click config object. */

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
    dac9_cfg_setup( &dac9_cfg );
    DAC9_MAP_MIKROBUS( dac9_cfg, MIKROBUS_1 );
    err_t init_flag  = dac9_init( &dac9, &dac9_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "     Soft reset      \r\n" );
    dac9_soft_reset( &dac9 );
    Delay_ms ( 200 );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Vref divided by 2  \r\n" );
    log_printf( &logger, "  Set DAC gain of 2  \r\n" );
    dac9_set_gain( &dac9, DAC9_GAIN_REF_DIV_2, DAC9_GAIN_BUFF_GAIN_2 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "---------------------\r\n" );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Demonstrates use of DAC 9 Click board by changeing output values every two seconds.

```c
void application_task ( void ) 
{
    uint16_t n_cnt;
    for ( n_cnt = 0; n_cnt <= res; n_cnt += 500 ) {
        log_printf( &logger, "Output Voltage : %d mV\r\n", ( uint16_t ) n_cnt );
        dac9_set_vout( &dac9, n_cnt );
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
