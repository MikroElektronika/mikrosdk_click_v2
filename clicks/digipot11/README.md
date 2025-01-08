
---
# DIGI POT 11 Click

> [DIGI POT 11 Click](https://www.mikroe.com/?pid_product=MIKROE-5318) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5318&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of DIGI POT 11 Click board by changing the wipers position of both U1 and U2 devices.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT11

### Example Key Functions

- `digipot11_cfg_setup` Config Object Initialization function.
```c
void digipot11_cfg_setup ( digipot11_cfg_t *cfg );
```

- `digipot11_init` Initialization function.
```c
err_t digipot11_init ( digipot11_t *ctx, digipot11_cfg_t *cfg );
```

- `digipot11_set_u1_wiper` This function sets the position of the selected wiper of U1 device by using I2C serial interface.
```c
err_t digipot11_set_u1_wiper ( digipot11_t *ctx, uint8_t wiper_sel, uint8_t data_in );
```

- `digipot11_set_u2_wiper` This function sets the position of the selected wiper of U2 device by using I2C serial interface.
```c
err_t digipot11_set_u2_wiper ( digipot11_t *ctx, uint8_t wiper_sel, uint8_t data_in );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot11_cfg_t digipot11_cfg;  /**< Click config object. */

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
    digipot11_cfg_setup( &digipot11_cfg );
    DIGIPOT11_MAP_MIKROBUS( digipot11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == digipot11_init( &digipot11, &digipot11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Iterates through the entire wiper range and sets the wipers position of both U1 and U2 devices once per second. The current wiper position will be displayed on the USB UART.

```c
void application_task ( void )
{
    for ( uint16_t wiper_pos = DIGIPOT11_WIPER_ZERO_SCALE; wiper_pos <= DIGIPOT11_WIPER_FULL_SCALE; wiper_pos += 5 )
    {
        if ( DIGIPOT11_OK == digipot11_set_u1_wiper ( &digipot11, DIGIPOT11_WIPER_SEL_BOTH, ( uint8_t ) wiper_pos ) )
        {
            log_printf( &logger, " U1 wipers position: %u\r\n", wiper_pos );
        }
        if ( DIGIPOT11_OK == digipot11_set_u2_wiper ( &digipot11, DIGIPOT11_WIPER_SEL_BOTH, 
                                                      ( uint8_t ) ( DIGIPOT11_WIPER_FULL_SCALE - wiper_pos ) ) )
        {
            log_printf( &logger, " U2 wipers position: %u\r\n\n", ( DIGIPOT11_WIPER_FULL_SCALE - wiper_pos ) );
        }
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
