#include "skinsurl.h"
#include "ui_skinsurl.h"

SkinsUrl::SkinsUrl(GosumemoryClient *client, QWidget *parent) :
	QDialog(parent)
	, gosumemoryClient(client)
	, ui(new Ui::SkinsUrl)
{
	ui->setupUi(this);
	loadData();

	ui->skinURLsTable->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->skinURLsTable->setSelectionBehavior(QAbstractItemView::SelectItems);

	connect(ui->addSkinBtn, &QPushButton::clicked, this, &SkinsUrl::on_addSkinBtn_clicked);
	connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SkinsUrl::on_saveBtnClicked);
	connect(ui->removeSkinBtn, &QPushButton::clicked, this, &SkinsUrl::on_removeSkinBtn_clicked);
	connect(gosumemoryClient, &GosumemoryClient::messageReceived, this, &SkinsUrl::on_gosumemoryMessage_received);
}


SkinsUrl::~SkinsUrl()
{
	delete ui;
}


void SkinsUrl::loadData()
{
	qDebug() << "[Osu!Skins] Loading data";
	QSettings settings;
	settings.beginGroup("skin");
	auto skins = settings.childKeys();

	for (auto skin : skins)
	{
		addRow(skin, settings.value(skin).toString());
	}
}


void SkinsUrl::on_addSkinBtn_clicked()
{
	auto skins = getListedSkins();
	auto skinName = getSkinName();

	// Match, the skin is already present
	if (skins.indexOf(skinName) != -1) {
		return;
	}

	addRow(skinName);
}


void SkinsUrl::on_removeSkinBtn_clicked()
{
	QSettings settings;
	auto selectionModel = ui->skinURLsTable->selectionModel();
	if (!selectionModel->hasSelection()){
		return;
	}

	auto selected = selectionModel->selectedIndexes();

	for (auto selection : selected) {
		auto row = selection.row();
		auto skinName = ui->skinURLsTable->item(row, 0)->text();

		settings.remove(QString("skin/%1").arg(skinName));
		ui->skinURLsTable->removeRow(row);
	}
}


void SkinsUrl::on_saveBtnClicked()
{
	qDebug() << "[Osu!Skins] Saving data";

	for (int row = 0; row < ui->skinURLsTable->rowCount(); row++) {
		auto skinNameItem = ui->skinURLsTable->item(row, 0);
		auto skinUrlItem  = ui->skinURLsTable->item(row, 1);

		if (skinUrlItem == nullptr || skinNameItem == nullptr) {
			return;
		}

		auto skinName = skinNameItem->text();
		auto skinUrl  = skinUrlItem->text();

		if (!isUrl(skinUrl)) {
			QMessageBox().critical(this, "Error", "Invalid url");
			break;
		}

		QSettings settings;
		QString key = QString("skin/%1").arg(skinName);
		settings.setValue(key, skinUrl);
	}
  accept();
}


void SkinsUrl::on_gosumemoryMessage_received(GosuMemoryDataWrapper message)
{
	ui->addSkinBtn->setEnabled(true);
	ui->currentSkinLabel->setText(message.getSkinName());
}


void SkinsUrl::addRow(QString skinName, QString skinUrl)
{
	// adding new line
	ui->skinURLsTable->insertRow(ui->skinURLsTable->rowCount());

	auto skinNameItem = new QTableWidgetItem(skinName);
	skinNameItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

	// Skin Name column
	ui->skinURLsTable->setItem(
		ui->skinURLsTable->rowCount() - 1,
		0,
		skinNameItem
	);

	// Skin URL column
	ui->skinURLsTable->setItem(
		ui->skinURLsTable->rowCount() - 1,
		1,
		new QTableWidgetItem(skinUrl)
	);

}


QStringList SkinsUrl::getListedSkins()
{
	QStringList skins;
	for (int row = 0; row < ui->skinURLsTable->rowCount(); row++) {
		auto value = ui->skinURLsTable->item(row, 0);
		if (value == nullptr){
			continue;
		}
		skins << value->text();
	}
	return skins;
}


QString SkinsUrl::getSkinName()
{
	return ui->currentSkinLabel->text();
}


bool SkinsUrl::isUrl(QString url)
{
	QRegularExpression rx("(https?:\\/\\/)?(www)?.*\\.(.){2,}");
	return rx.globalMatch(url).hasNext();
}
