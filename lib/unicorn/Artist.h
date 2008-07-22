/***************************************************************************
 *   Copyright 2005-2008 Last.fm Ltd.                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Steet, Fifth Floor, Boston, MA  02110-1301, USA.          *
 ***************************************************************************/

#ifndef UNICORN_ARTIST_H
#define UNICORN_ARTIST_H

#include "lib/DllExportMacro.h"
#include "lib/unicorn/ws/WsReply.h" //convenience
#include <QString>


class UNICORN_DLLEXPORT Artist
{
    QString m_name;

public:
    Artist()
    {}

    explicit Artist( const QString& name ) : m_name( name )
    {}

    operator QString() const { return m_name; }

    WsReply* share( const class User& recipient, const QString& message = "" );
};

#endif
