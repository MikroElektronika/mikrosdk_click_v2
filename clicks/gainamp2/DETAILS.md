
---
# GainAMP 2 click

GainAMP 2 click is a 6-channel programmable gain amplifier, used to amplify signals on any of the 6 non-inverting input channels up to 32x, in eight discrete steps.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gainapm2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/gainamp-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the GainAmp2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for GainAmp2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gainamp2_cfg_setup ( gainamp2_cfg_t *cfg ); 
 
- Initialization function.
> GAINAMP2_RETVAL gainamp2_init ( gainamp2_t *ctx, gainamp2_cfg_t *cfg );

- Click Default Configuration function.
> void gainamp2_default_cfg ( gainamp2_t *ctx );


#### Example key functions :

- Click Default Configuration function.
> void gainamp2_default_cfg ( gainamp2_t *ctx );
 
- Generic transfer function.
> void gainamp2_generic_transfer ( gainamp2_t *ctx, spi_master_transfer_data_t *block );

- Send Command
> void gainamp2_write_Command( gainamp2_t *ctx, uint8_t instruction, uint8_t input )

## Examples Description

> This application is programmable gain amplifier

**The demo application is composed of two sections :**

### Application Init 

> Initializes CS pin as output and SPI module

```c

void application_init ( void )
{

}
  
```

### Application Task

> Setup GainAMP 2 click channel 4 to amplify the signal 4 times 

```c

void application_task ( void )
{
    // Nothing to do here 
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.GainAmp2

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