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

#include "ShareDialog.h"
#include "Settings.h"
#include "lib/unicorn/User.h"
#include <QLineEdit>
#include <QPainter>
#include <QTimer>
#include <QPushButton>


ShareDialog::ShareDialog( QWidget* parent )
        : QDialog( parent )
{
    ui.setupUi( this );
    connect( ui.friends, SIGNAL(editTextChanged( QString )), SLOT(enableDisableOk()) );
    ok()->setText( tr("Share") );

    WsReply* r = User( The::settings().username() ).getFriends();
    connect( r, SIGNAL(finished( WsReply* )), SLOT(onFriendsReturn( WsReply* )) );

    ui.friends->lineEdit()->installEventFilter( this );

}


void
ShareDialog::setTrack( const Track& t )
{
    m_track = t;
    ui.artist->setText( t.artist() );
    ui.album->setText( t.album() );
    ui.track->setText( t.prettyTitle() );
}


void
ShareDialog::onFriendsReturn( WsReply* r )
{
    QString const edit_text = ui.friends->currentText();
    ui.friends->clear();
    ui.friends->addItems( User::getFriends( r ) );
    ui.friends->setEditText( edit_text );
}


void
ShareDialog::enableDisableOk()
{
    ok()->setEnabled( ui.friends->currentText().size() );
}


void
ShareDialog::accept()
{
    WsReply* r;

    User recipient( ui.friends->currentText() );
    QString const message = ui.message->toPlainText();

    if (ui.artist->isChecked()) r = m_track.artist().share( recipient, message );
    if (ui.track->isChecked()) r = m_track.share( recipient, message );
    if (ui.album->isChecked()) r = m_track.album().share( recipient, message );

    //TODO feedback on success etc, do via that bar thing you planned

    QDialog::accept();
}


bool
ShareDialog::eventFilter( QObject* o, QEvent* e )
{
    if (e->type() != QEvent::Paint)
        return false;

    QWidget* w = (QWidget*)o;

    if (w->hasFocus()) return false;
    
    o->event( e );
    
    QString const text = tr( "Type friends' names or emails, separated by commas" );
    QRect r = w->rect().adjusted( 5, 2, -5, 0 );
    QPainter p( w );
    p.setPen( Qt::gray );
    p.setFont( w->font() );
    p.drawText( r, Qt::AlignVCenter, text );

    return true; //eat event
}
