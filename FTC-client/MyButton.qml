import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Button{
    id: root

    property string name : ''
    property int name_pointSize: 12

    style: ButtonStyle {
        label: Text{
            color: 'Black'
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: name
            font.pointSize: name_pointSize
        }

        background: Rectangle {
            anchors.fill: parent
            border.width: 3
            border.color: "black"
            radius: 4

            gradient: Gradient {
                GradientStop { position: 0 ; color: control.pressed ? 'gray' : "lightgray" }
           }
        }
    }
}
