import QtQuick 2.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import SearchEmployeeModel 1.0

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
        id: filtersTitle
        anchors.left: parent.left
        font.pointSize: 20
        text: 'Filter:'
    }

    Rectangle{
        anchors.horizontalCenter: parent.horizontalCenter
        Layout.fillWidth: true
        Layout.minimumHeight: nameInput.height + 20
        border.width: 2

        MouseArea{
            id: nameInputArea
            anchors.fill: parent

            onClicked: {
                keyboard.visible = !keyboard.visible
            }

            TextEdit{
                id: nameInput
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: ''
                font.pointSize: 16
            }
        }
    }

    Keyboard{
        id: keyboard
        visible: false

        Component.onCompleted: {
            keyboard.letterClicked.connect(letterPressed)
        }

        function letterPressed(letter){
            if(letter === '←'){
                nameInput.text = nameInput.text.substr(0, nameInput.text.length-1)
                nameInput.cursorPosition = nameInput.text.length
            }else if(letter === '┘'){
                keyboard.visible = false;
            }else{
                nameInput.insert(nameInput.length, letter);
            }
            console.log('Letter:' + letter);
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
        title{
            text: 'Result'
        }
        content_model: SearchEmployeeModel{ }
    }

    MyButton{
        anchors.horizontalCenter: parent.horizontalCenter
        name: 'Search'
        name_pointSize: 18
        Layout.minimumWidth: 150
        Layout.minimumHeight: 50
    }
}
