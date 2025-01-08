
---
# Charger 13 Click

> [Charger 13 Click](https://www.mikroe.com/?pid_product=MIKROE-3748) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3748&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This demo application charges the battery.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger13

### Example Key Functions

- `charger13_cfg_setup` Config Object Initialization function. 
```c
void charger13_cfg_setup ( charger13_cfg_t *cfg );
``` 
 
- `charger13_init` Initialization function. 
```c
err_t charger13_init ( charger13_t *ctx, charger13_cfg_t *cfg );
```

- `charger13_default_cfg` Click Default Configuration function. 
```c
void charger13_default_cfg ( charger13_t *ctx );
```

- `charger13_enable` This function enable battery charging by cleared to LOW state of the EN ( PWM ) pin of the Charger 13 Click board. 
```c
void charger13_enable ( charger13_t *ctx );
```
 
- `` This function disable battery charging by sets to HIGH state of the EN ( PWM ) pin of the Charger 13 Click board. 
```c
charger13_disable  ( charger13_t *ctx );
```

- `charger13_check` This function check if the battery is charging of the Charger 13 Click board. 
```c
uint8_t charger13_check ( charger13_t *ctx );
```

### Application Init

> Initialization device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    charger13_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    charger13_cfg_setup( &cfg );
    CHARGER13_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    charger13_init( &charger13, &cfg );

    Delay_100ms( );

    charger_flag = 2;
    enable_flag = 0;

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "      'E' : Enable       \r\n" );
    log_printf( &logger, "      'D' : Disable      \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "Charging Status : Disable\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_100ms( );
}
```

### Application Task

> This is an example which demonstrates the use of Charger 13 Click board.
> This example shows the automatic control of the Charger 13 Click,
> waits for valid user input and executes functions based on a set of valid commands
> and check the battery charge status.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart for approximately every 1 sec when the data value changes.

```c
void application_task ( void )
{
    if ( enable_flag == 0 )
    {
        enable_flag = 1;
        charger13_enable( &charger13 );
        log_printf( &logger, "Charging Status : Enabled\r\n" );
        log_printf( &logger, "-------------------------\r\n" );
    }
    else if ( enable_flag == 1 )
    {
        enable_flag = 0;
        charger13_disable( &charger13 );
        log_printf( &logger, "Charging Status : Disable\r\n" );
        log_printf( &logger, "-------------------------\r\n" );
    }
    status_flag = charger13_check( &charger13 );

    if ( status_flag != charger_flag )
    {   
        charger_flag = charger13_check( &charger13 );

        if ( charger_flag == 0 )
        {
            log_printf( &logger, "   Battery is charging   \r\n" );
            log_printf( &logger, "-------------------------\r\n" );
        }
        else
        {
            log_printf( &logger, " Battery does not charge \r\n" );
            log_printf( &logger, "-------------------------\r\n" );
        }
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
