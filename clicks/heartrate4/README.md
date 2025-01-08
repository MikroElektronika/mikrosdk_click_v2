
---
# Heart rate 4 Click

> [Heart rate 4 Click](https://www.mikroe.com/?pid_product=MIKROE-2510) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2510&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Heart rate 4 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate4

### Example Key Functions

- `heartrate4_cfg_setup` Config Object Initialization function. 
```c
void heartrate4_cfg_setup ( heartrate4_cfg_t *cfg );
``` 
 
- `heartrate4_init` Initialization function. 
```c
err_t heartrate4_init ( heartrate4_t *ctx, heartrate4_cfg_t *cfg );
```

- `heartrate4_default_cfg` Click Default Configuration function. 
```c
void heartrate4_default_cfg ( heartrate4_t *ctx );
```

- `heartrate4_get_intrrupt` Function is used to read desired interrupt specified by flag. 
```c
uint8_t heartrate4_get_intrrupt ( heartrate4_t *ctx, uint8_t flag );
```
 
- `heartrate4_get_red_val` Function is used to read the oldest RED value. 
```c
uint32_t heartrate4_get_red_val ( heartrate4_t *ctx );
```

- `heartrate4_enable_slot` Function is used to determine which LED is active in each time slot. 
```c
void heartrate4_enable_slot ( heartrate4_t *ctx, uint8_t slot_num, uint8_t dev );
```

### Application Init

> Initalizes I2C driver, applies default settings, and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate4_cfg_t cfg;

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

    heartrate4_cfg_setup( &cfg );
    HEARTRATE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate4_init( &heartrate4, &cfg );

    Delay_ms ( 100 );
    heartrate4_default_cfg( &heartrate4 );
    Delay_ms ( 100 );
}
```

### Application Task

> Reads data from Red diode and displays the results on USB UART if the measured data
> is above defined threshold, otherwise, it displays desired message on the terminal.

```c

void application_task ( void )
{
    if ( heartrate4_get_intrrupt( &heartrate4, 1 ) & 0x40 )
    {
        red_samp = heartrate4_get_red_val( &heartrate4 );
        counter++;
        
        // If sample pulse amplitude is not under threshold value 0x8000
        if ( red_samp > 0x8000 )
        {
            log_printf( &logger, "%lu\r\n", red_samp );
            Delay_ms ( 1 );
            counter = 200;
        }
        else if ( counter > 200 )
        {
            log_printf( &logger, "Place Finger On Sensor\r\n" );
            Delay_ms ( 100 );
            counter = 0;
        }
    }
}
```

### Note
> <pre>
>     MCU              : STM32F107VCT6
>     Dev. Board       : Fusion for ARM v8
> </pre> 

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
