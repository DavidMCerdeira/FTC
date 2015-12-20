import QtQuick 2.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

ColumnLayout {
    id: root
    spacing: 5
    Layout.margins: 30

    Text{
        id: title
        font.pointSize: 24
        text: "Employees Working"
    }

    RowLayout{
        width: parent.width
        MyComboBox{
            id: department
            anchors.left: parent.left
            editable: false
            Layout.minimumWidth: 150
            Layout.minimumHeight: 40
        }

//        Rectangle {
//            id: spacer
//            color: transparent
//            Layout.minimumWidth: root.width - department.width - selectDay.width
//        }

//        MyButton{
//            id: selectDay
//            Layout.minimumWidth: 50
//            Layout.minimumHeight: 50
//            anchors.right: parent.right
//            name: 'Select day'

//            states : State {
//                name: day; when: selectDay.pressed == true
//            }
//        }
    }

//    MyTextHolder{
//        Layout.fillHeight: true
//        title: 'Workers'
//        content: 'Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker Worker'
//    }
}

