\mainpage Main Page
 
---
# ECG GSR click

ECG GSR click is a complete solution for PPG, ECG and GSR application development, utilizing a specialized IC with a clinical-grade analog front-end (AFE) and electrical front-end. ECG GSR click uses the AS7030B IC, an ultra-low power, multi-channel bio-sensor, which features a wide range of different options, making it an ideal solution for development of blood oxygen level, heart rate and galvanic skin response monitoring applications, fitness applications, for the ECG bio-authentication, and similar applications related to heart monitoring. ECG GSR click is also equipped with the 3.5mm electrodes connectors, making it ready to be used out of the box.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ecg_gsr_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ecg-gsr-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the ECG GSR Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly from compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ECG GSR Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ecg_gsr_cfg_setup ( ecg_gsr_cfg_t *cfg ); 
 
- Initialization function.
> ecg_gsr_err_t ecg_gsr_init ( ecg_gsr_t *ctx, ecg_gsr_cfg_t *cfg );

- Click Default Configuration function.
> void ecg_gsr_default_cfg ( ecg_gsr_t *ctx );


#### Example key functions :

- Function performs reading of an ID of the device.
> void ecg_gsr_read_dev_id( ecg_gsr_t *ctx, uint8_t register_address, uint8_t *dev_id_out, uint8_t num_of_regs );
 
- Function writes 8-bit data to the register.
> ecg_gsr_err_t ecg_gsr_write_reg( ecg_gsr_t *ctx, uint8_t register_address, uint8_t transfer_data );

- Function performs the SW reset of the device and waits until the device returns back to normal state.
> void ecg_gsr_reset( ecg_gsr_t *ctx );

## Examples Description

> This click is made for PPG, ECG and GSR,
> equipped with an ultra-low power, multi channel, integrated biopotential AFE and EFE.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver, performs SW reset of all the registers, which puts the registers in their initial state.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    
    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    
    //  Click initialization.
    ecg_gsr_cfg_setup( &ecg_gsr_cfg );
    ECG_GSR_MAP_MIKROBUS( ecg_gsr_cfg, MIKROBUS_1 );
    ecg_gsr_init( &ecg_gsr, &ecg_gsr_cfg );
    Delay_1sec();
    ecg_gsr_default_cfg( &ecg_gsr, &ecg_gsr_cfg );
    Delay_1sec();
}
  
```

### Application Task

> Depending on the user selection, application measures:
> value of oxygen level in human's blood or
> heartrate or
> galvanic skin response

```c

ecg_gsr_err_t application_task( void )
{
    // ------------------------------------------------------------
    // Check the presence of the ECG GSR Click by reading device ID.
    // ------------------------------------------------------------
    ecg_gsr_read_dev_id(&ecg_gsr, ECG_GSR_ID_REG, &dev_id , 1);
    
    if ( dev_id != ECG_GSR_DEV_ID )
    {
        return ecg_gsr_init_error;
    }

    // ------------------------------------------------------------
    // Enable desired functionality of the ECG GSR Click.
    // ------------------------------------------------------------
    if ( ecg_gsr_cfg.click_functionality == DEFAULT_ECG_GSR_CLICK_FUNCTIONALITY )
    {
        ecg_gsr_get_oxygen_saturation();
    } else if ( ecg_gsr_cfg.click_functionality == ENABLE_HEARTRATE_FUNCTIONALITY )
    {
        ecg_gsr_get_heartrate();
    } else if ( ecg_gsr_cfg.click_functionality == ENABLE_GALVANIC_SKIN_RESPONSE_FUNCTIONALITY )
    {
        ecg_gsr_get_galvanic_skin_response();
    } else
    {
        return ecg_gsr_init_error;
    }
    
    return ecg_gsr_ok;
}

```

## Note

The full application code, and ready to use projects can be  installed directly from compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ECG_GSR

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
