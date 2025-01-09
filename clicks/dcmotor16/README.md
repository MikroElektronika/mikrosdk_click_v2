
---
# DC Motor 16 Click

> [DC Motor 16 Click](https://www.mikroe.com/?pid_product=MIKROE-4333) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4333&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example shows the capabilities of the DC Motor 16 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor16

### Example Key Functions

- `dcmotor16_cfg_setup` Config Object Initialization function.
```c
void dcmotor16_cfg_setup ( dcmotor16_cfg_t *cfg );
```

- `dcmotor16_init` Initialization function.
```c
err_t dcmotor16_init ( dcmotor16_t *ctx, dcmotor16_cfg_t *cfg );
```

- `dcmotor16_set_direction` Set motor direction.
```c
void dcmotor16_set_direction( dcmotor16_t *ctx, uint8_t dir );
```

- `dcmotor16_ctrl_vref` Control motor VRef (speed).
```c
void dcmotor16_ctrl_vref( dcmotor16_t *ctx, uint16_t value );
```

- `dcmotor16_stop` Motor stop.
```c
void dcmotor16_stop( dcmotor16_t *ctx );
```

### Application Init

> Initialization driver init.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor16_cfg_t dcmotor16_cfg;  /**< Click config object. */

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

    dcmotor16_cfg_setup( &dcmotor16_cfg );
    DCMOTOR16_MAP_MIKROBUS( dcmotor16_cfg, MIKROBUS_1 );
    err_t init_flag  = dcmotor16_init( &dcmotor16, &dcmotor16_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Start motor example with change in motor direction and speed.

```c
void application_task ( void ) 
{
    uint16_t cnt;
    
    log_printf( &logger, ">> Motor start with direction [FORWARD] <<\r\n" );
    dcmotor16_set_direction( &dcmotor16, DCMOTOR16_DIR_FORWARD );
    for( cnt = 0; cnt <= 0x0100; cnt+= 25 ) {
        dcmotor16_ctrl_vref( &dcmotor16, cnt );
        Delay_ms ( 250 );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">> Motor stop \r\n" );
    dcmotor16_stop( &dcmotor16 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">> Motor start with direction [BACKWARD] <<\r\n" );
    dcmotor16_set_direction( &dcmotor16, DCMOTOR16_DIR_BACKWARD );
    for( cnt = 0; cnt <= 0x0100; cnt+= 25 ) {
        dcmotor16_ctrl_vref( &dcmotor16, cnt );
        Delay_ms ( 250 );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">> Motor stop \r\n" );
    dcmotor16_stop( &dcmotor16 );
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
