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

- `ecggsr_cfg_setup` Config Object Initialization function.
```c
void ecggsr_cfg_setup ( ecggsr_cfg_t *cfg ); 
```

- `ecggsr_init` Initialization function.
```c
err_t ecggsr_init( ecggsr_t *ctx, ecggsr_cfg_t* cfg );
```

- `ecggsr_default_cfg` Click Default Configuration function.
```c
void ecggsr_default_cfg( ecggsr_t *ctx, ecggsr_cfg_t *cfg );
```

#### Example key functions :

- `ecggsr_read_reg` Function performs reading of an ID of the device.
```c
err_t ecggsr_read_reg( ecggsr_t *ctx, uint8_t register_address, uint8_t *data_out, uint8_t num_of_regs );
```

- `ecggsr_write_reg` Function writes 8-bit data to the register.
```c
err_t ecggsr_write_reg( ecggsr_t *ctx, uint8_t register_address, uint8_t transfer_data );
```

- `ecggsr_reset` Function performs the SW reset of the device and waits until the device returns back to normal state.
```c
void ecggsr_reset( ecggsr_t *ctx );
```

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
    ecggsr_cfg_setup( &ecggsr_cfg );
    ECGGSR_MAP_MIKROBUS( ecggsr_cfg, MIKROBUS_1 );
    ecggsr_init( &ecggsr, &ecggsr_cfg );
    Delay_1sec();
    ecggsr_default_cfg( &ecggsr, &ecggsr_cfg );
    Delay_1sec();
}
  
```

### Application Task

> Depending on the user selection, application measures:
> 1. value of oxygen level in human's blood or
> 2. heartrate or
> 3. galvanic skin response

```c

void application_task( void )
{
    // ------------------------------------------------------------
    // Check the presence of the ECG GSR Click by reading device ID.
    // ------------------------------------------------------------
    ecggsr_read_dev_id( &ecggsr, &dev_id );
    if ( ECGGSR_DEV_ID == dev_id  )
    {
        // ------------------------------------------------------------
        // Enable desired functionality of the ECG GSR Click.
        // ------------------------------------------------------------
        if ( ENABLE_OXIMETER_FUNCTIONALITY == ecggsr_cfg.click_functionality )
        {
            ecggsr_get_oxy_saturation( );
        } 
        else if ( ENABLE_HEARTRATE_FUNCTIONALITY == ecggsr_cfg.click_functionality )
        {
            ecggsr_get_heartrate( );
        } 
        else if ( ENABLE_GALVANIC_SKIN_RESPONSE_FUNCTIONALITY == ecggsr_cfg.click_functionality )
        {
            ecggsr_get_gal_skin_resp( );
        } 
    }
}

```

The full application code, and ready to use projects can be  installed directly from compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ECGGSR

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
