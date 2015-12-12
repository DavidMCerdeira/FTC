import QtQuick 2.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

ColumnLayout {
    id: root
    spacing: 5
    Layout.margins: 30

    Text{
        anchors.horizontalCenter: parent.horizontalCenter
        id: title
        font.pointSize: 24
        text: "Search Employee"
    }

    Text{
        anchors.left: parent.left
        id: filtersTitle
        font.pointSize: 20
        text: 'Filter:'
    }

    Rectangle{
        anchors.horizontalCenter: parent.horizontalCenter
        Layout.fillWidth: true
        Layout.minimumHeight: employeeName.height + 20
        border.width: 2

        TextEdit{
            Layout.fillWidth: true
            anchors.verticalCenter: parent.verticalCenter
            id: employeeName
            text: ' Name Surname'
            font.pointSize: 16
        }
    }

    MyComboBox{
        anchors.horizontalCenter: parent.horizontalCenter
        Layout.minimumWidth: 150
        Layout.minimumHeight: 40
        editable: false
    }

    MyComboBox{
        anchors.horizontalCenter: parent.horizontalCenter
        Layout.minimumWidth: 150
        Layout.minimumHeight: 40
        editable: false
    }

    MyTextHolder{
        Layout.fillHeight: true
        Layout.preferredHeight: parent.height
        title: 'Result:'
        content: 'Worker Worker Worker'
    }

    MyButton{
        anchors.horizontalCenter: parent.horizontalCenter
        name: 'Search'
        name_pointSize: 18
        Layout.minimumWidth: 150
        Layout.minimumHeight: 50
    }
}
