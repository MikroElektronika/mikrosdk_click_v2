
---
# IR Gesture Click

> [IR Gesture Click](https://www.mikroe.com/?pid_product=MIKROE-2086) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2086&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This Click enables contactless gesture recognition: 
> basic directional swipes (up, down, left or right).  

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IrGesture

### Example Key Functions

- `irgesture_cfg_setup` Config Object Initialization function. 
```c
void irgesture_cfg_setup ( irgesture_cfg_t *cfg );
``` 
 
- `irgesture_init` Initialization function. 
```c
err_t irgesture_init ( irgesture_t *ctx, irgesture_cfg_t *cfg );
```

- `irgesture_default_cfg` Click Default Configuration function. 
```c
void irgesture_default_cfg ( irgesture_t *ctx );
```

- `irgesture_enable_gesture_sensor` Function starts the gesture recognition engine on the APDS-9960 IC on IR Gesture Click. 
```c
void irgesture_enable_gesture_sensor ( irgesture_t *ctx );
```

- `irgesture_detect_gesture` Function processes a gesture event and returns best guessed position engine on IR Gesture Click. 
```c
uint8_t irgesture_detect_gesture ( irgesture_t *ctx );
```
 
- `compare_data ` Function compares input data and returns position of gesture. 
```c
static uint8_t compare_data  (  uint8_t value0, uint8_t value1, uint8_t value2, uint8_t value3  );
```

### Application Init

> Initialization driver enable's - I2C, set default configuration, enable geasture sensor and start write log. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    irgesture_cfg_t cfg;

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

    irgesture_cfg_setup( &cfg );
    IRGESTURE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irgesture_init( &irgesture, &cfg );
    irgesture_default_cfg( &irgesture );
}
```

### Application Task

> This is a example which demonstrates the use of IR Gesture Click board.
> IR Gesture Click detects gestures and sends the movement to terminal every 1 second.

```c
void application_task ( void )
{
    position = irgesture_detect_gesture( &irgesture );

    if ( position_old != position )
    {
        if ( position == IRGESTURE_FAR )
        {
            log_printf( &logger, "       F A R        \r\n" );
        }
        if ( position == IRGESTURE_RIGHT )
        {
            log_printf( &logger, "     R I G H T      \r\n" );
        }
        if ( position == IRGESTURE_LEFT )
        {
            log_printf( &logger, "      L E F T       \r\n" );
        }
        if ( position == IRGESTURE_UP )
        {
            log_printf( &logger, "        U P         \r\n" );
        }
        if ( position == IRGESTURE_DOWN )
        {
            log_printf( &logger, "      D O W N       \r\n" );
        }
        if ( position == IRGESTURE_NEAR )
        {
            log_printf( &logger, "      N E A R       \r\n" );
        }

        position_old = position;
        log_printf( &logger, "--------------------\r\n" );

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
