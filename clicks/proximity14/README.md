
---
# Proximity 14 Click

> [Proximity 14 Click](https://www.mikroe.com/?pid_product=MIKROE-4744) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4744&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases the ability of the device to read proximity 
value. It can be configured to detect objects up to 20cm of distance.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity14

### Example Key Functions

- `proximity14_cfg_setup` Config Object Initialization function.
```c
void proximity14_cfg_setup ( proximity14_cfg_t *cfg );
```

- `proximity14_init` Initialization function.
```c
err_t proximity14_init ( proximity14_t *ctx, proximity14_cfg_t *cfg );
```

- `proximity14_default_cfg` Click Default Configuration function.
```c
err_t proximity14_default_cfg ( proximity14_t *ctx );
```

- `proximity14_generic_write` Writing function.
```c
err_t proximity14_generic_write ( proximity14_t *ctx, uint8_t reg, uint16_t tx_data );
```

- `proximity14_generic_read` Reading function.
```c
err_t proximity14_generic_read ( proximity14_t *ctx, uint8_t reg, uint16_t *rx_data );
```

- `proximity14_get_int` Get INT pin state.
```c
uint8_t proximity14_get_int ( proximity14_t *ctx );
```

### Application Init

> Initialization of host communication modules (UART, I2C) and 
additional pins. Reads device ID and sets default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity14_cfg_t proximity14_cfg;  /**< Click config object. */

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
    proximity14_cfg_setup( &proximity14_cfg );
    PROXIMITY14_MAP_MIKROBUS( proximity14_cfg, MIKROBUS_1 );
    err_t init_flag = proximity14_init( &proximity14, &proximity14_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    init_flag |= proximity14_default_cfg ( &proximity14 );
    if ( PROXIMITY14_OK != init_flag ) 
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint16_t temp_data = 0;
    init_flag = proximity14_generic_read( &proximity14, PROXIMITY14_REG_ID, &temp_data );
    log_printf( &logger, " > ID: 0x%.4X\r\n", temp_data );
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
}
```

### Application Task

> In span of 100ms reads proximity data from device and logs result.

```c
void application_task ( void ) 
{
    uint16_t temp_data = 0;
    proximity14_generic_read( &proximity14, PROXIMITY14_REG_DATA, &temp_data );
    log_printf( &logger, " > Data: %u\r\n", temp_data );
    Delay_ms ( 100 );
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
