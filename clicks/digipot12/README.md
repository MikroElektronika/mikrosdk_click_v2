
---
# DIGI POT 12 Click

> [DIGI POT 12 Click](https://www.mikroe.com/?pid_product=MIKROE-5656) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5656&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for DIGI POT 12 Click driver.
> The demo application uses a digital potentiometer 
> to change the resistance values of both channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT12

### Example Key Functions

- `digipot12_cfg_setup` Config Object Initialization function.
```c
void digipot12_cfg_setup ( digipot12_cfg_t *cfg );
```

- `digipot12_init` Initialization function.
```c
err_t digipot12_init ( digipot12_t *ctx, digipot12_cfg_t *cfg );
```

- `digipot12_default_cfg` Click Default Configuration function.
```c
err_t digipot12_default_cfg ( digipot12_t *ctx );
```

- `digipot12_set_resistance` DIGI POT 12 set the resistance function.
```c
err_t digipot12_set_resistance ( digipot12_t *ctx, uint8_t wiper_sel, float res_kohm );
```

- `digipot12_get_resistance` DIGI POT 12 get the resistance function.
```c
err_t digipot12_get_resistance ( digipot12_t *ctx, uint8_t wiper_sel, float *res_kohm );
```

### Application Init

> The initialization of I2C module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot12_cfg_t digipot12_cfg;  /**< Click config object. */

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
    digipot12_cfg_setup( &digipot12_cfg );
    DIGIPOT12_MAP_MIKROBUS( digipot12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == digipot12_init( &digipot12, &digipot12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIPOT12_ERROR == digipot12_default_cfg ( &digipot12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the DIGI POT 12 Click board&trade;.
> The demo application iterates through the entire wiper range and 
> sets the resistance of both channels in steps of approximately 1kOhm.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static float res_kohm;
    for ( uint8_t n_cnt = DIGIPOT12_RES_0_KOHM; n_cnt <= DIGIPOT12_RES_10_KOHM; n_cnt++ )
    {
        if ( DIGIPOT12_OK == digipot12_set_resistance( &digipot12, DIGIPOT12_WIPER_SEL_1, ( float ) n_cnt ) )
        {
            if ( DIGIPOT12_OK == digipot12_get_resistance( &digipot12, DIGIPOT12_WIPER_SEL_1, &res_kohm ) )
            {
                log_printf( &logger, " Rwb1 : %.2f kOhm\r\n", res_kohm );
                Delay_ms ( 100 );
            }
        }
        
        if ( DIGIPOT12_OK == digipot12_set_resistance( &digipot12, DIGIPOT12_WIPER_SEL_2, ( float ) ( DIGIPOT12_RES_10_KOHM - n_cnt ) ) )
        {
            if ( DIGIPOT12_OK == digipot12_get_resistance( &digipot12, DIGIPOT12_WIPER_SEL_2, &res_kohm ) )
            {
                log_printf( &logger, " Rwb2 : %.2f kOhm\r\n", res_kohm );
                Delay_ms ( 100 );
            }
        }
        log_printf( &logger, " ----------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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
