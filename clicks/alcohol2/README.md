
---
# Alcohol 2 Click

> [Alcohol 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3097) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3097&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> The demo application gets Alcohol data and logs data to USBUART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Alcohol2

### Example Key Functions

- `alcohol2_cfg_setup` Config Object Initialization function. 
```c
void alcohol2_cfg_setup ( alcohol2_cfg_t *cfg );
``` 
 
- `alcohol2_init` Initialization function. 
```c
err_t alcohol2_init ( alcohol2_t *ctx, alcohol2_cfg_t *cfg );
```

- `alcohol2_default_cfg` Click Default Configuration function. 
```c
void alcohol2_default_cfg ( alcohol2_t *ctx );
```

- `alcohol2_write_byte` This function writes one byte to the register. 
```c
void alcohol2_write_byte ( alcohol2_t *ctx, uint8_t reg, uint8_t w_data );
```
 
- `alcohol2_read_byte` This function reads one byte from the register. 
```c
uint8_t alcohol2_read_byte ( alcohol2_t *ctx, uint8_t reg );
```

- `alcohol2_read_alcohol` This function reads Alcohol data. 
```c
uint16_t alcohol2_read_alcohol ( alcohol2_t *ctx );
```

### Application Init

> Initializes device configuration.

```c
oid application_init ( void )
{
    log_cfg_t log_cfg;
    alcohol2_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    ALCOHOL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    alcohol2_init( &alcohol2, &cfg );

    alcohol2_write_byte( &alcohol2, ALCOHOL2_MODECN_REG, ALCOHOL2_DEEP_SLEEP_MODE );
    alcohol2_write_byte( &alcohol2, ALCOHOL2_LOCK_REG,   ALCOHOL2_WRITE_MODE );
    alcohol2_write_byte( &alcohol2, ALCOHOL2_TIACN_REG, ALCOHOL2_EXT_TIA_RES | ALCOHOL2_100_OHM_LOAD_RES );
    alcohol2_write_byte( &alcohol2, ALCOHOL2_REFCN_REG, ALCOHOL2_VREF_INT | ALCOHOL2_50_PERCENTS_INT_ZERO | ALCOHOL2_BIAS_POL_NEGATIVE | ALCOHOL2_0_PERCENTS_BIAS );

    log_printf( &logger, "Alcohol 2 is initialized\r\n");
    Delay_ms ( 300 );
}
```

### Application Task

> Gets Alcohol (C2H5OH) data and logs data to USBUART every 500ms. 

```c
void application_task ( void )
{
    alcohol_value = alcohol2_read_alcohol( &alcohol2 );
    log_printf( &logger, "Alcohol value : %f \r\n",alcohol_value );
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
