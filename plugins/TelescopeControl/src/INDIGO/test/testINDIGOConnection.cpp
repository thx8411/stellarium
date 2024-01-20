/*
 * Copyright (C) 2017 Alessandro Siniscalchi <asiniscalchi@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */

#include "testINDIGOConnection.hpp"

#include <limits>
#include <cmath>

#include "INDIGOConnection.hpp"
#include "libindi/basedevice.h"

void TestINDIGOConnection::deafultCoordinates()
{
    INDIGOConnection::Coordinates position;
    QVERIFY(std::abs(position.RA - 0.0) < std::numeric_limits<double>::epsilon());
    QVERIFY(std::abs(position.DEC - 0.0) < std::numeric_limits<double>::epsilon());
}

void TestINDIGOConnection::defaultPosition()
{
    INDIGOConnection instance;
    QVERIFY(instance.position() == INDIGOConnection::Coordinates());
}

void TestINDIGOConnection::initialConnectionStatus()
{
    INDIGOConnection instance;
    QVERIFY(instance.isDeviceConnected() == false);
}

void TestINDIGOConnection::setPositionNotConnected()
{
    INDIGOConnection::Coordinates position;
    position.DEC = 0.1;
    position.RA = 0.2;

    INDIGOConnection instance;
    instance.setPosition(position);
    QVERIFY(instance.position() == INDIGOConnection::Coordinates());
}

void TestINDIGOConnection::listDevices()
{
    INDIGOConnection instance;
    QVERIFY(instance.devices().empty());

    INDI::BaseDevice device;
    device.setDeviceName("dummy");

    instance.newDevice(&device);
    QVERIFY(instance.devices().size() == 1);
    instance.removeDevice(&device);
    QVERIFY(instance.devices().empty());
}

QTEST_MAIN(TestINDIGOConnection)

