\mainpage Main Page
 

---
# Oximeter 2 click

Oximeter 2 Click is a compact add-on board suitable for measuring blood oxygen saturation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/oximeter2_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/oximeter-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Oximeter2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Oximeter2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void oximeter2_cfg_setup ( oximeter2_cfg_t *cfg ); 
 
- Initialization function.
> OXIMETER2_RETVAL oximeter2_init ( oximeter2_t *ctx, oximeter2_cfg_t *cfg );

#### Example key functions :

- Generic read function.
> uint8_t oximeter2_generic_read ( oximeter2_t *ctx, uint8_t reg );
 
- Gets state of the int pin
> uint8_t oximeter2_get_int_status ( oximeter2_t *ctx );

- Generic function for reading als and proximity values
> uint16_t oximeter3_read_value ( oximeter3_t *ctx, uint8_t type_macro );

## Examples Description

> This application collects data from the sensor, calculates it and then logs the result.

**The demo application is composed of two sections :**

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

    Delay_ms( 300 );
}

void application_task ( void )
{
    oximeter2_logs_results();
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Oximeter2

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
