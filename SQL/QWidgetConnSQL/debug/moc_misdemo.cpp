/****************************************************************************
** Meta object code from reading C++ file 'misdemo.h'
**
** Created: Sun Mar 4 18:57:56 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../misdemo.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'misdemo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MISDemo[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x08,
      30,    8,    8,    8, 0x08,
      53,    8,    8,    8, 0x08,
      78,   73,    8,    8, 0x08,
     108,    8,    8,    8, 0x08,
     117,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MISDemo[] = {
    "MISDemo\0\0on_FindBtn_clicked()\0"
    "on_DeleteBtn_clicked()\0on_AddBtn_clicked()\0"
    "arg1\0on_FindStd_activated(QString)\0"
    "slotOk()\0slotCancel()\0"
};

const QMetaObject MISDemo::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MISDemo,
      qt_meta_data_MISDemo, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MISDemo::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MISDemo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MISDemo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MISDemo))
        return static_cast<void*>(const_cast< MISDemo*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MISDemo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_FindBtn_clicked(); break;
        case 1: on_DeleteBtn_clicked(); break;
        case 2: on_AddBtn_clicked(); break;
        case 3: on_FindStd_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: slotOk(); break;
        case 5: slotCancel(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
