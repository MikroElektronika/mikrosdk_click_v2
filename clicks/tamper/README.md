
---
# Tamper Click

> [Tamper Click](https://www.mikroe.com/?pid_product=MIKROE-2551) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2551&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> Tamper Click is equipped with side-actuated detect switch. The switch itself acts as 
> a push button and has 2 Normally Open terminals, which get shorted when the force is applied. 
> The applied pressure closes the circuit, connecting the VCC routed to the first pin 
> of the switch with the INT pin on the mikroBUS. The microcontroller is then able to detect 
> a high logical level on the INT pin and the desired task can then be executed.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Tamper

### Example Key Functions

- `tamper_cfg_setup` Config Object Initialization function. 
```c
void tamper_cfg_setup ( tamper_cfg_t *cfg );
``` 
 
- `tamper_init` Initialization function. 
```c
err_t tamper_init ( tamper_t *ctx, tamper_cfg_t *cfg );
```

- `tamper_state` Function showes the state of the switch. 
```c
uint8_t tamper_state ( tamper_t *ctx );
```

### Application Init

> Initialization driver enables GPIO and also starts write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    tamper_cfg_t cfg;

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

    tamper_cfg_setup( &cfg );
    TAMPER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tamper_init( &tamper, &cfg );
}
```

### Application Task

> This is an example which demonstrates the use of Tamper Click board.
> It detects whether the state of switch on Tamper Click is changes to open or to closed.
> Results are being sent to the Usart Terminal where you can keep track of their changes.

```c
void application_task ( void )
{
    switch_state = tamper_state( &tamper );
    
    if ( switch_state == 1 && switch_state_old == 0 )
    {
        log_printf( &logger, "      Closed     \r\n" );
        log_printf( &logger, "- - - - - - - - -\r\n" );
        switch_state_old = 1;
    }

    if ( switch_state == 0 && switch_state_old == 1 )
    {
        log_printf( &logger, "       Open      \r\n" );
        log_printf( &logger, "- - - - - - - - -\r\n" );
        switch_state_old = 0;
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
