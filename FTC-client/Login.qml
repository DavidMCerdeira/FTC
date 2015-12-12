import QtQuick 2.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

ColumnLayout{
    id: login
    Layout.margins: 30
    height: parent.Height
    spacing: 5


    //    Rectangle
    //    {
    //        anchors.horizontalCenter: parent.horizontalCenter
    //        color: 'lightskyblue'
    //        width: parent.width
    //        height: parent.height
    //    }

    Text {
        text: 'Press the image after you\'re done!'
    }

    Rectangle {
        color: 'white'
        border.color: 'black'
        border.width: 2

        Layout.minimumWidth: 250
        Layout.minimumHeight: 250

        MouseArea{
            anchors.fill: parent
            onClicked: {
              Qt.quit()
            }
        }
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        id: recognitionStatus
        text: 'Facial recognition Status'
    }
    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        id: recognitionSuggestion
        verticalAlignment: Text.AlignVCenter
        text: "Stay still bitch!"
    }

    MyButton{
        Layout.minimumHeight: 50
        Layout.minimumWidth: 200
        name_pointSize: 18
        name: 'Clock In/Out'
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

