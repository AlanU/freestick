/****************************************************************************
** Meta object code from reading C++ file 'joystickconfigwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../joystickconfigwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'joystickconfigwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_JoyStickConfigWidget_t {
    QByteArrayData data[5];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JoyStickConfigWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JoyStickConfigWidget_t qt_meta_stringdata_JoyStickConfigWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "JoyStickConfigWidget"
QT_MOC_LITERAL(1, 21, 6), // "update"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 36), // "on_DeviceListBox_currentIndex..."
QT_MOC_LITERAL(4, 66, 5) // "index"

    },
    "JoyStickConfigWidget\0update\0\0"
    "on_DeviceListBox_currentIndexChanged\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JoyStickConfigWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    1,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,

       0        // eod
};

void JoyStickConfigWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        JoyStickConfigWidget *_t = static_cast<JoyStickConfigWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->update(); break;
        case 1: _t->on_DeviceListBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject JoyStickConfigWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_JoyStickConfigWidget.data,
      qt_meta_data_JoyStickConfigWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *JoyStickConfigWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JoyStickConfigWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_JoyStickConfigWidget.stringdata0))
        return static_cast<void*>(const_cast< JoyStickConfigWidget*>(this));
    if (!strcmp(_clname, "freestick::IFSJoystickListener"))
        return static_cast< freestick::IFSJoystickListener*>(const_cast< JoyStickConfigWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int JoyStickConfigWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
