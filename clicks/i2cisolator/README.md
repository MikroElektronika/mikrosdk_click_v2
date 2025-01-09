
---
# I2C isolator Click

> [I2C isolator Click](https://www.mikroe.com/?pid_product=MIKROE-1878) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1878&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> 
> This is an example which demonstrates the use of I2C Isolator Click board.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.I2Cisolator

### Example Key Functions

- `i2cisolator_cfg_setup` Config Object Initialization function. 
```c
void i2cisolator_cfg_setup ( i2cisolator_cfg_t *cfg );
``` 
 
- `i2cisolator_init` Initialization function. 
```c
err_t i2cisolator_init ( i2cisolator_t *ctx, i2cisolator_cfg_t *cfg );
```

- `i2cisolator_generic_write` Generic write function. 
```c
void i2cisolator_generic_write ( i2cisolator_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```
 
- `i2cisolator_generic_read` Generic read function. 
```c
void i2cisolator_generic_read ( i2cisolator_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

### Application Init

>
> Initialization driver enables - I2C,
> sets configuration of TMP007 sensor on IrThermo 2 Click and start to write log.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cisolator_cfg_t cfg;
    uint8_t tmp;

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

    i2cisolator_cfg_setup( &cfg );
    I2CISOLATOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cisolator_init( &i2cisolator, &cfg );

    log_printf( &logger, "    Driver  Initialized\r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
    
    tmp =    I2CISOLATOR_IRTHERMO2_CFG_MODEON |
                I2CISOLATOR_IRTHERMO2_CFG_ALERTEN | 
                I2CISOLATOR_IRTHERMO2_CFG_TRANSC | 
                I2CISOLATOR_IRTHERMO2_CFG_16SAMPLE;
    i2cisolator_generic_write( &i2cisolator, I2CISOLATOR_IRTHERMO2_CONFIGURATION, &tmp, 1 );

    tmp =    I2CISOLATOR_IRTHERMO2_STAT_ALERTEN | 
                I2CISOLATOR_IRTHERMO2_STAT_CRTEN;
    i2cisolator_generic_write( &i2cisolator, I2CISOLATOR_IRTHERMO2_STATUS_MASK_AND_ENABLE, &tmp, 1 );    
    
    log_printf( &logger, "       Configuration\r\n" );
    log_printf( &logger, "      IrThermo 2 Click\r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

>
> In this example we use IrThermo 2 Click, measures the temperature with,
> and calculate the temperature in degrees Celsius [ C ].
> Results are being sent to the USART Terminal where you can track their changes.
> All data logs on usb uart each second.
> 

```c
void application_task ( void )
{
    i2cisolator_get_temperature( );   
    
    log_printf( &logger, " Temperature : %0.2f C\r\n", temperature );
    log_printf( &logger, "---------------------------\r\n" );
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
