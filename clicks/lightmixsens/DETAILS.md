
---
# Light mix sens click

Light mix-sens Click is carrying TMD37253, an advanced proximity measurement, color sense (RGBC+IR), and digital ambient light sensing (ALS) device. The TMD37253 slim module package has been designed to accommodate a “single hole” aperture approach that incorporates an IR LED and factory calibrated LED driver. The proximity detection feature provides object detection (e.g., mobile device screen to the user’s ear) by photodiode detection of reflected IR energy (sourced by the integrated LED). The ALS detection feature provides photopic light intensity data. The color photodiodes have UV and IR blocking filters and a dedicated data converters producing 16-bit data.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lightmixsens_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/light-mix-sens-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the LightMixSens Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LightMixSens Click driver.

#### Standard key functions :

- `lightmixsens_cfg_setup` Config Object Initialization function.
```c
void lightmixsens_cfg_setup ( lightmixsens_cfg_t *cfg );
```

- `lightmixsens_init` Initialization function.
```c
err_t lightmixsens_init ( lightmixsens_t *ctx, lightmixsens_cfg_t *cfg );
```

- `lightmixsens_default_cfg` Light mix sens default configuration function.
```c
void lightmixsens_default_cfg ( lightmixsens_t *ctx );
```

#### Example key functions :

- `lightmixsens_write_byte` Generic Write Byte function.
```c
err_t lightmixsens_write_byte ( lightmixsens_t *ctx, uint8_t reg_addr, uint8_t data_in );
```

- `lightmixsens_read_byte` Generic Read Byte function.
```c
err_t lightmixsens_read_byte ( lightmixsens_t *ctx, uint8_t reg_addr, uint8_t *data_out );
```

- `lightmixsens_switch_ir_to_prox` Switch IR To Proximity function.
```c
void lightmixsens_switch_ir_to_prox ( lightmixsens_t *ctx );
```

## Examples Description

> This example show usage of Light Mix Sens Click. It switches the IR light for separate and 
> measure sectar of RGB lights. Click also measure proximity from the object using light source.

**The demo application is composed of two sections :**

### Application Init 

> Initializes all necessary peripherals and pins, initializes I2C driver and performs 
> the Click board default configuration to allow ALS/Color and Proximity measurements.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lightmixsens_cfg_t cfg;

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

    lightmixsens_cfg_setup( &cfg );
    LIGHTMIXSENS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lightmixsens_init( &lightmixsens, &cfg );

    lightmixsens_default_cfg( &lightmixsens );

    lightmixsens_cdata = LIGHTMIXSENS_DUMMY_DATA;
    lightmixsens_rdata = LIGHTMIXSENS_DUMMY_DATA;
    lightmixsens_gdata = LIGHTMIXSENS_DUMMY_DATA;
    lightmixsens_bdata = LIGHTMIXSENS_DUMMY_DATA;
    lightmixsens_pdata = LIGHTMIXSENS_DUMMY_DATA;

    log_printf( &logger, "*  Light mix-sens click initialization done.  *\r\n" );
}
  
```

### Application Task

> Waits until ALS/Color integration cycle was done and then reads the entire measurement.
> The all results will be sent to the selected UART terminal.

```c

void application_task ( void )
{
    lightmixsens_wait_atime( &lightmixsens );
    
    lightmixsens_read_word( &lightmixsens, LIGHTMIXSENS_REG_CDATA, &lightmixsens_cdata );
    lightmixsens_read_word( &lightmixsens, LIGHTMIXSENS_REG_RDATA, &lightmixsens_rdata );
    lightmixsens_read_word( &lightmixsens, LIGHTMIXSENS_REG_GDATA_IRDATA, &lightmixsens_gdata );
    lightmixsens_read_word( &lightmixsens, LIGHTMIXSENS_REG_BDATA, &lightmixsens_bdata );
    lightmixsens_read_byte( &lightmixsens, LIGHTMIXSENS_REG_PDATA, &lightmixsens_pdata );
    
    log_printf( &logger, "- Clear light:  %d lx\r\n", lightmixsens_cdata );
    log_printf( &logger, "- Red light:    %d lx\r\n", lightmixsens_rdata );
    log_printf( &logger, "- Green light:  %d lx\r\n", lightmixsens_gdata );
    log_printf( &logger, "- Blue light:   %d lx\r\n", lightmixsens_bdata );
    
    prox_app( );
    log_printf( &logger, "** Proximity:   %s\r\n", prox_str );
    
    log_printf( &logger, "\r\n" );
    Delay_ms ( 1000 );
} 

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LightMixSens

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
