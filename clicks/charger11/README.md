
---
# Charger 11 Click

> [Charger 11 Click](https://www.mikroe.com/?pid_product=MIKROE-3650) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3650&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the Charger 11 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger11

### Example Key Functions

- `charger11_cfg_setup` Config Object Initialization function.
```c
void charger11_cfg_setup ( charger11_cfg_t *cfg );
```

- `charger11_init` Initialization function.
```c
err_t charger11_init ( charger11_t *ctx, charger11_cfg_t *cfg );
```

- `charger11_spi_increment_wiper` Charger 11 incrementing wiper position.
```c
void charger11_spi_increment_wiper( charger11_t *ctx );
```

- `charger11_spi_decrement_wiper` Charger 11 decrementing wiper position.
```c
void charger11_spi_decrement_wiper( charger11_t *ctx );
```

- `charger11_i2c_get_volt` Charger 11 getting output voltage.
```c
float charger11_i2c_get_volt( charger11_t *ctx, float reference_voltage );
```

### Application Init

> Initalizes INT ( ST ), PWM ( LG ), AN ( LR ) pins and SPI, I2C, LOG modules.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger11_cfg_t charger11_cfg;  /**< Click config object. */

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
    charger11_cfg_setup( &charger11_cfg );
    CHARGER11_MAP_MIKROBUS( charger11_cfg, MIKROBUS_1 );
    err_t init_flag  = charger11_init( &charger11, &charger11_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    charger11_case_report( &charger11 );
}
```

### Application Task

> Waits for user input in order to increment, decrement wiper or log report (Wiper position and Output voltage)

```c
void application_task ( void ) 
{
    char uart_char;
    if ( log_read( &logger, &uart_char, 1 ) ) {
        switch (uart_char) {
            case '+' : {
                charger11_case_plus( &charger11 );
                break;
            }
            case '-' : {
                charger11_case_minus( &charger11 );
                break;
            }
            case 'r' : {
                charger11_case_report( &charger11 );
                break;
            }
            default : {
                log_printf( &logger, "> Invalid command \r\n" );
                break;
            }
        }
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
