
---
# AMR Current Click

> [AMR Current Click](https://www.mikroe.com/?pid_product=MIKROE-3812) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3812&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application integrated bi-directional analog output current sensors. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Amrcurrent

### Example Key Functions

- `amrcurrent_cfg_setup` Config Object Initialization function. 
```c
void amrcurrent_cfg_setup ( amrcurrent_cfg_t *cfg );
``` 
 
- `amrcurrent_init` Initialization function. 
```c
err_t amrcurrent_init ( amrcurrent_t *ctx, amrcurrent_cfg_t *cfg );
```

- `amrcurrent_default_cfg` Click Default Configuration function. 
```c
void amrcurrent_default_cfg ( amrcurrent_t *ctx );
```

- `amrcurrent_generic_write` This function writes data to the desired register. 
```c
void amrcurrent_generic_write ( amrcurrent_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```
 
- `amrcurrent_generic_read` This function reads data from the desired register. 
```c
void amrcurrent_generic_read ( amrcurrent_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

- `amrcurrent_read_value` This function read value. 
```c
uint16_t amrcurrent_read_value (  amrcurrent_t *ctx );
```

### Application Init

> Initializations driver init. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    amrcurrent_cfg_t cfg;

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

    amrcurrent_cfg_setup( &cfg );
    AMRCURRENT_MAP_MIKROBUS( cfg, MIKROBUS_POSITION_AMRCURRENT );
    amrcurrent_init( &amrcurrent, &cfg );
}

  
```

### Application Task

> Reading ADC data and converted current mA data from device and logs it to device. 

```c
void application_task ( void )
{
    //  Task implementation.

    read_adc_val = amrcurrent_read_value ( &amrcurrent );
    log_printf( &logger, " - ADC value: \r\n ", read_adc_val );
    
    Delay_ms ( 100 );

    read_curr_val = amrcurrent_get_current (  &amrcurrent );
    log_printf( &logger, " - Current value: \r\n ", read_curr_val );
    
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
