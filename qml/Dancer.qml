import QtQuick 2.0

Item {
    id: dancer
    //source: "../images/Dancer.png"

    width: 227
    height: 375

    LeftShoe {
        id: leftShoe
        x: 33
        y: 318
    }

    RightShoe{
        id: rightShoe
        x: 125
        y: 320
    }

    Body {
        id: body
        x: 57
        y: 113
    }

    LeftHand {
        id: leftHand
        x: 14
        y: 147
    }

    RightHand {
        id: rightHand
        x: 166
        y: 149
    }

    Necklace {
        id: necklace
        x: 70
        y: 138
    }

    Head {
        id: head
    }
}
