/*
 *  bdremoteng - helper daemon for Sony(R) BD Remote Control
 *  Based on bdremoted, written by Anton Starikov <antst@mail.ru>.
 *
 *  Copyright (C) 2009  Michael Wojciechowski <wojci@wojci.dk>
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

/** \ingroup Gen
 *  @{
 */

/*! \file bdrcfg.c
  \brief Implements functions for handling configuration.

  Implements a few functions used to set certain config keys.
*/

#include "bdrcfg.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <globaldefs.h>

void setDefaults(configuration* _config)
{
  assert(_config != NULL);

  _config->listen_port = 8888;
  _config->disconnect_timeout = 60;
  _config->repeat_rate  = 10;
  _config->repeat_delay = 200;
  _config->debug       = 0;
  _config->interface_addr_set = 0;
  FREEVAL(_config->interface_addr);
  FREEVAL(_config->remote_addr);
  _config->remote_addr = NULL;
  _config->detach      = 1;
  FREEVAL(_config->release);
  _config->lirc_namespace = 0;
  _config->release     = NULL;
  _config->event_out = 0;
  FREEVAL(_config->user);
  _config->user        = NULL;
  FREEVAL(_config->group);
  _config->group       = NULL;
  _config->log_filename_set = 0;
  FREEVAL(_config->log_filename);
  _config->log_filename = NULL;
  _config->battery_script_set = 0;
  FREEVAL(_config->battery_script);
  _config->battery_script = NULL;
}

void setRemoteAddress(configuration* _config, const char* _address)
{
  assert(_config != NULL);
  assert(_address != NULL);

  SETVAL(_config->remote_addr, _address);
}

void setInterfaceAddress(configuration* _config, const char* _address)
{
  assert(_config != NULL);
  assert(_address != NULL);

  SETVAL(_config->interface_addr, _address);
  _config->interface_addr_set = 1;
}

void setRelease(configuration* _config, const char* _release)
{
  assert(_config != NULL);
  assert(_release != NULL);

  SETVAL(_config->release, _release);
}

void setUser(configuration* _config, const char* _user)
{
  assert(_config != NULL);
  assert(_user != NULL);

  SETVAL(_config->user, _user);
}

void setGroup(configuration* _config, const char* _group)
{
  assert(_config != NULL);
  assert(_group != NULL);

  SETVAL(_config->group, _group);
}

void setBatteryScript(configuration* _config, const char* _script)
{
   assert(_config != NULL);
   assert(_script != NULL);

   SETVAL(_config->battery_script, _script);
   _config->battery_script_set = 1;
}

void destroyConfig(configuration* _config)
{
  assert(_config != NULL);

  FREEVAL(_config->remote_addr);
  FREEVAL(_config->release);
  FREEVAL(_config->user);
  FREEVAL(_config->group);
  FREEVAL(_config->log_filename);
  FREEVAL(_config->battery_script);
}

void printConfig(const configuration* _config)
{
  assert(_config != NULL);

  fprintf(printStream, "Configuration:\n");
  fprintf(printStream, " - listen port : %d.\n", _config->listen_port);
  fprintf(printStream, " - timeout     : %d second(s).\n", _config->disconnect_timeout);
#if ENABLE_REPEAT
  fprintf(printStream, " - repeat rate : %d per secound.\n", _config->repeat_rate);
  fprintf(printStream, " - repeat delay: %d ms.\n", _config->repeat_delay);
#else
  fprintf(printStream, " - repeat rate : disabled.\n");
  fprintf(printStream, " - repeat delay: disabled.\n");
#endif
  if (_config->release == NULL)
    {
      fprintf(printStream, " - release     : not set.\n");
    }
  else
    {
      fprintf(printStream, " - release     : %s.\n", _config->release);
    }
  fprintf(printStream, " - LIRC names  : %d.\n", _config->lirc_namespace);
  fprintf(printStream, " - event output: %d.\n", _config->event_out);
  fprintf(printStream, " - debug       : %d.\n", _config->debug);
  if (_config->debug)
    {
      fprintf(printStream, "                 LIRC thread(%u) sock(%u) callback(%u),\n",
	      BDREMOTE_MASKCHECK(MODULEMASK_LIRC_THR),
	      BDREMOTE_MASKCHECK(MODULEMASK_LIRC_SOCK),
	      BDREMOTE_MASKCHECK(MODULEMASK_LIRC_CB));

      fprintf(printStream, "                 bluetooth interface(%u) implementation(%u),\n",
	      BDREMOTE_MASKCHECK(MODULEMASK_BT_IF),
	      BDREMOTE_MASKCHECK(MODULEMASK_BT_IMPL));
 
      fprintf(printStream, "                 queue(%u),\n", 
	      BDREMOTE_MASKCHECK(MODULEMASK_QUEUE));

      fprintf(printStream, "                 spare(%u),\n", 
	      BDREMOTE_MASKCHECK(MODULEMASK_SPARE));

      fprintf(printStream, "                 main(%u).\n", 
	      BDREMOTE_MASKCHECK(MODULEMASK_MAIN));

    }

  if (_config->interface_addr_set)
    {
      fprintf(printStream, " - iface addr  : %s.\n", _config->interface_addr);
    }
  else
    {
      fprintf(printStream, " - iface addr  : ANY.\n");
    }

  fprintf(printStream, " - remote addr : %s.\n", _config->remote_addr);
  fprintf(printStream, " - detach      : %d.\n", _config->detach);
  if (_config->user == NULL)
    {
      fprintf(printStream, " - user        : not set.\n");
    }
  else
    {
      fprintf(printStream, " - user        : %s.\n", _config->user);
    }
  if (_config->group == NULL)
    {
      fprintf(printStream, " - group       : not set.\n");
    }
  else
    {
      fprintf(printStream, " - group       : %s.\n", _config->group);
    }
  if (_config->log_filename_set)
    {
      fprintf(printStream, " - log         : '%s'.\n", _config->log_filename);
    }
  else
    {
      fprintf(printStream, " - log         : stdout.\n");
    }
  if (_config->battery_script_set)
     {
        fprintf(printStream, " - battery\n");
        fprintf(printStream, " - script    : '%s'.\n", _config->battery_script);
     }
  else
     {
        fprintf(printStream, " - battery\n");
        fprintf(printStream, " - script    : not set.\n");
     }
}

int userAndGroupSet(const configuration* _config)
{
  int status = 1;
  assert(_config != NULL);

  if (_config->user == NULL)
    {
      status = 0;
    }
  if (_config->group == NULL)
    {
      status = 0;
    }

  return status;
}

void setLogFilename(configuration* _config, const char* _filename)
{
  assert(_config != NULL);
  assert(_filename != NULL);

  SETVAL(_config->log_filename, _filename);
  _config->log_filename_set = 1;
}

/*@}*/

