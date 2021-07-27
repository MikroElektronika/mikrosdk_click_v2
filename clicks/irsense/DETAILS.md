
---
# IR SENSE click

IR Sense click carries the AK9750 quantum-type IR sensor. The click is designed to run on a 3.3V power supply. It communicates with the target microcontroller over I2C interface, with additional functionality provided by the INT pin on the mikroBUS™ line >

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irsense_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ir-sense-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the IrSense Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for IrSense Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void irsense_cfg_setup ( irsense_cfg_t *cfg ); 
 
- Initialization function.
> IRSENSE_RETVAL irsense_init ( irsense_t *ctx, irsense_cfg_t *cfg );


#### Example key functions :

- Function write the 8-bit data to the target 8-bit register address of AK9750 sensor on IR Sense click board.
> void irsense_write_byte ( irsense_t *ctx, uint8_t reg_address, uint8_t write_data );
 
- Function read the 8-bit data from the target 8-bit register address of AK9750 sensor on IR Sense click board.
> uint8_t irsense_read_byte ( irsense_t *ctx, uint8_t reg_address );

- Function read the 16-bit data from the two target 8-bit register address of AK9750 sensor on IR Sense click board.
> uint16_t irsense_read_data ( irsense_t *ctx, uint8_t reg_address_low );

## Examples Description

> This application return the temperature of object.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - I2C, enable sensor, set soft reset, set Continuous Mode 0,  also write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    irsense_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    irsense_cfg_setup( &cfg );
    IRSENSE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irsense_init( &irsense, &cfg );

    log_printf( &logger, "     I2C Driver Init       \r\n"  );
    Delay_ms( 100 );
    log_printf( &logger, "---------------------------\r\n"  );

    irsense_power_on( &irsense );
    log_printf( &logger, "         Power On          \r\n"  );
    Delay_ms( 1000 );
    log_printf( &logger, "---------------------------\r\n"  );

    irsense_soft_reset( &irsense );
    log_printf( &logger, "        Soft Reset         \r\n"  );
    Delay_ms( 1000 );
    log_printf( &logger, "---------------------------\r\n"  );

    irsense_set_mode( &irsense, IRSENSE_ECNTL1_MODE_CONTINUOUS_0 );
    irsense_set_cutoff_frequency( &irsense, IRSENSE_ECNTL1_CUTOFF_FREQUENCY_0_6_Hz );
    log_printf( &logger, "  Set Continuous Mode 0    \r\n"  );
    log_printf( &logger, "Set cutoff frequency 0.6 Hz\r\n"  );
    Delay_ms( 100 );
    log_printf( &logger, "---------------------------\r\n"  );

    irsense_set_interrupts_reg( &irsense, IRSENSE_EINTEN_IR13_HIGH_INT_DISABLE,
                                         IRSENSE_EINTEN_IR13_LOW_INT_DISABLE,
                                         IRSENSE_EINTEN_IR24_HIGH_INT_DISABLE,
                                         IRSENSE_EINTEN_IR24_LOW_INT_DISABLE,
                                         IRSENSE_EINTEN_DRI_INT_ENABLE );

    log_printf( &logger, " Interrupt Source Setting  \r\n"  );
    log_printf( &logger, "Enable Data Ready Interrupt\r\n"  );
    Delay_ms( 100 );
    log_printf( &logger, "---------------------------\r\n"  );
    log_printf( &logger, "      IR Sense  Click      \r\n"  );
    log_printf( &logger, "---------------------------\r\n"  );
    log_printf( &logger, "      Observable Area      \r\n"  );
    deg_cel[ 0 ] = 32;
    deg_cel[ 1 ] = 176;
    deg_cel[ 2 ] = 67;
    deg_cel[ 3 ] = 0;
}
  
```

### Application Task

> This is an example which demonstrates the use of IR Sense Click board. Detects the temperature of objects and detects the motion in observable area of the AK9750 sensor. Results are being sent to the Usart Terminal where you can track their changes. All data logs write on usb uart changes for every 1 sec.

```c

void application_task ( void )
{
   if ( irsense_check_available( &irsense ) )
    {
        irsense_get_ir_sense( &irsense, &bottom_area, &left_area, &right_area, &top_area );

        log_printf( &logger, "- - - - - - - - -\r\n" );
        log_printf( &logger, " Bottom : %d \r\n", bottom_area );

        log_printf( &logger, " Left   : %d \r\n", left_area );

        log_printf( &logger, " Top    : %d \r\n", top_area );

        log_printf( &logger, " Right  : %d \r\n", right_area );
        log_printf( &logger, "- - - - - - - - -\r\n" );

        temperature = irsense_get_temperature( &irsense );
        log_printf( &logger, " Temperature: %f \r\n", temperature );
        log_printf( &logger, "---------------------------\r\n" );

        irsense_refresh( &irsense );
        Delay_ms( 1000 );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.IrSense

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
