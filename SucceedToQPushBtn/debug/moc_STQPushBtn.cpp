/****************************************************************************
** Meta object code from reading C++ file 'STQPushBtn.h'
**
** Created: Thu Mar 8 18:36:40 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../STQPushBtn.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'STQPushBtn.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SucceedTOQPB[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       2,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
      21,   13, 0x0a095003,
      27,   13, 0x0a095003,

       0        // eod
};

static const char qt_meta_stringdata_SucceedTOQPB[] = {
    "SucceedTOQPB\0QString\0frame\0tip\0"
};

const QMetaObject SucceedTOQPB::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_SucceedTOQPB,
      qt_meta_data_SucceedTOQPB, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SucceedTOQPB::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SucceedTOQPB::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SucceedTOQPB::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SucceedTOQPB))
        return static_cast<void*>(const_cast< SucceedTOQPB*>(this));
    return QPushButton::qt_metacast(_clname);
}

int SucceedTOQPB::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = GetFrame(); break;
        case 1: *reinterpret_cast< QString*>(_v) = GetTip(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: SetFrame(*reinterpret_cast< QString*>(_v)); break;
        case 1: SetTip(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
