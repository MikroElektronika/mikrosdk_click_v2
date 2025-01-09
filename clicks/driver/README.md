
---
# Driver Click

> [Driver Click](https://www.mikroe.com/?pid_product=MIKROE-3109) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3109&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application offering a nine-pole spring terminal that can be used to implement and realize a wide range of different applications 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Driver

### Example Key Functions

- `driver_cfg_setup` Config Object Initialization function. 
```c
void driver_cfg_setup ( driver_cfg_t *cfg );
``` 
 
- `driver_init` Initialization function. 
```c
err_t driver_init ( driver_t *ctx, driver_cfg_t *cfg );
```

- `driver_set_in1` IN1 Set function. 
```c
void driver_set_in1 ( driver_t *ctx, uint8_t state );
```
 
- `driver_set_in2` IN2 Set function. 
```c
void driver_set_in2 ( driver_t *ctx, uint8_t state );
```

- `driver_set_in3` IN3 Set function. 
```c
void driver_set_in3 ( driver_t *ctx, uint8_t state );
```

### Application Init


> Initializes GPIO driver and selects which inputs will be set in operation.
   Bits from 0 to 6 (selectIN) select inputs from IN1 to IN7, respectively.
 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    driver_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    driver_cfg_setup( &cfg );
    DRIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    driver_init( &driver, &cfg );
}
```

### Application Task

> Performs cycles in which selected inputs will be turned on for pulseWidth
   delay time one by one. When one input is turned on, it will be turned off after desired delay time before the next input be turned on.

```c
void application_task ( void )
{
    uint8_t select_in;
    uint8_t temp;
    uint8_t count;

    select_in = 0x7F;
    temp = 1;
    
    for (count = 0; count < 7; count++)
    {
        switch ( select_in & temp )
        {
            case 0x01 :
            {
                driver_set_in1( &driver, ENABLE_IN );
                log_printf( &logger, "OUT1 enabled\r\n" );
                Delay_ms ( PULSE_WIDTH );
                driver_set_in1( &driver, DISABLE_IN );
                log_printf( &logger, "OUT1 disabled\r\n" );
                break;
            }
            case 0x02 :
            {
                driver_set_in2( &driver, ENABLE_IN );
                log_printf( &logger, "OUT2 enabled\r\n" );
                Delay_ms ( PULSE_WIDTH );
                driver_set_in2( &driver, DISABLE_IN );
                log_printf( &logger, "OUT2 disabled\r\n" );
                break;
            }
            case 0x04 :
            {
                driver_set_in3( &driver, ENABLE_IN );
                log_printf( &logger, "OUT3 enabled\r\n" );
                Delay_ms ( PULSE_WIDTH );
                driver_set_in3( &driver, DISABLE_IN );
                log_printf( &logger, "OUT3 disabled\r\n" );
                break;
            }
            case 0x08 :
            {
                driver_set_in4( &driver, ENABLE_IN );
                log_printf( &logger, "OUT4 enabled\r\n" );
                Delay_ms ( PULSE_WIDTH );
                driver_set_in4( &driver, DISABLE_IN );
                log_printf( &logger, "OUT4 disabled\r\n" );
                break;
            }
            case 0x10 :
            {
                driver_set_in5( &driver, ENABLE_IN );
                log_printf( &logger, "OUT5 enabled\r\n" );
                Delay_ms ( PULSE_WIDTH );
                driver_set_in5( &driver, DISABLE_IN );
                log_printf( &logger, "OUT5 disabled\r\n" );
                break;
            }
            case 0x20 :
            {
                driver_set_in6( &driver, ENABLE_IN );
                log_printf( &logger, "OUT6 enabled\r\n" );
                Delay_ms ( PULSE_WIDTH );
                driver_set_in6( &driver, DISABLE_IN );
                log_printf( &logger, "OUT6 disabled\r\n" );
                break;
            }
            case 0x40 :
            {
                driver_set_in7( &driver, ENABLE_IN );
                log_printf( &logger, "OUT7 enabled\r\n" );
                Delay_ms ( PULSE_WIDTH );
                driver_set_in7( &driver, DISABLE_IN );
                log_printf( &logger, "OUT7 disabled\r\n" );
                break;
            }
            default :
            {
                break;
            }
        }
        log_printf( &logger, "----------------------\r\n" );
        temp <<= 1;
        
        Delay_ms ( 1000 );
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
