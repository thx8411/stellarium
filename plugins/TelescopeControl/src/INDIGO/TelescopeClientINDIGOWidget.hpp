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


#ifndef TELESCOPECLIENTINDIGOWIDGET_HPP
#define TELESCOPECLIENTINDIGOWIDGET_HPP

#include <QWidget>

#include "INDIGOConnection.hpp"

namespace Ui {
class TelescopeClientINDIGOWidget;
}

class TelescopeClientINDIGOWidget : public QWidget
{
	Q_OBJECT

public:
	explicit TelescopeClientINDIGOWidget(QWidget *parent = nullptr);
	~TelescopeClientINDIGOWidget() override;

	QString host() const;
	void setHost(const QString& host);
	int port() const;
	void setPort(int port);
	QString selectedDevice() const;
	void setSelectedDevice(const QString& device);

private slots:
	void onConnectionButtonClicked();
	void onDevicesChanged();
	void onServerDisconnected(int code);

private:
	Ui::TelescopeClientINDIGOWidget *ui;
	INDIGOConnection mConnection;
};

#endif // TELESCOPECLIENTINDIGOUI_HPP
