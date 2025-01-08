
---
# Analog Key Click

> [Analog Key Click](https://www.mikroe.com/?pid_product=MIKROE-3409) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3409&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : ADC type

# Software Support

## Example Description

> This example logs which button is pressed.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AnalogKey

### Example Key Functions

- `analogkey_cfg_setup` Config Object Initialization function. 
```c
void analogkey_cfg_setup ( analogkey_cfg_t *cfg );
``` 
 
- `analogkey_init` Initialization function. 
```c
err_t analogkey_init ( analogkey_t *ctx, analogkey_cfg_t *cfg );
```

- `analogkey_get_key` This function returns which button is pressed. 
```c
uint8_t analogkey_get_key ( analogkey_t* ctx, uint16_t adc_value );
```
 
- `analogkey_set_resolution` This function sets the resolution. 
```c
void analogkey_set_resolution ( analogkey_t* ctx, uint8_t resolution );
```

### Application Init

> Initializes driver.


```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    analogkey_cfg_t cfg;

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

    analogkey_cfg_setup( &cfg );
    ANALOGKEY_MAP_MIKROBUS( cfg, MIKROBUS_1 );

    analogkey_set_resolution( &analogkey, ANALOGKEY_ADC_RESOLUTION_12bit );
    
    analogkey_init( &analogkey, &cfg );
    Delay_ms ( 100 );

    log_printf(&logger, " Press the button :D\r\n ");

}
```

### Application Task

> Reads ADC value and detects which button is pressed based on that value.

```c
void application_task ( void )
{
    float an_voltage = 0;
    analogkey_key_id_t key;
    float an_average = 0;
    
    an_voltage = analogkey_read_voltage( &analogkey );
    
    if ( an_voltage > 0.2 )
    {
        an_average += an_voltage / ANALOGKEY_N_SAMPLES;
        for ( uint8_t cnt = 0; cnt < ANALOGKEY_N_SAMPLES - 1; cnt++ )
        {
            an_voltage = analogkey_read_voltage( &analogkey );
        
            an_average += an_voltage / ANALOGKEY_N_SAMPLES;
        }
    }
    
    if ( ( key = analogkey_get_key( &analogkey, an_average ) ) != ANALOGKEY_TOUCH_KEY_NONE )
    {
        log_printf( &logger, " T%u is pressed.\r\n", (uint16_t)key );
        
        while ( analogkey_read_voltage( &analogkey ) > 0.2 ) {
             Delay_ms ( 1 );   
        }
    
        log_printf( &logger, " T%u is released.\r\n", (uint16_t)key );
        Delay_ms ( 10 );
    }
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
