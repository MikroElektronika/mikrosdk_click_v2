
---
# 2x2 key Click

> [2x2 key Click](https://www.mikroe.com/?pid_product=MIKROE-2152) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2152&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> 
> This example code demonstrates the usage of 2X2 Key Click board.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.2x2key

### Example Key Functions

- `c2x2key_cfg_setup` Config Object Initialization function. 
```c
void c2x2key_cfg_setup ( c2x2key_cfg_t *cfg );
``` 
 
- `c2x2key_init` Initialization function. 
```c
err_t c2x2key_init ( c2x2key_t *ctx, c2x2key_cfg_t *cfg );
```

- `c2x2key_default_cfg` Click Default Configuration function. 
```c
void c2x2key_default_cfg ( c2x2key_t *ctx );
```

- `c2x2key_t1_state` This function gets state of AN pin on 2X2_Key Click board. 
```c
uint8_t c2x2key_t1_state ( c2x2key_t *ctx );
```
 
- `c2x2key_t2_state` This function gets state of RST pin on 2X2_Key Click board. 
```c
uint8_t c2x2key_t2_state ( c2x2key_t *ctx );
```

- `c2x2key_t3_state` This function gets state of CS pin on 2X2_Key Click board. 
```c
uint8_t c2x2key_t3_state ( c2x2key_t *ctx );
```

- `c2x2key_t4_state` This function gets state of PWM pin on 2X2_Key Click board. 
```c
uint8_t c2x2key_t4_state ( c2x2key_t *ctx );
```

### Application Init

>
> Application Init performs Logger and Click initialization.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c2x2key_cfg_t cfg;

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
    log_printf( &logger, "-- Application  Init --\r\n" );
    Delay_ms ( 1000 );

    //  Click initialization.

    c2x2key_cfg_setup( &cfg );
    C2X2KEY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c2x2key_init( &c2x2key, &cfg );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "     2X2 key Click     \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "    System is ready    \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

>
> Application Task detects whether any of the keys is pressed,
> and results are being sent to the UART Terminal where you can track changes.
> 

```c
void application_task ( void )
{
   t1_state = c2x2key_t1_state( &c2x2key );
   
   if ( t1_state == 1 && t1_state_old == 0 )
    {
        log_printf( &logger, "-----------------------\r\n" );
        log_printf( &logger, "     Key 1 pressed     \r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        t1_state_old = 1;
    }
    
    if ( t1_state == 0 && t1_state_old == 1 )
    {
        t1_state_old = 0;
    }
    
    t2_state = c2x2key_t2_state( &c2x2key );
   
   if ( t2_state == 1 && t2_state_old == 0 )
    {
        log_printf( &logger, "-----------------------\r\n" );
        log_printf( &logger, "     Key 2 pressed     \r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        t2_state_old = 1;
    }
    
    if ( t2_state == 0 && t2_state_old == 1 )
    {
        t2_state_old = 0;
    }
    
    t3_state = c2x2key_t3_state( &c2x2key );
   
   if ( t3_state == 1 && t3_state_old == 0 )
    {
        log_printf( &logger, "-----------------------\r\n" );
        log_printf( &logger, "     Key 3 pressed     \r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        t3_state_old = 1;
    }
    
    if ( t3_state == 0 && t3_state_old == 1 )
    {
        t3_state_old = 0;
    }
    
    t4_state = c2x2key_t4_state( &c2x2key );
   
   if ( t4_state == 1 && t4_state_old == 0 )
    {
        log_printf( &logger, "-----------------------\r\n" );
        log_printf( &logger, "     Key 4 pressed     \r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        t4_state_old = 1;
    }
    
    if ( t4_state == 0 && t4_state_old == 1 )
    {
        t4_state_old = 0;
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
