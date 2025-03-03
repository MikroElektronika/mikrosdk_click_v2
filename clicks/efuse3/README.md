
---
# e Fuse 3 Click

> [e Fuse 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4630) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4630&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for the eFuse 3 Click driver.
> The library contains drivers to enable/disable the device, 
> for reading ADC voltage, overflow status, output and current value [ A ].

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.eFuse3

### Example Key Functions

- `efuse3_cfg_setup` Config Object Initialization function.
```c
void efuse3_cfg_setup ( efuse3_cfg_t *cfg );
```

- `efuse3_init` Initialization function.
```c
err_t efuse3_init ( efuse3_t *ctx, efuse3_cfg_t *cfg );
```

- `efuse3_default_cfg` Click Default Configuration function.
```c
void efuse3_default_cfg ( efuse3_t *ctx );
```

- `efuse3_get_current` e Fuse 3 get current function.
```c
err_t efuse3_get_current ( efuse3_t *ctx, float *current );
```

- `efuse3_get_flag` e Fuse 3 get flag function.
```c
uint8_t efuse3_get_flag ( efuse3_t *ctx );
```

- `efuse3_reset` e Fuse 3 reset function.
```c
void efuse3_reset ( efuse3_t *ctx );
```

### Application Init

> Initializes SPI driver and set default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;        /**< Logger config object. */
    efuse3_cfg_t efuse3_cfg;  /**< Click config object. */

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

    efuse3_cfg_setup( &efuse3_cfg );
    EFUSE3_MAP_MIKROBUS( efuse3_cfg, MIKROBUS_1 );
    err_t init_flag  = efuse3_init( &efuse3, &efuse3_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    efuse3_default_cfg ( &efuse3 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that demonstrates the use of the eFuse 3 Click board. 
> Read and display device status information and current value [ A ].
> The eFuse 3 includes an overvoltage clamp the circuit that limits the output voltage
> during transients but does not shut the unit down, 
> thereby allowing the load circuit to continue its operation.
> The Electronic Fuse is to limit current and current limit 
> Current limit ( 0.1 A - 1.8 A ) depends on the choice of resistor wired 
> on the Rlimit ( 1 Ohm - 15 Ohm ) connector.
> For example, for Rlimit resistance of 1 Ohm, current limit is 1 A 
> ( 3.5 Ohm - 0.5 A, 7 Ohm - 0.25 A ). 
> Read details from the ON Semiconductor NIS6150 datasheets.   
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    log_printf( &logger, " Status  :" );    
    
    if ( efuse3_get_flag( &efuse3 ) == EFUSE3_FLAG_NORMAL_OPERATION ) {
        log_printf( &logger, " Normal operation \r\n" );
    } else {
        log_printf( &logger, " Device OFF \r\n" );

        if ( overflow_status == EFUSE3_OVERFLOW_HIGH ) {
            log_printf( &logger, " Overflow high in the analog input voltage.\r\n" );    
        } else if ( overflow_status == EFUSE3_OVERFLOW_LOW ) {
            log_printf( &logger, " Overflow low in the analog input voltage.\r\n" ); 
        }
        
        efuse3_reset( &efuse3 );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, "- - - - - - - - - - - - - - \r\n" );
    efuse3_get_current( &efuse3, &current );
    log_printf( &logger, " Current : %.5f A\r\n", current );
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
