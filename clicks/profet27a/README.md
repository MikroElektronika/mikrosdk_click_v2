
---
# PROFET 2 7A Click

> [PROFET 2 7A Click](https://www.mikroe.com/?pid_product=MIKROE-4819) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4819&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : ADC type

# Software Support

## Example Description

> This example showcases the ability of the PROFET 2 7A Click board.
It configures Host MCU for communication and then enables 
and disables output channel. Besides that, it reads the voltage 
of IS pin and calculates current on output for the channel 0.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PROFET27A

### Example Key Functions

- `profet27a_cfg_setup` Config Object Initialization function.
```c
void profet27a_cfg_setup ( profet27a_cfg_t *cfg );
```

- `profet27a_init` Initialization function.
```c
err_t profet27a_init ( profet27a_t *ctx, profet27a_cfg_t *cfg );
```

- `profet27a_default_cfg` Click Default Configuration function.
```c
void profet27a_default_cfg ( profet27a_t *ctx );
```

- `profet27a_set_mode` Set mode device mode for specific channel channel.
```c
err_t profet27a_set_mode ( profet27a_t *ctx, profet27a_channel_t channel, uint8_t mode );
```

- `profet27a_read_an_pin_voltage` Read AN pin voltage level function.
```c
err_t profet27a_read_an_pin_voltage ( profet27a_t *ctx, float *data_out );
```

- `profet27a_set_den` Set diagnostic enable pin state.
```c
void profet27a_set_den ( profet27a_t *ctx, uint8_t state );
```

### Application Init

> Initialization of the communication modules(ADC and UART) 
and additional pins for controlling the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    profet27a_cfg_t profet27a_cfg;  /**< Click config object. */

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
    profet27a_cfg_setup( &profet27a_cfg );
    PROFET27A_MAP_MIKROBUS( profet27a_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == profet27a_init( &profet27a, &profet27a_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    profet27a_default_cfg ( &profet27a );
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
}
```

### Application Task

> On every iteration of the task device switches between 
DIAGNOSTIC and OFF mode while it reads the voltage of IS pin 
and with that calculates current on output for channel 0.

```c
void application_task ( void ) 
{
    static uint8_t mode = PROFET27A_DIAGNOSTIC_ON;
    float profet27a_an_voltage = 0;
    
    err_t error_val = profet27a_set_mode( &profet27a, PROFET27A_CHANNEL_0, mode );
    
    if ( error_val )
    {
        log_error( &logger, "Channe/Mode" );
    }
    
    if ( PROFET27A_DIAGNOSTIC_ON == profet27a.mode )
    {
        mode = PROFET27A_MODE_OFF;
        log_printf( &logger, " > Output ON Channel %u in diagnostic mode\r\n", ( uint16_t )profet27a.channel );
        Delay_ms ( 1000 );
    }
    else
    {
        mode = PROFET27A_DIAGNOSTIC_ON;
        log_printf( &logger, " > Output OFF\r\n" );
    }

    if ( profet27a_read_an_pin_voltage ( &profet27a, &profet27a_an_voltage ) != ADC_ERROR )
    {
        log_printf( &logger, " > IS Voltage \t~ %.3f[V]\r\n", profet27a_an_voltage );
        
        float current = profet27a_an_voltage * profet27a.kilis / profet27a.rsens;
        log_printf( &logger, " > OUT Current \t~ %.3f[A]\r\n", current );
    }  
    
    log_printf( &logger, "*******************************************\r\n" );
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Formula for calculating current on load: 
I_load = voltage(IS) x kILIS(1800) / rsens(1.2 kΩ)

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
