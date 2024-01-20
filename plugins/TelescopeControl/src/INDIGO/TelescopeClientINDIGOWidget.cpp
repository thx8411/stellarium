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

#include "TelescopeClientINDIGOWidget.hpp"
#include "ui_TelescopeClientINDIGOWidget.h"

TelescopeClientINDIGOWidget::TelescopeClientINDIGOWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::TelescopeClientINDIGOWidget)
{
	ui->setupUi(this);
	QObject::connect(ui->connectButton, &QPushButton::clicked, this, &TelescopeClientINDIGOWidget::onConnectionButtonClicked);
	QObject::connect(&mConnection, &INDIGOConnection::newDeviceReceived, this, &TelescopeClientINDIGOWidget::onDevicesChanged);
	QObject::connect(&mConnection, &INDIGOConnection::removeDeviceReceived, this, &TelescopeClientINDIGOWidget::onDevicesChanged);
	QObject::connect(&mConnection, &INDIGOConnection::serverDisconnectedReceived, this, &TelescopeClientINDIGOWidget::onServerDisconnected);
}

TelescopeClientINDIGOWidget::~TelescopeClientINDIGOWidget()
{
	delete ui;
}

QString TelescopeClientINDIGOWidget::host() const
{
	return ui->lineEditHostName->text();
}

void TelescopeClientINDIGOWidget::setHost(const QString &host)
{
	ui->lineEditHostName->setText(host);
}

int TelescopeClientINDIGOWidget::port() const
{
	return ui->spinBoxTCPPort->value();
}

void TelescopeClientINDIGOWidget::setPort(int port)
{
	ui->spinBoxTCPPort->setValue(port);
}

QString TelescopeClientINDIGOWidget::selectedDevice() const
{
	return ui->devicesComboBox->currentText();
}

void TelescopeClientINDIGOWidget::setSelectedDevice(const QString &device)
{
	ui->devicesComboBox->setCurrentText(device);
}

void TelescopeClientINDIGOWidget::onConnectionButtonClicked()
{
	if (mConnection.isServerConnected())
		mConnection.disconnectServer();

	QString host = ui->lineEditHostName->text();
	QString port = ui->spinBoxTCPPort->text();
	mConnection.setServer(host.toStdString().c_str(), port.toUInt());
	mConnection.connectServer();
}

void TelescopeClientINDIGOWidget::onDevicesChanged()
{
	ui->devicesComboBox->clear();
	auto devices = mConnection.devices();
	ui->devicesComboBox->addItems(devices);
}

void TelescopeClientINDIGOWidget::onServerDisconnected(int code)
{
	Q_UNUSED(code)
	ui->devicesComboBox->clear();
}

