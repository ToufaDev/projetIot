/*
 * Copyright (C) 2015 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Example application for demonstrating the RIOT network stack
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>
#include <lpsxxx.h>
#include <lpsxxx_params.h>
#include <lpsxxx_internal.h>

#include "shell.h"
#include "msg.h"
#include "xtimer.h"
#include "net/af.h"
#include "net/protnum.h"
#include "net/ipv6/addr.h"
#include "net/sock/udp.h"

#define MAIN_QUEUE_SIZE     (8)
int main(void)
{
  sock_udp_ep_t local = SOCK_IPV6_EP_ANY;
  sock_udp_t sock;
  local.port = 0xabcd;
  
  if (sock_udp_create(&sock, &local, NULL, 0) < 0)
    {
      puts("Error creating UDP sock");
      return 1;
    }

  lpsxxx_t sensor;
  char data[32];
  int i, temp_abs;
  int16_t temp;
  int error = lpsxxx_init(&sensor, &lpsxxx_params[0]);

  if (error != LPSXXX_OK)
    {
      puts("error on lpsxxx_init\n");
      return -1;
    }
  puts("starting experiment....\n");
  for (i = 0; i < 10; i++)
    {
      xtimer_sleep(1);
      error = lpsxxx_read_temp(&sensor, &temp);
      if (error == LPSXXX_OK)
	      { 
	        temp_abs = temp / 100;
	        temp -= temp_abs * 100;
	        snprintf(data, 32, "temp : %2i.%02iC", temp_abs, temp);
	        data[31] = '\0';
	        puts(data);
	        puts("\n");
          sock_udp_ep_t remote = { .family = AF_INET6 };
          remote.port = 12345;
          /* Ici on envoie en multicast à tous les nodes c'est pas ouf faut mettre l'addr ipv6 en dur du puit de donnée */
          ipv6_addr_set_all_nodes_multicast((ipv6_addr_t *)&remote.addr.ipv6, IPV6_ADDR_MCAST_SCP_LINK_LOCAL);
          if (sock_udp_send(&sock, data, 32, &remote) < 0)
            {
              puts("Error sending message");
              sock_udp_close(&sock);z
            return 1;
            }
	      }
    }

  puts("experiment over\n");  
  lpsxxx_disable(&sensor);
  return 0;
}
