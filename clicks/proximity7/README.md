
---
# PROXIMITY 7 Click

> [PROXIMITY 7 Click](https://www.mikroe.com/?pid_product=MIKROE-3330) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3330&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application give us lux level and proximiti data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity7

### Example Key Functions

- `proximity7_cfg_setup` Config Object Initialization function. 
```c
void proximity7_cfg_setup ( proximity7_cfg_t *cfg );
``` 
 
- `proximity7_init` Initialization function. 
```c
err_t proximity7_init ( proximity7_t *ctx, proximity7_cfg_t *cfg );
```

- `proximity7_default_cfg` Click Default Configuration function. 
```c
void proximity7_default_cfg ( proximity7_t *ctx );
```

- `proximity7_get_proximity_data` Get proximity data. 
```c
uint16_t proximity7_get_proximity_data ( proximity7_t *ctx  );
```
 
- `proximity7_get_lux_level` Get lux level. 
```c
float proximity7_get_lux_level ( proximity7_t *ctx  );
```

- `proximity7_set_proximity_offset` Set proximity offset. 
```c
uint8_t proximity7_set_proximity_offset (  proximity7_t *ctx, uint8_t proximity_offset_magnitude  );
```

### Application Init

> Initializes I2C driver and writes basic settings to device registers

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity7_cfg_t cfg;

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

    proximity7_cfg_setup( &cfg );
    PROXIMITY7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity7_init( &proximity7, &cfg );

    Delay_ms ( 100 );

    log_printf( &logger, "> > > app init done < < <\r\n" );

}
```

### Application Task

> Logs lux level and proximity data

```c
void application_task ( void )
{
    uint8_t write_buffer[ 2 ];
    uint8_t read_buffer[ 1 ] ;
    float lux_level;
    uint16_t proximity;
    uint8_t als_valid;
    uint8_t proximity_valid;

    proximity7_generic_read( &proximity7, PROXIMITY7_STATUS | PROXIMITY7_REPEATED_BYTE, &read_buffer[ 0 ], 1 );
    
    als_valid = read_buffer[ 0 ] & PROXIMITY7_ALS_VALID_MASK;
    proximity_valid = read_buffer[ 0 ] & PROXIMITY7_PROXIMITY_VALID_MASK;
    
    if ( ( als_valid != 0 ) && ( proximity_valid != 0 ) )
    {
        log_printf( &logger, " " );

        lux_level = proximity7_get_lux_level( &proximity7 );
        log_printf( &logger, "> > > Lux level   : %f lx\r\n", lux_level );
    
        proximity = proximity7_get_proximity_data( &proximity7 );
        log_printf( &logger, "> > > Proximity   : %d\r\n", proximity );

        write_buffer[ 0 ] = PROXIMITY7_SPECIAL_FUNCTION | PROXIMITY7_PROXIMITY_AND_ALS_INT_PIN_CLEAR;
        proximity7_generic_write( &proximity7, PROXIMITY7_SPECIAL_FUNCTION | PROXIMITY7_PROXIMITY_AND_ALS_INT_PIN_CLEAR, &write_buffer[ 0 ], 1 );
    }
    
    Delay_ms ( 300 );
}
```

### Note

> - When setting LED drive strength please note that if "proximity drive level - PDL" bit in "configuration register" is set to 1, LED drive current values are reduced by 9.
  - When setting wait time note that if "wait long - WLONG" bit is set to 1, time is 12x longer. Therefore if WLONG == 1 set time between 33ms and 8386.56ms.
  - When setting ALS gain note that if "ALS gain level - AGL" bit is set to 1, ALS gains are scaled by 0.16, otherwise, they are scaled by 1.

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
