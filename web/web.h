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

/**
 * @file web.h
 * @brief HTTP server wrapper thread macros and structures.
 * @addtogroup WEB_THREAD
 * @{
 */

#ifndef _WEB_H_
#define _WEB_H_

#ifndef UDP_THREAD_STACK_SIZE
#define UDP_THREAD_STACK_SIZE   4096
#endif

#ifndef TCP_THREAD_STACK_SIZE
#define TCP_THREAD_STACK_SIZE   4096
#endif

#ifndef UDP_THREAD_PORT
#define UDP_THREAD_PORT         8000
#endif

#ifndef TCP_THREAD_PORT
#define TCP_THREAD_PORT         8000
#endif

#ifndef UDP_THREAD_PRIORITY
#define UDP_THREAD_PRIORITY     (LOWPRIO + 2)
#endif

#ifndef TCP_THREAD_PRIORITY
#define TCP_THREAD_PRIORITY     (LOWPRIO + 2)
#endif

extern THD_WORKING_AREA(wa_udp_echo_server, UDP_THREAD_STACK_SIZE);
extern THD_WORKING_AREA(wa_tcp_echo_server, TCP_THREAD_STACK_SIZE);

#ifdef __cplusplus
extern "C" {
#endif
  THD_FUNCTION(udp_echo_server, p);
  THD_FUNCTION(tcp_echo_server, p);
#ifdef __cplusplus
}
#endif

#endif /* _WEB_H_ */

/** @} */
