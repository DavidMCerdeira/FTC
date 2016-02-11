import QtQuick 2.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import SearchResultModel 1.0


ColumnLayout {
    id: root
    spacing: 5
    Layout.margins: 30

    signal search()


//    RowLayout{
//        id: pre_results
//        anchors.left: parent.left
//        anchors.right: parent.right

//        Calendar {
//            id: calendar
//            weekNumbersVisible: true
//            visible: false

//            states : [
//                State {
//                    name: 'showDays'
//                    when: selectDay.checked == true
//                    PropertyChanges {
//                        target: calendar; visible: true
//                    }

//                },
//                State {
//                    name: 'noDays'
//                    when: selectDay.checked == false
//                    PropertyChanges {
//                        target: calendar; visible: false
//                    }
////                    PropertyChanges {
////                        target: srchWrkngRslt;
////                        date: calendar.selectedDate;
////                    }
//                }
//            ]
//        }

//        MyButton{
//            id: selectDay
//            anchors.top: parent.top
//            anchors.right: parent.right
//            name: 'Select day'
//            checkable: true
//            name_pointSize: 18
//            Layout.minimumWidth: 130
//            Layout.minimumHeight: 50
//        }

//    }

    MyTextHolder{
        title{
            text: 'Result'
        }
        content_model: SearchResulModel{
            id: rslt
        }
    }

//    Connections{
//        target: rslt
//        onSearch: rslt.search()
//    }


    Component.onCompleted: {
       search.connect(startSearch)
    }

    function startSearch(){
        rslt.search();
    }

}

