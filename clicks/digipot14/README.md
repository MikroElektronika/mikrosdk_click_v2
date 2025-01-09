
---
# DIGI POT 14 Click

> [DIGI POT 14 Click](https://www.mikroe.com/?pid_product=MIKROE-5814) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5814&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for DIGI POT 14 Click driver.
  The demo application uses a digital potentiometer 
  to change the resistance values.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT14

### Example Key Functions

- `digipot14_cfg_setup` Config Object Initialization function.
```c
void digipot14_cfg_setup ( digipot14_cfg_t *cfg );
```

- `digipot14_init` Initialization function.
```c
err_t digipot14_init ( digipot14_t *ctx, digipot14_cfg_t *cfg );
```

- `digipot14_default_cfg` Click Default Configuration function.
```c
err_t digipot14_default_cfg ( digipot14_t *ctx );
```

- `digipot14_reg_write` DIGI POT 14 register write function.
```c
err_t digipot14_reg_write ( digipot14_t *ctx, uint8_t reg, uint8_t data_in );
```

- `digipot14_set_pot_a_wiper` DIGI POT 14 set the wiper position of potentiometer A function.
```c
err_t digipot14_set_pot_a_wiper ( digipot14_t *ctx, uint8_t wiper_pos );
```

- `digipot14_set_pot_b_wiper` DIGI POT 14 set the wiper position of potentiometer B function.
```c
err_t digipot14_set_pot_b_wiper ( digipot14_t *ctx, uint8_t wiper_pos );
```

### Application Init

> The initialization of I2C module, log UART, and additional pins.
  After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot14_cfg_t digipot14_cfg;  /**< Click config object. */

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
    digipot14_cfg_setup( &digipot14_cfg );
    DIGIPOT14_MAP_MIKROBUS( digipot14_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == digipot14_init( &digipot14, &digipot14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIPOT14_ERROR == digipot14_default_cfg ( &digipot14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the DIGI POT 14 Click board&trade;.
  The demo application iterates through the entire wiper range.
  Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    for ( uint8_t wiper_val = DIGIPOT14_MIN_POSITION; wiper_val <= DIGIPOT14_MAX_POSITION; wiper_val++ )
    {
        
        digipot14_set_pot_a_wiper( &digipot14, wiper_val );
        digipot14_set_pot_b_wiper( &digipot14, wiper_val );
        log_printf( &logger, " Resistance = %.3f KOhm \r\n", 
                    ( DIGIPOT14_MAX_RESISTANCE_KOHM * ( wiper_val / DIGIPOT14_MAX_POSITION_NUM ) ) );
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
