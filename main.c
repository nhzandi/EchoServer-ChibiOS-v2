/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ch.h"
#include "hal.h"
#include "test.h"
#include "ch.h"

#include "lwipthread.h"

#include "web/web.h"

/*
 * Orange LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg)
{
  (void)arg;
  chRegSetThreadName("blinker");
  while (TRUE)
  {
    palClearPad(GPIOD, GPIOD_LED6);
    chThdSleepMilliseconds(500);
    palSetPad(GPIOD, GPIOD_LED6);
    chThdSleepMilliseconds(500);
  }
}


/*
 * Application entry point.
 */
int main(void)
{

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();
  lwipInit(NULL);
  /*
   * Activates the serial driver 1 using the driver default configuration.
   */
  // sdStart(&SD3, NULL);

  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  /*
   * Creates the LWIP threads (it changes priority internally).
   */
  // chThdCreateStatic(wa_lwip_thread, LWIP_THREAD_STACK_SIZE, HIGHPRIO + 1,
  //                   lwip_thread, NULL);

  /*
   * Creates the UDP echo thread (it changes priority internally).
   */
  chThdCreateStatic(wa_udp_echo_server, sizeof(wa_udp_echo_server), NORMALPRIO + 1,
                    udp_echo_server, NULL);


  /*
   * Creates the TCP echo thread (it changes priority internally).
   */
  chThdCreateStatic(wa_tcp_echo_server, sizeof(wa_tcp_echo_server), NORMALPRIO + 1,
                    tcp_echo_server, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (TRUE)
  {
    // if (palReadPad(GPIOA, GPIOA_BUTTON) == 1)
    //   TestThread(&SD3);
    chThdSleepMilliseconds(500);
  }
}
