\mainpage Main Page

---
# Diff pressure click

> Diff pressure click carries NXP’s MPXV5010DP signal conditioned, temperature compensated and calibrated pressure sensor with two axial ports to accommodate industrial grade tubing. 

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

- `diffpressure_cfg_setup` Config Object Initialization function.
```c
void diffpressure_cfg_setup ( diffpressure_cfg_t *cfg ); 
```

- `diffpressure_init` Initialization function.
```c
err_t diffpressure_init ( diffpressure_t *ctx, diffpressure_cfg_t *cfg );
```

#### Example key functions :

- `diffpressure_read_adc_voltage` This function read ADC voltage value from Diff Pressure click.
```c
float diffpressure_read_adc_voltage ( diffpressure_t *ctx );
```

- `diffpressure_get_pa_difference` This function get pressure difference [Pa].
```c
int32_t diffpressure_get_pa_difference ( diffpressure_t *ctx, float adc_voltage );
```

## Example Description
 
> This application is temperature compensated and calibrated pressure sensor.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    diffpressure_cfg_t cfg;

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
    diffpressure_cfg_setup( &cfg );
    DIFFPRESSURE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    if ( DIFFPRESSURE_OK != diffpressure_init( &diffpressure, &cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> This is an example which demonstrates the use of Diff Pressure click board.
The example reads the values of ADC module (MPC3551) 22-bit register value
converted to voltage and the pressure difference [ Pa ] and displays
those values on the USB UART.

```c

void application_task ( void )
{
    float adc_voltage = 0;
    int32_t difference = 0;

    adc_voltage = diffpressure_read_adc_voltage( &diffpressure );
    difference = diffpressure_get_pa_difference( &diffpressure, adc_voltage );

    log_printf( &logger, " ADC Voltage: %.3f [V]\r\n", adc_voltage );

    log_printf( &logger, " Pressure Diff: %ld [Pa]\r\n\n", difference );

    Delay_ms( 100 );
}  

```
The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Diffpressure

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
