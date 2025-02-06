
---
# Nixie Power IN-12B Click

> [Nixie Power IN-12B Click](https://www.mikroe.com/?pid_product=MIKROE-6496) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6496&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Nixie Power IN-12B Click board by displaying digits from 0 to 9 in sequence and then setting a comma indicator.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NixiePowerIN12B

### Example Key Functions

- `nixiepowerin12b_cfg_setup` Config Object Initialization function.
```c
void nixiepowerin12b_cfg_setup ( nixiepowerin12b_cfg_t *cfg );
```

- `nixiepowerin12b_init` Initialization function.
```c
err_t nixiepowerin12b_init ( nixiepowerin12b_t *ctx, nixiepowerin12b_cfg_t *cfg );
```

- `nixiepowerin12b_default_cfg` Click Default Configuration function.
```c
err_t nixiepowerin12b_default_cfg ( nixiepowerin12b_t *ctx );
```

- `nixiepowerin12b_set_digit` This function sets the display output digit and comma.
```c
err_t nixiepowerin12b_set_digit ( nixiepowerin12b_t *ctx, uint8_t digit, uint8_t comma );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nixiepowerin12b_cfg_t nixiepowerin12b_cfg;  /**< Click config object. */

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
    nixiepowerin12b_cfg_setup( &nixiepowerin12b_cfg );
    NIXIEPOWERIN12B_MAP_MIKROBUS( nixiepowerin12b_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == nixiepowerin12b_init( &nixiepowerin12b, &nixiepowerin12b_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( NIXIEPOWERIN12B_ERROR == nixiepowerin12b_default_cfg ( &nixiepowerin12b ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Sequentially displays digits 0 through 9 on a IN-12B display, with a 1-second delay
between each digit. After displaying all digits, it clears the digits and enables
a comma indicator on the display. Each operation is logged on the USB UART.

```c
void application_task ( void )
{
    for ( uint8_t digit = NIXIEPOWERIN12B_DIGIT_0; digit <= NIXIEPOWERIN12B_DIGIT_9; digit++ )
    {
        if ( NIXIEPOWERIN12B_OK == nixiepowerin12b_set_digit ( &nixiepowerin12b, 
                                                               digit, 
                                                               NIXIEPOWERIN12B_COMMA_CLEAR ) )
        {
            log_printf ( &logger, " Digit %u\r\n", ( uint16_t ) digit );
        }
        Delay_ms ( 1000 );
    }
    if ( NIXIEPOWERIN12B_OK == nixiepowerin12b_set_digit ( &nixiepowerin12b, 
                                                           NIXIEPOWERIN12B_DIGIT_NONE, 
                                                           NIXIEPOWERIN12B_COMMA_SET ) )
    {
        log_printf ( &logger, " Comma\r\n" );
    }
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
