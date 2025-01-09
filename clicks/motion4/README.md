
---
# Motion 4 Click

> [Motion 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4078) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4078&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Motion 4 Click boards.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Motion4

### Example Key Functions

- `motion4_cfg_setup` Config Object Initialization function.
```c
void motion4_cfg_setup ( motion4_cfg_t *cfg );
```

- `motion4_init` Initialization function.
```c
err_t motion4_init ( motion4_t *ctx, motion4_cfg_t *cfg );
```

- `motion4_enable` This function enables/disables motion sensor by setting EN pin state.
```c
void motion4_enable ( motion4_t *ctx, uint8_t state );
```

- `motion4_detect_state` This function returns INT pin state.
```c
uint8_t motion4_detect_state ( motion4_t *ctx );
```

### Application Init

> Initializes the driver and enables the motion sensor.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    motion4_cfg_t motion4_cfg;  /**< Click config object. */

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

    motion4_cfg_setup( &motion4_cfg );
    MOTION4_MAP_MIKROBUS( motion4_cfg, MIKROBUS_1 );
    if ( motion4_init( &motion4, &motion4_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
       
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    motion4_enable( &motion4, MOTION4_MODULE_ENABLE );
    Delay_ms ( 100 );
    log_printf( &logger, "The sensor is ready.\r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}
```

### Application Task

> It checks if the sensor has detected movement and therefore displays the desired message on the USB UART.

```c
void application_task ( void ) 
{
    uint8_t int_status;

    int_status = motion4_detect_state( &motion4 );

    if ( int_status == MOTION4_DETECT_OBJECT ) {
        
        log_printf( &logger, "Motion detected!\r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        while ( int_status == MOTION4_DETECT_OBJECT ) {
           
            int_status = motion4_detect_state( &motion4 );
        }
        log_printf( &logger, "The sensor is ready.\r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        Delay_ms ( 100 );
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
