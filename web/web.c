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

/*
 * This file is a modified version of the lwIP web server demo. The original
 * author is unknown because the file didn't contain any license information.
 */

/**
 * @file web.c
 * @brief HTTP server wrapper thread code.
 * @addtogroup WEB_THREAD
 * @{
 */

#include "ch.h"

#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "web.h"
#include <string.h>
#include "chregistry.h"
#include "chprintf.h"
// #include <io_channel.h>
#if LWIP_NETCONN


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

static struct netconn *conn;
static struct netbuf *buf;
static struct ip_addr *addr;
static unsigned short port;
/**
 * Stack area for the udp thread.
 */
THD_WORKING_AREA(wa_udp_echo_server, UDP_THREAD_STACK_SIZE);

/**
 * UDP echo server thread.
 */
THD_FUNCTION(udp_echo_server, p)
{
  err_t err, recv_err;

  LWIP_UNUSED_ARG(p);

  conn = netconn_new(NETCONN_UDP);
  if (conn!= NULL)
  {
    err = netconn_bind(conn, IP_ADDR_ANY, UDP_THREAD_PORT);
    if (err == ERR_OK)
    {
      while (1)
      {
        recv_err = netconn_recv(conn, &buf);

        if (recv_err == ERR_OK)
        {
          addr = netbuf_fromaddr(buf);
          port = netbuf_fromport(buf);
          netconn_connect(conn, addr, port);
          buf->addr.addr = 0;
          netconn_send(conn,buf);
          netbuf_delete(buf);
        }
      }
    }
    else
    {
      netconn_delete(conn);
      // printf("can not bind netconn");
    }
  }
  else
  {
    // printf("can create new UDP netconn");
  }
  // return MSG_OK;
}

THD_WORKING_AREA(wa_tcp_echo_server, TCP_THREAD_STACK_SIZE);

/**
 * TCP echo server thread.
 */
THD_FUNCTION(tcp_echo_server,p)
{
    struct netconn *conn, *newconn;
  err_t err, accept_err;
  struct netbuf *buf;
  void *data;
  u16_t len;
  err_t recv_err;

  LWIP_UNUSED_ARG(p);

  /* Create a new connection identifier. */
  conn = netconn_new(NETCONN_TCP);

  if (conn!=NULL)
  {
    /* Bind connection to well known port number 7. */
    err = netconn_bind(conn, NULL, TCP_THREAD_PORT);

    if (err == ERR_OK)
    {
      /* Tell connection to go into listening mode. */
      netconn_listen(conn);

      while (1)
      {
        /* Grab new connection. */
         accept_err = netconn_accept(conn, &newconn);

        /* Process the new connection. */
        if (accept_err == ERR_OK)
        {
          recv_err = netconn_recv(newconn, &buf);
          while ( recv_err == ERR_OK)
          {
            do
            {
              netbuf_data(buf, &data, &len);
              netconn_write(newconn, data, len, NETCONN_COPY);

            }
            while (netbuf_next(buf) >= 0);

            netbuf_delete(buf);
            recv_err = netconn_recv(newconn, &buf);
          }

          /* Close connection and discard connection identifier. */
          netconn_close(newconn);
          netconn_delete(newconn);
        }
      }
    }
    else
    {
      netconn_delete(newconn);
      // printf(" can not bind TCP netconn");
    }
  }
  else
  {
    // printf("can not create TCP netconn");
  }
  // return MSG_OK;
}

#endif /* LWIP_NETCONN */

/** @} */
