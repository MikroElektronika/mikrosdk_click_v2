
---
# DIGI POT 6 Click

> [DIGI POT 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4110) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4110&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This example showcases how to initialize, configure and use the DIGI POT 6 Click module. The
> Click is a digital potentiometer. The potentiometer has a programmable wiper which controls 
> the resistance between P0W-POA and POW-POB. An external power supply is required for this example. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT6

### Example Key Functions

- `digipot6_cfg_setup` Config Object Initialization function. 
```c
void digipot6_cfg_setup ( digipot6_cfg_t *cfg );
``` 
 
- `digipot6_init` Initialization function. 
```c
err_t digipot6_init ( digipot6_t *ctx, digipot6_cfg_t *cfg );
```

- `digipot6_default_cfg` Click Default Configuration function. 
```c
void digipot6_default_cfg ( digipot6_t *ctx );
```

- `digipot6_read_data` This function reads data from the specified register address. 
```c
uint8_t digipot6_read_data ( digipot6_t *ctx, uint8_t reg );
``` ;
 
- `digipot6_write_wiper_cmd` This function writes a wiper configuration command to the Click module. 
```c
void digipot6_write_wiper_cmd ( digipot6_t *ctx, uint8_t cmd );
```

- `digipot6_set_resistor` This function reads data from the specified register address. 
```c
void digipot6_set_resistor ( digipot6_t *ctx, uint8_t state, uint8_t mask, uint8_t tcon );
```

### Application Init

> This function initializes and configures the logger and Click modules. This function also sets the Click default configuration. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    digipot6_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    digipot6_cfg_setup( &cfg );
    DIGIPOT6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    digipot6_init( &digipot6, &cfg );
    Delay_100ms( );
    digipot6_default_cfg( &digipot6 );
    Delay_100ms( );
}
```

### Application Task

> This function programs the wiper position and shows the current wiper position in the UART console every second.

```c
void application_task ( void )
{
    uint8_t wiper;
    uint16_t cnt;
    
    for ( cnt = 0; cnt <= 255; cnt += 15 )
    {
        digipot6_write_data( &digipot6, DIGIPOT6_VOLATILE_WIPER_0, cnt );
        Delay_ms ( 10 );

        wiper = digipot6_read_data( &digipot6, DIGIPOT6_VOLATILE_WIPER_0 );

        log_printf( &logger, " * Wiper position: %u *\r\n", ( uint16_t ) wiper );
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
