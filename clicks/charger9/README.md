
---
# Charger 9 Click

> [Charger 9 Click](https://www.mikroe.com/?pid_product=MIKROE-3568) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3568&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application is battery charger, capable of charging one, two or three battery cells. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger9

### Example Key Functions

- `charger9_cfg_setup` Config Object Initialization function. 
```c
void charger9_cfg_setup ( charger9_cfg_t *cfg );
``` 
 
- `charger9_init` Initialization function. 
```c
err_t charger9_init ( charger9_t *ctx, charger9_cfg_t *cfg );
```

- Enable function
err_t charger9_enable ( charger9_t *ctx, CHARGER9_STATE pwr_state );
 
- Fast-Charge Indicate function
err_t charger9_fast_charge_ind ( charger9_t *ctx );

- Full-Charge Indicate function
err_t charger9_full_charge_ind ( charger9_t *ctx );

### Application Init

> Initializes GPIO driver and turns OFF the charger as initial state.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    charger9_cfg_t cfg;

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

    charger9_cfg_setup( &cfg );
    CHARGER9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    charger9_init( &charger9, &cfg );
    
    charger9_enable( &charger9, CHARGER9_DISABLE );
    en_flag = CHARGER9_DISABLE;
    Delay_ms ( 100 );
    
    log_printf( &logger, "** Charger 9 initialization done ** \r\n" );
}
```

### Application Task

> Checks which command was sent by user and performs the selected command.
> Also checks the fault condition, and when fault condition is detected sends a report message to the uart terminal 
> and turns OFF the charger. 

```c
void application_task ( )
{   
err_t charge_state;
    
    if ( en_flag == CHARGER9_DISABLE )
    {
        charger9_enable( &charger9, CHARGER9_ENABLE );
        en_flag = CHARGER9_ENABLE;
        
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        log_printf( &logger, "** Charger 9 is enabled ** \r\n" );
    }

    charge_state = charger9_full_charge_ind( &charger9 );
                
    if ( charge_state == CHARGER9_IND_ACTIVE )
    {
        log_printf( &logger, "** Full-Charge state ** \r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    charge_state = charger9_fast_charge_ind( &charger9 );
    if ( charge_state == CHARGER9_IND_ACTIVE )
    {
        log_printf( &logger, "** Fast-Charge state ** \r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    charge_state = charger9_fault_ind ( &charger9 );
    
    if ( charge_state == CHARGER9_IND_ACTIVE )
    {
        charger9_enable( &charger9, CHARGER9_DISABLE );
        en_flag = CHARGER9_DISABLE;
        
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        log_printf( &logger, "** Fault condition! ** \r\n" );
        log_printf( &logger, "** Charger 9 is disabled ** \r\n" );
    }
}
```

### Note

> When user sends a desired command to the charger, a report message will be sent to the uart terminal as 
> indication to the user.
> The possible commands, for Charger 9 control, will be written to the uart terminal.
> The alarm sound will be generated on the determined commands: enable, disable and fault condition detecting.

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
