import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import QtQuick.Controls.Private 1.0

Rectangle{

    signal curItemChanged( int idx );

    property var thisModel: ListModel {
        id: cbItems
        ListElement { display: "Banana"; }
        ListElement { display: "Apple" }
        ListElement { display: "Coconut" }
        ListElement { display: "Coconut" }
        ListElement { display: "Coconut" }
        ListElement { display: "Coconut" }
    }

    ListView{
        id: list
        clip: true
        focus: true

        highlight: Rectangle { color: "lightgrey"; radius: 5; y: list.currentItem.y  }
        anchors.fill: parent
        model: thisModel
            delegate: Text{
                text: display
                font.pointSize: 18
                MouseArea{
                    anchors.fill: parent
                    id: mouseArea
                    onClicked: {
                        console.log("clicked")
                        list.currentIndex = index;
                        curItemChanged(index)
                    }
                }
            }
    }

    border.width: 2
}

//ComboBox{
//    //    id: box
//    //    currentIndex: 2
//    //    activeFocusOnPress: true
//    style: ComboBoxStyle {
//        id: comboBox
//        //        background: Rectangle {
//        //            id: rectCategory
//        //            radius: 5
//        //            border.width: 2
//        //            color: 'lightgrey'
//        //        }

//        background: RowLayout{
//            Rectangle {
//                Layout.fillWidth: true
//                Layout.fillHeight: true
//                id: rectCategory
//                radius: 5
//                border.width: 2
//                color: 'lightgrey'

//                Triangle {
//                    triangleWidth: 10
//                    triangleHeight: 10
//                    Layout.minimumWidth: triangleWidth
//                    Layout.minimumHeight: triangleHeight
//                    anchors.verticalCenter: parent.verticalCenter
//                    anchors.right: parent.right
//                    strokeStyle: 'black'
//                    fillStyle: 'black'
//                }
//                Rectangle{
//                    Layout.fillWidth: true
//                    Layout.fillHeight: true
//                    radius: 5
//                    border.width: 2
//                    color: 'lightgrey'
//                }
//            }

//        }

//        label: Text {
//            verticalAlignment: Text.AlignVCenter
//            horizontalAlignment: Text.AlignHCenter
//            font.pointSize: 15
//            color: "black"
//            text: control.currentText
//        }

//        // drop-down customization here
//        property Component __dropDownStyle: MenuStyle {
//            __maxPopupHeight: 600
//            __menuItemType: "comboboxitem"

//            frame: Rectangle {              // background
//                color: "lightgrey"
//                border.width: 2
//                smooth: true
//            }

//            itemDelegate.label:             // an item text
//                                            Text {
//                verticalAlignment: Text.AlignVCenter
//                horizontalAlignment: Text.AlignHCenter
//                font.pointSize: 15
//                text: styleData.text
//            }

//            itemDelegate.background: Rectangle {  // selection of an item
//                radius: 2
//                color: styleData.selected ? "Gray" : "transparent"
//            }

//            __scrollerStyle: ScrollViewStyle { }
//        }

//        //        property Component __popupStyle: Style {
//        //            property int __maxPopupHeight: 400
//        //            property int submenuOverlap: 0

//        //            property Component frame: Rectangle {
//        //                width: (parent ? parent.contentWidth : 0)
//        //                height: (parent ? parent.contentHeight : 0) + 2
//        //                border.color: "black"
//        //                property real maxHeight: 500
//        //                property int margin: 1
//        //            }

//        //            property Component menuItemPanel: Text {
//        //                text: "NOT IMPLEMENTED"
//        //                color: "red"
//        //                font {
//        //                    pixelSize: 14
//        //                    bold: true
//        //                }
//        //            }

//        //            property Component __scrollerStyle: null
//    }


//    model: ListModel {
//        id: cbItems
//        ListElement { text: "Banana"; }
//        ListElement { text: "Apple" }
//        ListElement { text: "Coconut" }
//    }
//}
