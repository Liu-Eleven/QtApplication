/****************************************************************************
** Meta object code from reading C++ file 'ftpclient.h'
**
** Created: Sun Mar 4 11:51:04 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ftpclient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ftpclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTPClient[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      23,   10,   10,   10, 0x08,
      33,   10,   10,   10, 0x08,
      49,   43,   10,   10, 0x08,
      77,   71,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FTPClient[] = {
    "FTPClient\0\0slotLogin()\0slotPut()\0"
    "slotGet()\0state\0slotStateChanged(int)\0"
    "error\0slotDone(bool)\0"
};

const QMetaObject FTPClient::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FTPClient,
      qt_meta_data_FTPClient, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FTPClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FTPClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FTPClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTPClient))
        return static_cast<void*>(const_cast< FTPClient*>(this));
    return QDialog::qt_metacast(_clname);
}

int FTPClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotLogin(); break;
        case 1: slotPut(); break;
        case 2: slotGet(); break;
        case 3: slotStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: slotDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
