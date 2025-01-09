
---
# SHT AN Click

> [SHT AN Click](https://www.mikroe.com/?pid_product=MIKROE-3984) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3984&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of SHT AN Click to measure temperature and humidity.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ShtAn

### Example Key Functions

- `shtan_cfg_setup` Config Object Initialization function. 
```c
void shtan_cfg_setup ( shtan_cfg_t *cfg );
``` 
 
- `shtan_init` Initialization function. 
```c
err_t shtan_init ( shtan_t *ctx, shtan_cfg_t *cfg );
```

- `shtan_default_cfg` Click Default Configuration function. 
```c
void shtan_default_cfg ( shtan_t *ctx );
```

- Function sets signal output ADC mode 
- of the SHT3x-ARP Humidity and Temperature Sensor IC on SHT
- `shtan_set_mode` ANClick. 
```c
void shtan_set_mode ( shtan_t *ctx, uint8_t adc_mode );
```
 
- Function hardware reset the SHT3x-ARP Humidity and Temperature Sensor IC
- on SHT AN Click by cleared to '0' state of the RST pin,
- `shtan_reset` wait the 100 ms, sets to '1' state of the RST pin. 
```c
void shtan_reset ( shtan_t *ctx );
```

### Application Init

> Initialization driver enables - GPIO, sw reset,
> initializes ADC, set ADC channel and sets ADC read mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    shtan_cfg_t cfg;

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

    shtan_cfg_setup( &cfg );
    SHTAN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    shtan_init( &shtan, &cfg );

    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "   SHT AN Click   \r\n" );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 100 );

    deg_cel[ 0 ] = 32;
    deg_cel[ 1 ] = 176;
    deg_cel[ 2 ] = 67;
    deg_cel[ 3 ] = 0;

    shtan_reset( &shtan );
    Delay_ms ( 1000 );
    shtan_set_mode( &shtan, SHTAN_SET_ADC_MODE_TEMP );
    adc_mode = SHTAN_SET_ADC_MODE_TEMP;
    log_printf( &logger, "  Temp. & Hum.   \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> This is a example which demonstrates the use of SHT AN Click board.
> Measured temperature and humidity ADC data and calculate temperature data to degrees Celsius [ �C ] and
> humidity data to percentarg [ % ].
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart for aproximetly every 1 sec.

```c
void application_task ( void )
{
   shtan_calculate_temperature( void );
   log_printf( &logger, "  Temp. : %.2f\r\n", temperature );
   shtan_calculate_humidity( void );
   log_printf( &logger, "  Hum.  : %.2f\r\n", humidity );
   log_printf( &logger, "--------------------------" );
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
