import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Grid {
    id: keyboard

    rows: 9
    columns: 5
    spacing: 1

    property var letterKeys: [
        'A', 'B', 'C', 'Ç', 'D',
        'E', 'F', 'G', 'H', 'I',
        'J', 'K', 'L', 'M', 'N',
        'O', 'P', 'Q', 'R', 'S',
        'T', 'U', 'V', 'X', 'Z',
        '123', '←', '┘', ' '
    ]

    property var numberKeys: [
        '0', '1', '2', '3', '4',
        '5', '6', '7', '8', '9',
        'abc', '←', '┘', ' '
    ]

    property var keys: letterKeys;

    signal hideKeyboard()
    signal letterClicked(string letter)

    Repeater {
        model: keys.length
        Button {
            width: 50; height: 50

            text: {
                if(index < keys.length){
                    return keys[(index)];
                }
            }

            style: ButtonStyle {
                label: Text{
                    anchors.centerIn: parent
                    color: {
                        if((keys[(index)] === '123') || (keys[(index)] === 'abc')){
                            'red'
                        }
                        else 'black'
                    }
                    text: {
                        if(index < keys.length){
                            return keys[(index)];
                        }
                    }
                }
            }


            onClicked: {
                if(text === '123'){
                    keys = numberKeys;
                }
                else if(text === 'abc'){
                    keys = letterKeys
                }
                else
                    letterClicked(text)
            }
        }
    }
}
