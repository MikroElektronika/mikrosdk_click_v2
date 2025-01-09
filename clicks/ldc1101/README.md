
---
# LDC 1101 Click

> [LDC 1101 Click](https://www.mikroe.com/?pid_product=MIKROE-3240) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3240&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : nov 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> Example demonstrates measurement of inductance change depending on the linear motion 
> of the metal object.
> Induction of the linear metal position depends on the type of metal and the configuration.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ldc1101

### Example Key Functions

- `ldc1101_cfg_setup` Config Object Initialization function. 
```c
void ldc1101_cfg_setup ( ldc1101_cfg_t *cfg );
``` 
 
- `ldc1101_init` Initialization function. 
```c
err_t ldc1101_init ( ldc1101_t *ctx, ldc1101_cfg_t *cfg );
```

- `ldc1101_default_cfg` Click Default Configuration function. 
```c
void ldc1101_default_cfg ( ldc1101_t *ctx );
```

- `ldc1101_get_rp_data` Functions for reads RP data. 
```c
uint16_t ldc1101_get_rp_data ( ldc1101_t *ctx );
```
 
- `ldc1101_get_l_data` Functions for reads L data. 
```c
uint16_t ldc1101_get_l_data ( ldc1101_t *ctx );
```

- `ldc1101_get_interrupt` Functions for get interrupt pin status. 
```c
uint8_t ldc1101_get_interrupt ( ldc1101_t *ctx );
```

### Application Init

> Initializes I2C module and sets CS pin as OUTPUT and PWM and INT pin sa INPUT.
> Driver intialization, standard configurations and start measurement.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ldc1101_cfg_t cfg;

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

    ldc1101_cfg_setup( &cfg );
    LDC1101_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ldc1101_init( &ldc1101, &cfg );

    log_printf( &logger, "     LDC1101 Click\r\n" );
    log_printf( &logger, "------------------------\r\n" );
    
    ldc1101_default_cfg ( &ldc1101 );
    Delay_ms ( 100 );
}
```

### Application Task

> Reads RP data and logs data to USBUART every 1 sec.

```c
void application_task ( void )
{
    uint16_t rp_data;
    
    rp_data = ldc1101_get_rp_data( &ldc1101 );
    log_printf( &logger, " Inductive Linear Position : %u\r\n", rp_data );
    
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
