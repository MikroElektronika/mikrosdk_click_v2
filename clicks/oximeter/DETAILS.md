

---
# Oximeter click

> Oximeter click is a versatile photometric Click board�, perfectly suited for
measuring the blood oxygen saturation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/oximeter_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/oximeter-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Oximeter Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Oximeter Click driver.

#### Standard key functions :

- `oximeter_cfg_setup` Config Object Initialization function.
```c
void oximeter_cfg_setup ( oximeter_cfg_t *cfg ); 
```

- `oximeter_init` Initialization function.
```c
err_t oximeter_init ( oximeter_t *ctx, oximeter_cfg_t *cfg );
```

- `oximeter_default_cfg` Click Default Configuration function.
```c
void oximeter_default_cfg ( oximeter_t *ctx );
```

#### Example key functions :

- `oximeter_write_reg` Function writes 16-bit data to the register.
```c
err_t oximeter_write_reg ( oximeter_t* ctx, uint8_t reg, uint16_t data_in );
```

- `oximeter_set_time_slot_a` Function performs the configuration for Time Slot A and enables the interrupt for this Slot.
```c
err_t oximeter_set_time_slot_a ( oximeter_t* ctx, oximeter_enable_t* dev_enable, uint8_t set_mode );
```

- `oximeter_enable_channels` Function determines which channel/channels be enabled.
```c
err_t oximeter_enable_channels ( oximeter_t* ctx, uint8_t select_channel );
```

## Examples Description

> This application collects data from the sensor, calculates it and then logs the result.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and performs the device configuration which puts Time Slot A
> in enabled mode and LEDX2 (IR diode) to active state.  Before the device configuration, the
> SW reset will be performed and in this way we will put the registers in initial state.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    oximeter_cfg_t cfg;

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
    oximeter_cfg_setup( &cfg );
    OXIMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oximeter_init( &oximeter, &cfg );
    oximeter_default_cfg( &oximeter );
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Logs PD1-PD4 data on USB UART

```c

void application_task ( void )
{
    oxim_logs_results();
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Oximeter

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
