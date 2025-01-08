
---
# PCR Click

> [PCR Click](https://www.mikroe.com/?pid_product=MIKROE-4636) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4636&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of PCR Click board by 
  reading distance between Click board and object. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PCR

### Example Key Functions

- `pcr_cfg_setup` Config Object Initialization function.
```c
void pcr_cfg_setup ( pcr_cfg_t *cfg );
```

- `pcr_init` Initialization function.
```c
err_t pcr_init ( pcr_t *ctx, pcr_cfg_t *cfg );
```

- `pcr_default_cfg` Click Default Configuration function.
```c
err_t pcr_default_cfg ( pcr_t *ctx );
```

- `pcr_write_reg` PCR register writing function.
```c
err_t pcr_write_reg ( pcr_t *ctx, uint16_t reg, uint32_t data_in );
```

- `pcr_check_if_busy` PCR check if device is busy function.
```c
err_t pcr_check_if_busy ( pcr_t *ctx );
```

- `pcr_get_distance` PCR read distance function.
```c
err_t pcr_get_distance ( pcr_t *ctx, uint32_t *distance_data );
```

### Application Init

> Initializes the driver and logger and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pcr_cfg_t pcr_cfg;  /**< Click config object. */

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
    pcr_cfg_setup( &pcr_cfg );
    PCR_MAP_MIKROBUS( pcr_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pcr_init( &pcr, &pcr_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PCR_ERROR == pcr_default_cfg ( &pcr ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reading distance between Click board and object every 2 seconds and logging it on UART terminal.

```c
void application_task ( void ) 
{
    uint32_t distance_data = 0;

    pcr_get_distance ( &pcr, &distance_data );
    log_printf( &logger, " Distance: %lu mm \r\n", distance_data );
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
