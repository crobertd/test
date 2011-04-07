#ifndef TEST_H
#define TEST_H

#include <QtGui/QMainWindow>

#include "ui_TestWindow.h"
#include "ui_SizeDialog.h"

class TestWindow : public QMainWindow
{
	Q_OBJECT

public:
	TestWindow(QUrl url);

	void setSize(int width, int height);

private Q_SLOTS:
    void open();
    void reload();
	void setSize640x480() { setSize(640, 480); }
	void setSize800x600() { setSize(800, 600); }
	void setSize1024x768() { setSize(1024, 768); }
	void setSizeCustom();

private:
	Ui::TestWindow ui;
};

#endif // TEST_H
