
---
# Wheatstone Click

> [Wheatstone Click](https://www.mikroe.com/?pid_product=MIKROE-4124) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4124&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Wheatstone Click board by measuring the input resistance.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Wheatstone

### Example Key Functions

- `wheatstone_cfg_setup` Config Object Initialization function.
```c
void wheatstone_cfg_setup ( wheatstone_cfg_t *cfg ); 
```

- `wheatstone_init` Initialization function.
```c
err_t wheatstone_init ( wheatstone_t *ctx, wheatstone_cfg_t *cfg );
```

- `wheatstone_set_potentiometer` Set potentiometer ( 0 - 100k )
```c
void wheatstone_set_potentiometer ( wheatstone_t *ctx, uint8_t pot_value );
```

- `wheatstone_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t wheatstone_read_an_pin_voltage ( wheatstone_t *ctx, float *data_out );
```

### Application Init

> Initializes the driver and logger and sets the default potentiometer (gain) level.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    wheatstone_cfg_t cfg;

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
    wheatstone_cfg_setup( &cfg );
    WHEATSTONE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wheatstone_init( &wheatstone, &cfg );

    wheatstone_set_potentiometer ( &wheatstone, WHEATSTONE_POT_MAX );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the AN pin voltage and calculates the input resistance from it. All data are being displayed on the USB UART where you can track their changes.

```c
void application_task ( void )
{
    float an_pin_v = 0;
    float vout = 0;
    float r_kohm = 0;
    if ( WHEATSTONE_OK == wheatstone_read_an_pin_voltage ( &wheatstone, &an_pin_v ) ) 
    {
        vout = an_pin_v / wheatstone.gain;
        if ( 0 != vout )
        {
            r_kohm = ( WHEATSTONE_VCC_5V - 2 * vout ) / ( 4 * vout );
        }
        log_printf( &logger, " VCC     : %.3f V\r\n", WHEATSTONE_VCC_5V );
        log_printf( &logger, " GAIN    : %.3f\r\n", wheatstone.gain );
        log_printf( &logger, " AN_PIN  : %.3f V\r\n", an_pin_v );
        log_printf( &logger, " VOUT    : %.3f V\r\n", vout );
        log_printf( &logger, " R_INPUT : %.3f kOhm\r\n\n", r_kohm );
        Delay_ms ( 1000 );
    }
}
```

### Note

> The following formulas you may find useful:
> - AN_PIN(V) = ( ( 1kOhm + R_INPUT(kOhm) ) / ( 1kOhm + 2*R_INPUT(kOhm) ) - 1/2 ) * VCC(V) * GAIN
> - VOUT(V) = AN_PIN(V) / GAIN
> - R_INPUT(kOhm) = ( VCC(V) * GAIN - 2*AN_PIN(V) ) / ( 4*AN_PIN(V) )
> - R_INPUT(kOhm) = ( VCC(V) - 2*VOUT(V) ) / ( 4*VOUT(V) )

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
