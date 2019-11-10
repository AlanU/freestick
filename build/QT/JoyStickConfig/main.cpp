/**************************************************************************
Created by Alan Uthoff on 10/8/2013
Copyright (C) 2013.

This Code is free software; you can redistribute it and/or
modify it under the terms of the zlib/libpng License as published
by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
This software is provided 'as-is', without any express or implied warranty.

In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.
**************************************************************************/

#include "mainwindow.h"
#include "freestick.h"
#include "qfreestickdevicemanger.h"
#include <QQmlContext>
#include <QApplication>
#include <QQmlApplicationEngine>
#include "controllermappingtablemodel.h"
#include "devicelistmodel.h"
//This is a work around for VS 2013 not supporting constexpr correctly
//This should be change to constexpr once 2013 support is dropped
const char * version = "0.0.2";
#ifdef Q_OS_ANDROID

#include <native_app_glue/android_native_app_glue.h>
#include <QAndroidJniEnvironment>

#endif
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationVersion(version);
    QQmlApplicationEngine engine;
    //MainWindow w;
  //  w.show();
    FreeStickDeviceManager deviceManager;
#ifdef Q_OS_ANDROID
    QAndroidJniEnvironment qjniEnv;
    JavaVM * jvm = QAndroidJniEnvironment::javaVM();
    deviceManager.init(jvm);

#else
     deviceManager.init();
#endif
    QFreestickDeviceManger qDeviceManager(&deviceManager);//This is just a wrapper class to work with QML
    qmlRegisterType<ControllerMappingTableModel>("org.freestick.models", 1, 0, "ContorllerMapping");
    qmlRegisterType<DeviceListModel>("org.freestick.models", 1, 0, "DeviceList");

    engine.rootContext()->setContextProperty("deviceManager", &qDeviceManager);
    engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));

    return a.exec();
}

#if defined( Q_OS_ANDROID) && defined(FS_NATIVE_ANDROD)

void android_main(struct android_app* app)
{
    static struct android_app* app2;
    app_dummy();

    printf("Android main started");
    fflush(stdout);
    while(1)
    {
        // Check if we are exiting.
        if (app->destroyRequested != 0) {
           // engine_term_display(&engine);
            return;
        }
    }

}
#endif
