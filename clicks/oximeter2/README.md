
---
# Oximeter 2 Click

> [Oximeter2 Click](https://www.mikroe.com/?pid_product=MIKROE-4292) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4292&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application collects data from the sensor, calculates it and then logs the result.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Oximeter2

### Example Key Functions

- `oximeter2_cfg_setup` Config Object Initialization function. 
```c
void oximeter2_cfg_setup ( oximeter2_cfg_t *cfg );
``` 
 
- `oximeter2_init` Initialization function. 
```c
err_t oximeter2_init ( oximeter2_t *ctx, oximeter2_cfg_t *cfg );
```

- `oximeter2_generic_read` Generic read function. 
```c
uint8_t oximeter2_generic_read ( oximeter2_t *ctx, uint8_t reg );
```
 
- `oximeter2_get_int_status` Gets state of the int pin. 
```c
uint8_t oximeter2_get_int_status ( oximeter2_t *ctx );
```

- `oximeter3_read_value` Generic function for reading als and proximity values. 
```c
uint16_t oximeter3_read_value ( oximeter3_t *ctx, uint8_t type_macro );
```

### Application Init

> Initializes driver and performs the device configuration which puts Time Slot A and Time Slot B modes to active state. Before the device configuration, the SW reset will be performed, which puts the registers in their initial state.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    oximeter2_cfg_t cfg;
    
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

    oximeter2_cfg_setup( &cfg );
    OXIMETER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oximeter2_init( &oximeter2, &cfg );
    oximeter2_default_cfg( &oximeter2 );
}
```

### Application Task

> Application measures value of oxygen level in blood of a human. 

```c
void oximeter2_write_res ( uint32_t data_write )
{
    log_printf( &logger, "%u\r\n", data_write );
}

void oximeter2_logs_results( void )
{
    uint8_t final_result;
    
    oximeter2_read_data( &oximeter2, &res_slot[ 0 ] );

    log_printf( &logger, "Average result per photodiode is: \r\n" );
    
    switch ( oximeter2.enabled_channel )
    {
        case OXIMETER2_CH3_CH4_SELECTED:
        {
            log_printf( &logger, "PD3: " );
            oximeter2_write_res( res_slot[ 2 ] );
            log_printf( &logger, "PD4: " );
            oximeter2_write_res( res_slot[ 3 ] );

            final_result = ( res_slot[ 2 ] + res_slot[ 3 ] ) / 1000;
            break;
        }
        case OXIMETER2_ALL_CHANNELS_SELECTED:
        {
            log_printf( &logger, "PD1: " );
            oximeter2_write_res( res_slot[ 0 ] );
            log_printf( &logger, "PD2: " );
            oximeter2_write_res( res_slot[ 1 ] );
            log_printf( &logger, "PD3: " );
            oximeter2_write_res( res_slot[ 2 ] );
            log_printf( &logger, "PD4: " );
            oximeter2_write_res( res_slot[ 3 ]);

            final_result = ( res_slot[ 0 ] + res_slot [ 1 ] + res_slot[ 2 ] + res_slot[ 3 ] ) / 1000;
            break;
        }
        default:
        {
            break;
        }
    }
    
    if (final_result > 100)
    {
        final_result = 100;
    }
    log_printf( &logger, "Average result, in percentage: %u\r\n", ( uint16_t )final_result );
    log_printf( &logger, "-------------------------\r\n" );

    Delay_ms ( 300 );
}

void application_task ( void )
{
    oximeter2_logs_results();
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
