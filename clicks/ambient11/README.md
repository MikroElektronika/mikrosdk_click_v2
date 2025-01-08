
---
# Ambient 11 Click

> [Ambient 11 Click](https://www.mikroe.com/?pid_product=MIKROE-3990) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3990&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description


> The devices resolution depends on settings applied.
>  User should consult the datasheet and choose resolution value 
>   that corresponds to the settings applied.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient11

### Example Key Functions

- `ambient11_cfg_setup` Config Object Initialization function. 
```c
void ambient11_cfg_setup ( ambient11_cfg_t *cfg );
``` 
 
- `ambient11_init` Initialization function. 
```c
err_t ambient11_init ( ambient11_t *ctx, ambient11_cfg_t *cfg );
```

- `ambient11_default_cfg` Click Default Configuration function. 
```c
void ambient11_default_cfg ( ambient11_t *ctx );
```

- `ambient11_generic_write` This function writes data to the desired register. 
```c
void ambient11_generic_write ( ambient11_t *ctx, uint8_t wr_cmd, uint16_t wr_data );
```
 
- `ambient11_generic_read` This function reads data from the desired register. 
```c
uint16_t ambient11_generic_read ( ambient11_t *ctx, uint8_t reg_addr );
```

- `ambient11_calc_illumination` Function is used to calculate ambiental illumination. 
```c
float ambient11_calc_illumination ( ambient11_t *ctx, float typical_res );
```

- `ambient11_check_int` Function checks interrupt occurence. 
```c
uint8_t ambient11_check_int ( ambient11_t *ctx );
```

### Application Init


> Initalizes I2C driver, applies low sensitiviti settings
>( GAIN = 0, DG = 0, SENS = 1 and IT = 100ms ) and makes an initial log.
 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient11_cfg_t cfg;

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

    ambient11_cfg_setup( &cfg );
    AMBIENT11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient11_init( &ambient11, &cfg );
    ambient11_default_cfg ( &ambient11 );
}
```

### Application Task


> This example shows the capabilities of the Ambient 11 Click by measuring
>  ambiental illumination and displaying calculated value via USART terminal in luxes.
 

```c
void application_task ( void )
{
    lx_val = ambient11_calc_illumination( &ambient11, resolution );
    log_printf( &logger, "Illumination : %.2f lx \r\n",lx_val );
    log_printf( &logger, "-------------------------\r\n" );
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
