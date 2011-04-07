#include "test.h"

#include "VApplication.h"

#if 0
void loadDummyDataFiles(const QString& directory)
{
    QDir dir(directory+"/dummydata", "*.qml");
    QStringList list = dir.entryList();
    for (int i = 0; i < list.size(); ++i) {
        QString qml = list.at(i);
        QFile f(dir.filePath(qml));
        f.open(QIODevice::ReadOnly);
        QByteArray data = f.readAll();
        QDeclarativeComponent comp(VApplication::instancex()->engine());
        comp.setData(data, QUrl());
        QObject *dummyData = comp.create();

        if(comp.isError()) {
            QList<QDeclarativeError> errors = comp.errors();
            foreach (const QDeclarativeError &error, errors) {
                qWarning() << error;
            }
        }

        if (dummyData) {
            qWarning() << "Loaded dummy data:" << dir.filePath(qml);
            qml.truncate(qml.length()-4);
            VApplication::instancex()->engine()->rootContext()->setContextProperty(qml, dummyData);
			dummyData->setParent(VApplication::instancex()->view());
        }
    }
}
#endif

int main(int argc, char *argv[])
{
	VApplication app(argc, argv);
	app.addLibraryPath(QApplication::applicationDirPath() + "/plugins");

	QUrl url;
	bool fullScreen = false;

	for(int i = 1; i < argc; i++)
	{
		QString arg = argv[i];

		if (arg[0] == '-')
		{
			if (arg == "-full_screen")
				fullScreen = true;
		}
		else if (url.isEmpty())
		{
			url = QUrl::fromLocalFile(argv[1]);
		}
	}

	if (url.isEmpty())
	{
		if (fullScreen)
			url = QUrl::fromLocalFile("./QML_FullScreen/root.qml");
		else
			url = QUrl::fromLocalFile("./QML/root.qml");
//			url = QUrl::fromLocalFile("d:/QML/root.qml");
//			url = QUrl::fromLocalFile("d:/Subversion/Equinox/Demo/QML_FullScreen/root.qml");
//		fullScreen = true;
	}

	if (fullScreen)
	{
//		VApplication::init();
		VApplication::instancex()->addContext("default", url);
//		loadDummyDataFiles(VApplication::instancex()->rootDir());
		VApplication::instancex()->view()->showFullScreen();

		app.exec();
	}
	else
	{
		TestWindow testWindow(url);
//		loadDummyDataFiles(VApplication::instancex()->rootDir());
		testWindow.show();

		app.exec();
	}
}
