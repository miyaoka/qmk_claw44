/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// aaa

#pragma once

#undef TAPPING_TERM
#define TAPPING_TERM 250

#undef PREVENT_STUCK_MODIFIERS
#define PREVENT_STUCK_MODIFIERS

#undef MOUSEKEY_INTERVAL
#undef MOUSEKEY_DELAY
#undef MOUSEKEY_TIME_TO_MAX
#undef MOUSEKEY_MAX_SPEED
#undef MOUSEKEY_MOVE_DELTA

#define MOUSEKEY_INTERVAL 30
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 15
#define MOUSEKEY_MAX_SPEED 14
#define MOUSEKEY_MOVE_DELTA 3

#undef BLE_NUS_MIN_INTERVAL
#undef BLE_NUS_MAX_INTERVAL
#undef BLE_HID_MAX_INTERVAL
#undef BLE_HID_SLAVE_LATENCY

#define BLE_NUS_MIN_INTERVAL 30
#define BLE_NUS_MAX_INTERVAL 50
#define BLE_HID_MAX_INTERVAL 30
#define BLE_HID_SLAVE_LATENCY 4
