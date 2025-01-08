
---
# Thermostat 3 Click

> [Thermostat 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3724) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3724&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application enables usage of the general purpose Thermostat Click 
> to be used with temperature sensors.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermostat3

### Example Key Functions

- `thermostat3_cfg_setup` Config Object Initialization function. 
```c
void thermostat3_cfg_setup ( thermostat3_cfg_t *cfg );
``` 
 
- `thermostat3_init` Initialization function. 
```c
err_t thermostat3_init ( thermostat3_t *ctx, thermostat3_cfg_t *cfg );
```

- `thermostat3_default_cfg` Click Default Configuration function. 
```c
void thermostat3_default_cfg ( thermostat3_t *ctx );
```

- `thermostat3_relay_control` This function enables control of the relay. 
```c
void thermostat3_relay_control ( thermostat3_t *ctx, uint8_t relay_pos );
```
 
- `thermostat3_get_fault_data` This function returns Fault data Value. 
```c
uint8_t thermostat3_get_fault_data ( temp_vals_t *tmp, uint8_t err );
```

- `thermostat3_get_thermocouple_temperature` This function returns 14-Bit Thermocouple Temperature Data. 
```c
float thermostat3_get_thermocouple_temperature ( temp_vals_t *tmp, uint8_t temp_in );
```

### Application Init

> Initialization driver init

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermostat3_cfg_t cfg;

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

    Delay_ms ( 100 );

    //  Click initialization.

    thermostat3_cfg_setup( &cfg );
    THERMOSTAT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermostat3_init( &thermostat3, &cfg );

    // Power on delay
    Delay_ms ( 200 );
    log_printf( &logger, "---- Start Thermostat 3 ----\r\n" );
}
```

### Application Task

> Waits for valid user input and executes functions based on set of valid commands

```c
void application_task ( void )
{
    //  Task implementation.

    float internal_temp;
    float thermocouple_temp;

    thermostat3_process( &thermostat3, &temp_val );

    internal_temp = thermostat3_get_internal_temperature( &temp_val, THERMOSTAT3_TEMP_IN_CELSIUS );
    log_printf( &logger, "# Internal Temperature: %.2f", internal_temp );
    Delay_ms ( 200 );
   
    thermocouple_temp = thermostat3_get_thermocouple_temperature( &temp_val, THERMOSTAT3_TEMP_IN_CELSIUS );
    log_printf( &logger, "# Thermocouple Temperature: %.2f", thermocouple_temp );
    Delay_ms ( 200 );
    
    if( thermostat3.relay_flag == 1)
    {
        thermostat3.relay_flag = 0;
        thermostat3_relay_control( &thermostat3, THERMOSTAT3_RELAY_OFF );
        log_printf( &logger, "# Relay OFF\r\n" );
    }
    else
    {
        thermostat3.relay_flag = 1;
        thermostat3_relay_control( &thermostat3, THERMOSTAT3_RELAY_ON );
        log_printf( &logger, "# Relay ON\r\n" );
    }
    Delay_ms ( 200 );

    if( thermostat3.fault_flag == 1 )
    {
        thermostat3.fault_flag = 0;
        log_printf( &logger, "# Fault status -- OFF\r\n" );
    }
    else
    {
        thermostat3.fault_flag = 1;
        log_printf( &logger, "# Fault status -- ON\r\n" );
    }
    Delay_ms ( 200 );

    if( thermostat3.fault_flag == 1 )
        {
            thermostat3.f_error++;
            if( thermostat3.f_error > 3 )
            {
                thermostat3.f_error = 0;
            }
            display_fault( thermostat3.f_error );
            
            thermostat3.fault_status = thermostat3_get_fault_data( &temp_val, 0x01 << thermostat3.f_error );
            
            if ( thermostat3.fault_status == 1 )
            {
                log_printf( &logger, " -- ERROR\r\n" );
            }
            else
            {
                log_printf( &logger, " -- OK\r\n" );
            }
        }
}
```

### Note

> - Additional Functions :
>  -void _displayFault( uint8_t f_error )  - Display fault

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
