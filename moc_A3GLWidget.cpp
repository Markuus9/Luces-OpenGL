/****************************************************************************
** Meta object code from reading C++ file 'A3GLWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "A3GLWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'A3GLWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_A3GLWidget_t {
    QByteArrayData data[15];
    char stringdata0[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_A3GLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_A3GLWidget_t qt_meta_stringdata_A3GLWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "A3GLWidget"
QT_MOC_LITERAL(1, 11, 7), // "setTime"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 10), // "updateTime"
QT_MOC_LITERAL(4, 31, 4), // "Time"
QT_MOC_LITERAL(5, 36, 18), // "updateColorVermell"
QT_MOC_LITERAL(6, 55, 15), // "updateColorGroc"
QT_MOC_LITERAL(7, 71, 18), // "updateColorVioleta"
QT_MOC_LITERAL(8, 90, 15), // "updateColorVerd"
QT_MOC_LITERAL(9, 106, 12), // "updateTorxa1"
QT_MOC_LITERAL(10, 119, 12), // "updateTorxa2"
QT_MOC_LITERAL(11, 132, 12), // "updateTorxa3"
QT_MOC_LITERAL(12, 145, 12), // "updateTorxa4"
QT_MOC_LITERAL(13, 158, 12), // "updateTorxa5"
QT_MOC_LITERAL(14, 171, 12) // "updateTorxa6"

    },
    "A3GLWidget\0setTime\0\0updateTime\0Time\0"
    "updateColorVermell\0updateColorGroc\0"
    "updateColorVioleta\0updateColorVerd\0"
    "updateTorxa1\0updateTorxa2\0updateTorxa3\0"
    "updateTorxa4\0updateTorxa5\0updateTorxa6"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_A3GLWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   77,    2, 0x0a /* Public */,
       5,    0,   80,    2, 0x0a /* Public */,
       6,    0,   81,    2, 0x0a /* Public */,
       7,    0,   82,    2, 0x0a /* Public */,
       8,    0,   83,    2, 0x0a /* Public */,
       9,    0,   84,    2, 0x0a /* Public */,
      10,    0,   85,    2, 0x0a /* Public */,
      11,    0,   86,    2, 0x0a /* Public */,
      12,    0,   87,    2, 0x0a /* Public */,
      13,    0,   88,    2, 0x0a /* Public */,
      14,    0,   89,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void A3GLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<A3GLWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updateColorVermell(); break;
        case 3: _t->updateColorGroc(); break;
        case 4: _t->updateColorVioleta(); break;
        case 5: _t->updateColorVerd(); break;
        case 6: _t->updateTorxa1(); break;
        case 7: _t->updateTorxa2(); break;
        case 8: _t->updateTorxa3(); break;
        case 9: _t->updateTorxa4(); break;
        case 10: _t->updateTorxa5(); break;
        case 11: _t->updateTorxa6(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (A3GLWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&A3GLWidget::setTime)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject A3GLWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<MyGLWidget::staticMetaObject>(),
    qt_meta_stringdata_A3GLWidget.data,
    qt_meta_data_A3GLWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *A3GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *A3GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_A3GLWidget.stringdata0))
        return static_cast<void*>(this);
    return MyGLWidget::qt_metacast(_clname);
}

int A3GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MyGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void A3GLWidget::setTime(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
