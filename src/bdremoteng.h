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

/** @defgroup app Application
 *  This group contains the non-generic parts of the application.
 *  @{
 */

/*! \file bdremoteng.h
  \brief Program name and version information.

  This file contains the program name end version information.

*/

/*! \mainpage bdremote-ng
 *
 *
 * This projects attempts to write a working daemon that takes input
 * from a PS3 bluetooth remote and converts it into something that can
 * be given to LIRC.
 *
 */

#ifndef BD_BDREMOTENG_H
#define BD_BDREMOTENG_H

/** Application name. */
#define progname "bdremoted"
/** Application version. */
#define VERSION "0.5"

/** Print usage information to stdout. */
void usage(void);

#endif /* BD_BDREMOTENG_H */

/*@}*/

