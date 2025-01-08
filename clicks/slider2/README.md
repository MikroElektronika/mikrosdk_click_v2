
---
# Slider 2 Click

> [Slider 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3301) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3301&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : ADC type

# Software Support

## Example Description

> This Click utilizes potentiometer with long travel distance of the wiper 
> witch allows more accurate movements and combined with the high-quality 
> manufacturing process it allows to dial-in the desired voltage with ease.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Slider2

### Example Key Functions

- `slider2_cfg_setup` Config Object Initialization function. 
```c
void slider2_cfg_setup ( slider2_cfg_t *cfg );
``` 
 
- `slider2_init` Initialization function. 
```c
err_t slider2_init ( slider2_t *ctx, slider2_cfg_t *cfg );
```

- `slider2_default_cfg` Click Default Configuration function. 
```c
void slider2_default_cfg ( slider2_t *ctx );
```

- `slider2_enable` This function sets desired state to EN pin. 
```c
void slider2_enable ( slider2_t *ctx, uint8_t state );
```
 
- `slider2_set_reference` This function sets desired reference to RSL pin. 
```c
void slider2_set_reference ( slider2_t *ctx, uint8_t ref );
```

### Application Init

> Initialization driver init and ADC init.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    slider2_cfg_t cfg;

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

    slider2_cfg_setup( &cfg );
    SLIDER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    slider2_init( &slider2, &cfg );
    slider2_default_cfg( &slider2);

}
```

### Application Task

> Read Slider data value and this data logs to terminal every 500ms.

```c
void application_task ( void )
{
    slider2_data_t tmp;
        
    tmp = slider2_generic_read ( &slider2 );
    log_printf( &logger, "** ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );
    
    Delay_ms ( 500 );

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
