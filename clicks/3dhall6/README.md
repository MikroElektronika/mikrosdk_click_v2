\mainpage Main Page
 
---
# 3D Hall 6 click

> 3D Hall 6 Click is a very accurate, magnetic field sensing Click board™, used to measure the intensity of the magnetic field across three perpendicular axes. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3dhall6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/3d-hall-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the 3dHall6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 3dHall6 Click driver.

#### Standard key functions :

- `c3dhall6_cfg_setup` Config Object Initialization function.
```c
void c3dhall6_cfg_setup ( c3dhall6_cfg_t *cfg ); 
```

- `c3dhall6_init` Initialization function.
```c
err_t c3dhall6_init ( c3dhall6_t *ctx, c3dhall6_cfg_t *cfg );
```

#### Example key functions :

- `c3dhall6_set_reference_values` This function sets reference values for voltage and angle calculations.
```c
void c3dhall6_set_reference_values ( c3dhall6_t *ctx, c3dhall6_aux_ref_t ref_val );
```

- `c3dhall6_get_adc_value` This function reads ADC value on selected channel.
```c
void c3dhall6_get_adc_value ( c3dhall6_t *ctx, uint8_t channel_no, uint16_t *adc_value );
```

- `c3dhall6_get_volt` This function reads ADC value on selected channel and converts that value to Volts or miliVolts - depending on reference voltage setting.
```c
void c3dhall6_get_volt( c3dhall6_t *ctx, uint8_t channel_no, float *channel_voltage );
```

## Example Description

> This application measure the intensity of the magnetic field across three perpendicular axes.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c3dhall6_cfg_t cfg;

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
    c3dhall6_cfg_setup( &cfg );
    C3DHALL6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall6_init( &c3dhall6, &cfg );

    c3dhall6_aux_ref_t ref_val = 
    {
        .aux_ref_adc_ch0 = 2048.0,
        .aux_ref_adc_ch1 = 2048.0,
        .aux_ref_adc_ch2 = 2048.0,
        .aux_ref_adc_ch3 = 2048.0,
        .aux_ref_volt = 3.3
    };
    c3dhall6_set_reference_values( &c3dhall6, ref_val );
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Executes one or more 'c3dhall6_log_xxx_task' functions
> Additional Functions :
>
> - c3dhall6_log_adc_task() - performs and logs adc measurements on all channels
> - c3dhall6_log_volt_task() - performs and logs voltage measurements on all channels
> - c3dhall6_log_angleRad_task() - performs and logs angle measurements in radians on each die
> - c3dhall6_log_angleDeg_task() - performs and logs angle measurements in degrees on each die 

```c

void application_task ( void )
{
    c3dhall6_log_angle_deg_task( );
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.3dHall6

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
