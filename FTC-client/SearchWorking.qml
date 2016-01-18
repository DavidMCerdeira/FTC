import QtQuick 2.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import UserMessages 1.0


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
    }

    MyTextHolder{
        title{
            text: 'Result'
        }
        content_model: UserMessages
    }
}

