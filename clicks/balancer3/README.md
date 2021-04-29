\mainpage Main Page
 
 

---
# Balancer 3 click

Balancer 3 Click is overvoltage protection device for 2-series cell lithium-ion battery packs that incorporates a high-accuracy precision overvoltage detection circuit and automatic cell imbalance correction. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/balancer3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/balancer-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Balancer3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Balancer3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void balancer3_cfg_setup ( balancer3_cfg_t *cfg ); 
 
- Initialization function.
> BALANCER3_RETVAL balancer3_init ( balancer3_t *ctx, balancer3_cfg_t *cfg );

#### Example key functions :

- Cell Balance Enable function.
> void balancer3_enable_cell_balance ( balancer3_t *ctx, uint8_t state );
 
- Overvoltage Condition Check function.
> uint8_t balancer3_check_overvoltage_cond ( balancer3_t *ctx );

## Examples Description

> This application is device for 2-series cell lithium-ion battery.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device sets the time interval variable (time_inter) to the 0, which is used for OV condition message logging.

```c

void application_init ( void )
{
   log_cfg_t log_cfg;
   balancer3_cfg_t cfg;

   log_cfg.level = LOG_LEVEL_DEBUG;
   LOG_MAP_USB_UART( log_cfg );
   log_init( &logger, &log_cfg );
   log_info(&logger, "---- Application Init ----");

   balancer3_cfg_setup( &cfg );
   BALANCER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
   balancer3_init( &balancer3, &cfg );
}
  
```

### Application Task

> Allows user to enter a commands that can enable or disable
   cell balance and check the overvoltage condition.
   When OV condition is not detected, the status message will be sent after every 8 seconds.
   When OV condition is detected, the status message will be sent after every 2 seconds.
   Press '0' when you want to disable cell balance.
   Press '1' when you want to enable cell balance.
   Press '2' when you want to check the OV condition status immediately.

```c

void application_task ( void )
{
   uint16_t time_inter;
   uint8_t ov_cond;

   balancer3_enable_cell_balance( &balancer3, BALANCER3_CELL_BALANCE_DIS );
   log_printf( &logger, "* Cell balance is disabled * %d\r\n" );
         
   balancer3_enable_cell_balance( &balancer3, BALANCER3_CELL_BALANCE_EN );
   log_printf( &logger, "* Cell balance is enabled * %d\r\n" );

    
   ov_cond = balancer3_check_overvoltage_cond( &balancer3 );
    
   if ( ( time_inter == 8000 ) || ( ov_cond == BALANCER3_OV_COND_DETECTED ) )
   {
      if ( ov_cond == BALANCER3_OV_COND_NOT_DETECTED )
        {
            log_printf( &logger, "* Overvoltage condition is not detected * %d\r\n" );
            time_inter = 0;
        }
        else if ( time_inter > 2000 )
        {
            log_printf( &logger, "* Overvoltage condition is detected * %d\r\n", ov_cond );
            time_inter = 0;
        }
        else
        {
            time_inter++;
        }
   }
   else
   {
      time_inter++;
   }
    
   Delay_ms( 1 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Balancer3

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
