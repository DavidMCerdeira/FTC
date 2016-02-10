import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import QtQuick.Controls.Private 1.0

Rectangle{
    color: 'pink'



        ListView{
            id: list
            clip: true
            focus: true

            highlight: Rectangle { color: "lightsteelblue"; radius: 5; y: list.currentItem.y  }
            anchors.fill: parent
            model: ListModel {
                id: cbItems
                ListElement { fruit: "Banana"; }
                ListElement { fruit: "Apple" }
                ListElement { fruit: "Coconut" }
            }
            delegate: Text{
                text: "lol" + fruit + "kek" + list.currentIndex
                font.pointSize: 18
            }
        }

        MouseArea{
            anchors.fill: parent
            id: mouseArea
            onClicked: {
                console.log("clicked")
                list.incrementCurrentIndex()
            }
        }

}
