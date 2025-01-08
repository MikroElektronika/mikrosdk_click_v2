
---
# Proximity 9 Click

> [Proximity 9 Click](https://www.mikroe.com/?pid_product=MIKROE-3465) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3465&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application is proximity sensing (PS) and ambient light sensing (ALS) device.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity9

### Example Key Functions

- `proximity9_cfg_setup` Config Object Initialization function. 
```c
void proximity9_cfg_setup ( proximity9_cfg_t *cfg );
``` 
 
- `proximity9_init` Initialization function. 
```c
err_t proximity9_init ( proximity9_t *ctx, proximity9_cfg_t *cfg );
```

- `proximity9_default_cfg` Click Default Configuration function. 
```c
void proximity9_default_cfg ( proximity9_t *ctx );
```

- `proximity9_check_int_pin` INT Pin Check function. 
```c
uint8_t proximity9_check_int_pin ( proximity9_t *ctx );
```
 
- `proximity9_check_int_flag` INT Flag Check function. 
```c
uint8_t proximity9_check_int_flag ( proximity9_t *ctx, uint8_t bit_mask );
```

- `proximity9_get_als_lux` ALS Get function. 
```c
float proximity9_get_als_lux ( proximity9_t *ctx );
```

### Application Init

> Initializes I2C interface and performs a device configurations.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity9_cfg_t cfg;

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

    proximity9_cfg_setup( &cfg );
    PROXIMITY9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity9_init( &proximity9, &cfg );

    proximity9_default_cfg( &proximity9 );

    log_printf( &logger, "** Proximity 9 is initialized ** \r\n" );
    log_printf( &logger, "************************************ \r\n" );
    Delay_ms ( 300 );
}
```

### Application Task

> Performs a data reading and interrupt flag checking.
> Allows data and interrupt flags messages to be showed on the uart terminal.

```c
void application_task ( )
{
    uint8_t int_check;
    uint16_t prox_data;
    float als_data;
    uint8_t temp;

    als_data = proximity9_get_als_lux( &proximity9 );
    proximity9_read_register( &proximity9, PROXIMITY9_PS_DATA_REG, &prox_data );
    temp = PROXIMITY9_PS_IF_CLOSE_FLAG | PROXIMITY9_PS_IF_AWAY_FLAG;
    int_check = proximity9_check_int_flag( &proximity9, temp );
    
    log_printf( &logger, "** ALS: %.2f lux \r\n", als_data );
    log_printf( &logger, "** PROXIMITY: %d \r\n", prox_data );
    
    if ( int_check == PROXIMITY9_PS_IF_CLOSE_FLAG )
    {
        log_printf( &logger, "** Object is close! \r\n" );
        log_printf( &logger, "************************************ \r\n" );
        Delay_ms ( 200 );
    }
    if ( int_check == PROXIMITY9_PS_IF_AWAY_FLAG )
    {
        log_printf( &logger, "** Object is away!\r\n" );
        log_printf( &logger, "************************************ \r\n" );
        Delay_ms ( 200 );
    }
    if ( int_check == PROXIMITY9_INT_CLEARED )
    {
        log_printf( &logger, "************************************ \r\n" );
        Delay_ms ( 200 );
    }
}
```

### Note

> The ALS sensitivity depends on the ALS integration time setting.
> The longer integration time has higher sensitivity.
> The Proximity (PS) output data can be set to 12-bit or 16-bit resolution.

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
