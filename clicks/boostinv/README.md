
---
# Boost-INV Click

> [Boost-INV Click](https://www.mikroe.com/?pid_product=MIKROE-3124) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3124&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka FIlipovic
- **Date**          : Nov 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> Changes the positive and negative output voltage. Input Voltage 3.3V.
> Positive output voltage goes from 3200mV, 7750mV, 12000mV and 7750mV.
> Negative output voltage goes from -1450mV, -6700mV, -11050mV and -6700mV.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BoostInv

### Example Key Functions

- `boostinv_cfg_setup` Config Object Initialization function. 
```c
void boostinv_cfg_setup ( boostinv_cfg_t *cfg );
``` 
 
- `boostinv_init` Initialization function. 
```c
err_t boostinv_init ( boostinv_t *ctx, boostinv_cfg_t *cfg );
```

- `boostinv_default_cfg` Click Default Configuration function. 
```c
void boostinv_default_cfg ( boostinv_t *ctx );
```

- `boostinv_enable` Functions for enable chip. 
```c
void boostinv_enable ( boostinv_t *ctx );
```
 
- `boostinv_set_positive_voltage` Functions for set positive output voltage. 
```c
void boostinv_set_positive_voltage( boostinv_t *ctx, uint16_t voltage );
```

- `boostinv_set_negative_voltage` Functions for set negative output voltage. 
```c
void boostinv_set_negative_voltage( boostinv_t *ctx, int16_t voltage );
```

### Application Init

> Initializes I2C module and sets EN ( RST ) pin as output.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    boostinv_cfg_t cfg;

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

    boostinv_cfg_setup( &cfg );
    BOOSTINV_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boostinv_init( &boostinv, &cfg );
    
    boostinv_default_cfg ( &boostinv );
    log_printf( &logger, "     Boost INV Click\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> Changes the positive and negative output voltage every 5 sec.

```c
void application_task ( void )
{
    //  Task implementation.
    
    // Sets Positive output voltage
    
    log_printf( &logger, " Positive output voltage \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "          3200 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_positive_voltage( &boostinv, BOOSTINV_VOLTAGE_POSITIVE_3200_mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "          7750 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_positive_voltage( &boostinv, BOOSTINV_VOLTAGE_POSITIVE_7750_mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "        12000 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_positive_voltage( &boostinv, BOOSTINV_VOLTAGE_POSITIVE_12000_mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "         7750 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_positive_voltage( &boostinv, BOOSTINV_VOLTAGE_POSITIVE_7750_mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // Sets Negative output voltage
    
    log_printf( &logger, " Negative output voltage \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "        -1450 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_negative_voltage( &boostinv, BOOSTINV_VOLTAGE_NEGATIVE_1450_mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "       - 6700 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_negative_voltage( &boostinv, BOOSTINV_VOLTAGE_NEGATIVE_6700_mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "       - 11050 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_negative_voltage( &boostinv, BOOSTINV_VOLTAGE_NEGATIVE_11050_mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "       - 6700 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_negative_voltage( &boostinv, BOOSTINV_VOLTAGE_NEGATIVE_6700_mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
