\mainpage Main Page
 
---
# VREG click

VReg click is a digitally controlled DC Voltage regulator in mikroBUS™ form factor. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vreg_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/vreg-click>)

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
 
> The design is based on the well-known LM317-M circuit, with the addition of a 12-bit DAC, 12-bit ADC, and an Operational Amplifier. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - SPI, set output voltage.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    vreg_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    vreg_cfg_setup( &cfg );
    VREG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vreg_init( &vreg, &cfg );

    vreg_stop_measuring( &vreg );
    log_printf( &logger, " Stop  Measuring " );
    Delay_1sec( );

    log_printf( &logger, " Set Out Voltage " );
    vreg_set_out_voltage( &vreg, 600 );
    Delay_1sec( );

    log_printf( &logger, " Start Measuring " );
    vreg_start_measuring( &vreg );
    Delay_1sec( );
}
  
```

### Application Task

> This is a example which demonstrates the use of VREG click board.
  VREG click communicates with the device via SPI driver set DAC value and get ADC value.
  Results are being sent to the Usart Terminal where you can track their changes.
  All data logs write on usb uart changes for every 1 sec. 

```c

void application_task ( void )
{
    ch_reg = vreg_get_adc( &vreg, VREG_CHANNEL_0 );
   
    log_printf( &logger, " CH Reg  : %d \r\n", ch_reg );
    
    Delay_10ms( );

    ch_in = vreg_get_adc( &vreg, VREG_CHANNEL_1 );
    
    log_printf( &logger, " CH In   : %d \r\n ", ch_in );
    
    Delay_10ms( );

    ch_out = vreg_get_adc( &vreg, VREG_CHANNEL_2 );
    
    log_printf( &logger, " CH Out  : %d \r\n", ch_out );
    
    Delay_1sec( );
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
