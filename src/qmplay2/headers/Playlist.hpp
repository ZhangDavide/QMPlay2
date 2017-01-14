/*
	QMPlay2 is a video and audio player.
	Copyright (C) 2010-2017  Błażej Szczygieł

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published
	by the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include <IOController.hpp>

#include <QString>
#include <QList>

class Playlist
{
public:
	class Entry
	{
	public:
		enum Flags
		{
			Selected = 0x1,
			Skip = 0x2,
			StopAfter = 0x4,
			Locked = 0x8
		};

		inline Entry() :
			length(-1.0),
			flags(0), queue(0), GID(0), parent(0)
		{}

		QString name, url;
		double length;
		qint32 flags, queue, GID, parent;
	};
	typedef QVector<Entry> Entries;

	enum OpenMode
	{
		NoOpen,
		ReadOnly,
		WriteOnly
	};

	static Entries read(const QString &url, QString *name = NULL);
	static bool write(const Entries &list, const QString &url, QString *name = NULL);
	static QStringList extensions();

	virtual Entries read() = 0;
	virtual bool write(const Entries &) = 0;

	virtual ~Playlist();
private:
	static Playlist *create(const QString &url, OpenMode openMode, QString *name = NULL);
protected:
	QList<QByteArray> readLines();

	IOController<> ioCtrl;
};

#endif
