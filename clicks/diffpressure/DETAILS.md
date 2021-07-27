
# Diff pressure click

Diff pressure click carries NXP’s MPXV5010DP signal conditioned, temperature compensated and calibrated pressure sensor with two axial ports to accommodate industrial grade tubing. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/diffpressure_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/diff-pressure-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the diffpressure Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for diffpressure Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void diffpressure_cfg_setup ( diffpressure_cfg_t *cfg ); 
 
- Initialization function.
> DIFFPRESSURE_RETVAL diffpressure_init ( diffpressure_t *ctx, diffpressure_cfg_t *cfg );

- Click Default Configuration function.
> void diffpressure_default_cfg ( diffpressure_t *ctx );


#### Example key functions :

- Generic read data function.
> int32_t diffpressure_get_kpa_difference ( diffpressure_t *ctx, int32_t difference );
 
- Generic read data function.
> int32_t diffpressure_read_data ( diffpressure_t *ctx );

- Check status of measurement.
> status_t diffpressure_status_check ( diffpressure_t *ctx, int32_t result );

## Examples Description
 
> This application is temperature compensated and calibrated pressure sensor.

**The demo application is composed of two sections :**

### Application Init 

> Initialization device. Start sending log via UART.


```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    diffpressure_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    diffpressure_cfg_setup( &cfg );
    DIFFPRESSURE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    diffpressure_init( &diffpressure, &cfg );
}
  
```

### Application Task

> This is a example which demonstrates the use of Diff Pressure click board.
              The example is display
              values of ADC module (MPC3551) 22-bit register and
              value of difference pressure [ Pa ] via UART. 

```c

void application_task ( void )
{
    int32_t difference = 0;
    int32_t adc_value = 0;
    uint8_t difference_txt[ 20 ];
    uint8_t adc_value_txt[ 20 ];
    uint8_t status;

    adc_value = diffpressure_read_data( &diffpressure );
    difference = diffpressure_get_kpa_difference( &diffpressure, adc_value );
    status = diffpressure_status_check( &diffpressure, adc_value );

    if ( status == DIFFPRESSURE_OK )
    {
        log_printf( &logger, "ADC Value:  %d\r\n", adc_value_txt );

        log_printf( &logger, "Difference: &d\r\n", difference_txt );
        
        log_printf( &logger, "  [Pa] \r\n" );

        Delay_ms( 3000 );
    }

    if ( status == DIFFPRESSURE_OVH )
    {
        log_printf( &logger, "Overflow happened" );
        Delay_100ms( );
    }

    if ( status == DIFFPRESSURE_OVL )
    {
        log_printf( &logger, "Underflow happened" );
        Delay_100ms( );
    }

    log_printf( &logger, "" );
}  

```
The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.diffpressure

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
