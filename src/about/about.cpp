#include "about.h"

About::About(QObject *parent)
	: QObject{parent}
{
}

void About::show()
{
	qDebug() << "[About] Displaying about...";
	QMessageBox::about(nullptr,
		"About Miraya",

		"<h1>Miraya</h1>"
		"<p>A Twitch chatbot with GosuMemory and osu! IRC support.</p>"
		"<p>Version: " + QApplication::applicationVersion() + "</p>"
		"<p>Copyright © "+ QString::number(QDate::currentDate().year()) + " Miraya Project</p>"
		"<p>This program is free software: you can redistribute it and/or modify "
		"it under the terms of the GNU General Public License as published by "
		"the Free Software Foundation, either version 3 of the License, or "
		"(at your option) any later version.</p>"
		"<p>This program is distributed in the hope that it will be useful, "
		"but WITHOUT ANY WARRANTY; without even the implied warranty of "
		"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
		"GNU General Public License for more details.</p>"
		"<p>You should have received a copy of the GNU General Public License "
		"along with this program.  If not, see <a href=\"https://www.gnu.org/licenses/\">"
		"https://www.gnu.org/licenses/</a>.</p>" +
		"<p>Icons provided by <a href=\"https://icons8.com\">Icons8</a></p>"
	);
	qDebug() << "[About] Closed";
}
