
---
# PHT Click

> [PHT Click](https://www.mikroe.com/?pid_product=MIKROE-4348) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4348&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This is an example that demonstrates the use of the PHT Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PHT

### Example Key Functions

- `pht_cfg_setup` Config Object Initialization function.
```c
void pht_cfg_setup ( pht_cfg_t *cfg );
```

- `pht_init` Initialization function.
```c
err_t pht_init ( pht_t *ctx, pht_cfg_t *cfg );
```

- `pht_set_ratio` Set Ratio function.
```c
uint8_t pht_set_ratio ( pht_t *ctx, uint8_t temp_ratio, uint8_t press_ratio );
```

- `pht_get_temperature_pressure` Get temperature and pressure function.
```c
void pht_get_temperature_pressure ( pht_t *ctx, float *temperature, float *pressure );
```

- `pht_get_relative_humidity` Get humidity function.
```c
void pht_get_relative_humidity ( pht_t *ctx, float *humidity );
```

### Application Init

> Initialization driver enables - I2C,  performs the device reset and determines the oversampling ratio,  also write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pht_cfg_t pht_cfg;  /**< Click config object. */

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
    pht_cfg_setup( &pht_cfg );
    PHT_MAP_MIKROBUS( pht_cfg, MIKROBUS_1 );
    err_t init_flag = pht_init( &pht, &pht_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger, "--------------------------- \r\n " );
    log_printf( &logger, " Device reset \r\n" );
    pht_reset( &pht );
    Delay_ms ( 100 );
    log_printf( &logger, "--------------------------- \r\n " );
    log_printf( &logger, " Set Oversampling Ratio \r\n" );
    pht_set_ratio( &pht, PHT_PT_CMD_RATIO_2048, PHT_PT_CMD_RATIO_2048);
    Delay_ms ( 100 );
    log_printf( &logger, "--------------------------- \r\n " );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------- \r\n " );
}
```

### Application Task

> PHT Click board can be used to measure Pressure, Temperature  and Relative Humidity. All data logs write on USB uart changes every 3 sec.

```c
void application_task ( void ) 
{
    pht_get_temperature_pressure( &pht, &temperature, &pressure );
    Delay_ms ( 10 );
    pht_get_relative_humidity( &pht, &humidity );
    Delay_ms ( 10 );
    
    log_printf( &logger, " Preassure   : %.2f mbar \r\n ", pressure );
    log_printf( &logger, " Humidity    : %.2f %% \r\n ", humidity );
    log_printf( &logger, " Temperature : %.2f C \r\n ", temperature );
    log_printf( &logger, "--------------------------- \r\n " );
    Delay_ms ( 1000 );
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
