import QtQuick 2.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import SearchWorkingResult 1.0


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
        id: pre_results
        anchors.left: parent.left
        anchors.right: parent.right
        MyComboBox{
            id: department
            editable: false
            Layout.minimumWidth: 150
            Layout.minimumHeight: 40
        }

        Rectangle {
            id: spacer
            color: 'blue'
            width: root.width - department.width - selectDay.width
        }

        MyButton{
            id: selectDay
            anchors.right: parent.right
            name: 'Select day'
            checkable: true
            name_pointSize: 18
            Layout.minimumWidth: 150
            Layout.minimumHeight: 50
        }
    }

    Calendar {
        id: calendar
        weekNumbersVisible: true
        visible: false

        states : [
            State {
                name: 'showDays'
                when: selectDay.checked == true
                PropertyChanges {
                    target: calendar; visible: true
                }
            },
            State {
                name: 'noDays'
                    when: calendar.selectedDate === true
                    PropertyChanges {
                        target: selectDay;
                        checked: false
                    }
                    PropertyChanges {
                        target: calendar; visible: false
                    }
            }
        ]
    }

    MyTextHolder{
        title{
            text: 'Result'
        }
        content_model: SearchWorkingResult{}
    }
}

