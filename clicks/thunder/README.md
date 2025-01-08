
---
# Thunder Click

> [Thunder Click](https://www.mikroe.com/?pid_product=MIKROE-1444) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1444&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application detects the presence and proximity of potentially 
lightning activity and provides estimated distance to the center of the storm. 
It can also provide information on the noise level.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thunder

### Example Key Functions

- `thunder_cfg_setup` Config Object Initialization function.
```c
void thunder_cfg_setup ( thunder_cfg_t *cfg ); 
```

- `thunder_init` Initialization function.
```c
err_t thunder_init ( thunder_t *ctx, thunder_cfg_t *cfg );
```

- `thunder_default_cfg` Click Default Configuration function.
```c
void thunder_default_cfg ( thunder_t *ctx );
```

- `thunder_check_int` Function checks and returns the interrupt value.
```c
uint8_t thunder_check_int ( thunder_t *ctx );
```

- `thunder_get_storm_info` Function gets energy of the single lightning and distance estimation for the head of the storm.
```c
void thunder_get_storm_info ( thunder_t *ctx, uint32_t *energy_out, uint8_t *distance_out );
```

- `thunder_read_reg` Function reads a data byte from the registers.
```c
err_t thunder_read_reg ( thunder_t *ctx, uint8_t reg, uint8_t *data_out );
```

### Application Init

> Initializes SPI driver and performs the reset command and RCO calibrate command. Also configures the device for working properly.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thunder_cfg_t cfg;

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
    thunder_cfg_setup( &cfg );
    THUNDER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thunder_init( &thunder, &cfg );

    thunder_default_cfg( &thunder );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Checks if the interrupt event has occured (Listening mode) and after that reads the storm information and logs the results on the USB UART.

```c
void application_task ( void )
{
    storm_mode = thunder_check_int ( &thunder );

    if ( THUNDER_NOISE_LEVEL_INTERR == storm_mode )
    {
        log_printf( &logger, "Noise level too high\r\n\n" );
    }
    else if ( THUNDER_DISTURBER_INTERR == storm_mode )
    {
        log_printf( &logger, "Disturber detected\r\n\n" );
    }
    else if ( THUNDER_LIGHTNING_INTERR == storm_mode )
    {
        thunder_get_storm_info( &thunder, &storm_energy, &storm_distance );
        log_printf( &logger, "Energy of the single lightning : %lu\r\n", storm_energy );
        log_printf( &logger, "Distance estimation : %u km\r\n\n", ( uint16_t ) storm_distance );
        // Reset configuration to prepare for the next measurement
        thunder_default_cfg( &thunder );
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
