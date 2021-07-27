\mainpage Main Page
 


---
# VREG click

VReg click is a digitally controlled DC Voltage regulator in mikroBUS™ form factor. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vreg_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/vreg-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Vreg Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Vreg Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void vreg_cfg_setup ( vreg_cfg_t *cfg ); 
 
- Initialization function.
> VREG_RETVAL vreg_init ( vreg_t *ctx, vreg_cfg_t *cfg );

#### Example key functions :

- Get ADC value function.
> uint16_t vreg_get_adc ( vreg_t *ctx, uint8_t channel );
 
- Set output voltage function.
>void vreg_set_out_voltage ( vreg_t *ctx, uint16_t value_dac );

- Set output voltage procentage function.
> void vreg_set_output_voltage_procentage ( vreg_t *ctx, uint8_t value_dac_pct );

## Examples Description
 
> This is an example that demonstrates the use of VREG click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and sets output voltage.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    vreg_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    vreg_cfg_setup( &cfg );
    VREG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vreg_init( &vreg, &cfg );

    vreg_stop_measuring( &vreg );
    log_printf( &logger, " Stop Measuring \r\n" );
    Delay_1sec( );

    log_printf( &logger, " Set Out Voltage \r\n" );
    vreg_set_out_voltage( &vreg, 600 );
    Delay_1sec( );

    log_printf( &logger, " Start Measuring \r\n" );
    vreg_start_measuring( &vreg );
    Delay_1sec( );
}
  
```

### Application Task

> Reads ADC data from all 3 channels, converts those values to voltage 
> and displays the results on USB UART.

```c

void application_task ( void )
{
    ch_reg = vreg_get_adc( &vreg, VREG_CHANNEL_0 );
    voltage = ch_reg / 182.0;
   
    log_printf( &logger, " CH Reg  : %.2f V\r\n", voltage );
    
    Delay_10ms( );

    ch_in = vreg_get_adc( &vreg, VREG_CHANNEL_2 );
    voltage = ch_in / 182.0;
    
    log_printf( &logger, " CH In   : %.2f V\r\n", voltage );
    
    Delay_10ms( );
    
    ch_out = vreg_get_adc( &vreg, VREG_CHANNEL_1 );
    voltage = ch_out / 182.0;
    
    log_printf( &logger, " CH Out  : %.2f V\r\n", voltage );
    
    Delay_1sec( );
    log_printf( &logger, " ---------------------- \r\n" );
}  

```
The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Vreg

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
