/****************************************************************************
** Meta object code from reading C++ file 'rhznotepad.h'
**
** Created: Fri Mar 2 11:35:13 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../rhznotepad.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rhznotepad.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RHZNotepad[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      22,   11,   11,   11, 0x08,
      33,   11,   11,   11, 0x08,
      44,   11,   11,   11, 0x08,
      57,   11,   11,   11, 0x08,
      69,   11,   11,   11, 0x08,
      84,   11,   11,   11, 0x08,
     108,   11,   11,   11, 0x08,
     125,   11,   11,   11, 0x08,
     147,   11,   11,   11, 0x08,
     189,   11,   11,   11, 0x08,
     207,   11,   11,   11, 0x08,
     218,   11,   11,   11, 0x08,
     231,   11,   11,   11, 0x08,
     243,   11,   11,   11, 0x08,
     255,   11,   11,   11, 0x08,
     273,   11,   11,   11, 0x08,
     297,   11,   11,   11, 0x08,
     311,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RHZNotepad[] = {
    "RHZNotepad\0\0newFile()\0OpenFile()\0"
    "SaveFile()\0SaveAsFile()\0slotPrint()\0"
    "AboutProcess()\0slotSetTextBackground()\0"
    "slotIsLineWarp()\0TextAreaWasModified()\0"
    "slotCurrentFormatChanged(QTextCharFormat)\0"
    "slotFont(QString)\0slotBold()\0slotItalic()\0"
    "slotUnder()\0slotColor()\0slotSize(QString)\0"
    "slotAlignment(QAction*)\0slotList(int)\0"
    "slotCursorPositionChanged()\0"
};

const QMetaObject RHZNotepad::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RHZNotepad,
      qt_meta_data_RHZNotepad, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RHZNotepad::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RHZNotepad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RHZNotepad::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RHZNotepad))
        return static_cast<void*>(const_cast< RHZNotepad*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int RHZNotepad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newFile(); break;
        case 1: OpenFile(); break;
        case 2: SaveFile(); break;
        case 3: SaveAsFile(); break;
        case 4: slotPrint(); break;
        case 5: AboutProcess(); break;
        case 6: slotSetTextBackground(); break;
        case 7: slotIsLineWarp(); break;
        case 8: TextAreaWasModified(); break;
        case 9: slotCurrentFormatChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        case 10: slotFont((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: slotBold(); break;
        case 12: slotItalic(); break;
        case 13: slotUnder(); break;
        case 14: slotColor(); break;
        case 15: slotSize((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: slotAlignment((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 17: slotList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: slotCursorPositionChanged(); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
