
---
# Proximity 8 Click

> [Proximity 8 Click](https://www.mikroe.com/?pid_product=MIKROE-3439) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3439&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application enables usage of the proximity sensor

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity8

### Example Key Functions

- `proximity8_cfg_setup` Config Object Initialization function. 
```c
void proximity8_cfg_setup ( proximity8_cfg_t *cfg );
``` 
 
- `proximity8_init` Initialization function. 
```c
err_t proximity8_init ( proximity8_t *ctx, proximity8_cfg_t *cfg );
```

- `proximity8_default_cfg` Click Default Configuration function. 
```c
void proximity8_default_cfg ( proximity8_t *ctx );
```

- `proximity8_generic_read` This function reads data from the desired register. 
```c
void proximity8_generic_read ( proximity8_t *ctx, uint8_t reg, uint8_t *data_buf );
```
 
- `proximity8_generic_write` This function writes data to the desired register. 
```c
void proximity8_generic_write ( proximity8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

- `proximity8_get_interrupt_state` This function returns Interrupt state. 
```c
uint8_t proximity8_get_interrupt_state ( proximity8_t *ctx );
```

### Application Init

> Initialization Driver init, test comunication and configuration chip for measurement
 
```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity8_cfg_t cfg;
    uint16_t tmp;
    uint16_t w_temp;

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

    proximity8_cfg_setup( &cfg );
    PROXIMITY8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity8_init( &proximity8, &cfg );

    //Test Communication
    
    proximity8_generic_read( &proximity8, PROXIMITY8_REG_DEVICE_ID, &tmp );

    if( tmp == PROXIMITY8_DEVICE_ID )
    {
        log_printf( &logger, "---- Comunication OK!!! ----\r\n" );
    }
    else
    {
        log_printf( &logger, "---- Comunication ERROR!!! ----\r\n" );
        while( 1 );
    }

    proximity8_default_cfg( &proximity8 );

    log_printf( &logger, "---- Start measurement ----\r\n" );
}
```

### Application Task

> Reads Proximity data and this data logs to the USBUART every 1500ms.

```c
void application_task ( void )
{
    //  Task implementation.

   uint16_t proximity;
   
   proximity8_generic_read( &proximity8, PROXIMITY8_REG_PROX_DATA, &proximity );
   proximity = ( proximity & 0x7FFF );

   log_printf( &logger, " Proximity data: %d\r\n", proximity );
   
   log_printf( &logger, "-------------------------\r\n" );
   Delay_ms ( 1000 );
   Delay_ms ( 500 );
}
```

### Note

> The reading value and proximity of the data depend on the configuration.

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
