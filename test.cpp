#include <QtGui>
#include <QtTest>

#include "test.h"
#include "VApplication.h"

TestWindow::TestWindow(QUrl url)
	: QMainWindow(0, 0)
{
	ui.setupUi(this);

//	VApplication::init();
	setCentralWidget(VApplication::instancex()->view());
	VApplication::instancex()->addContext("default", url);
//	loadDummyDataFiles(VApplication::instancex()->rootDir());
	setSize(800, 600);
}

void TestWindow::open()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Page"), ".", tr("QML Files (*.qml)"));

	if (fileName.length() > 0)
	{
		QUrl url = QUrl::fromLocalFile(fileName);
		VApplication::instancex()->addContext("default", url);
//		loadDummyDataFiles(VApplication::instance()->rootDir());
	}
}

void TestWindow::reload()
{
	VApplication::instancex()->reload();
}

void TestWindow::setSize(int width, int height)
{
	QSize windowSize = QWidget::size();
	QSize viewSize = VApplication::instancex()->view()->size();
	setFixedSize(width + windowSize.width() - viewSize.width(), height + windowSize.height() - viewSize.height());
}

void TestWindow::setSizeCustom()
{
	QDialog sizeDialog(this);
	Ui::SizeDialog().setupUi(&sizeDialog);

	QSpinBox* widthSpin = sizeDialog.findChild<QSpinBox*>("widthSpin");
	QSpinBox* heightSpin = sizeDialog.findChild<QSpinBox*>("heightSpin");

	if (!widthSpin || !heightSpin)
		return;

	widthSpin->setValue(size().width());
	heightSpin->setValue(size().height());

	sizeDialog.exec();

	setSize(widthSpin->value(), heightSpin->value());
}