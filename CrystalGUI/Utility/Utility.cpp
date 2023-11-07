/*
Copyright (C) <2023>  <Dezeming>  <feimos@mail.ustc.edu.cn>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or any
later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.

Github site: <https://github.com/dezeming/Crystal>
*/
#ifdef CRYSTAL_Using_Shared_Lib
#undef _EXPORTING
#endif

#include "Utility.hpp"

#include <QColorDialog>

namespace CrystalGUI {


FloatSetter::FloatSetter(QGroupBox* parent, QString Name, float min, float max) {

    layout = new QGridLayout;

    qpb = new QPushButton;
    slider = new QDoubleSlider;
    spinbox = new QDoubleSpinBox;

    slider->setMinimum((float)min);
    slider->setMaximum((float)max);
    spinbox->setMinimum((float)min);
    spinbox->setMaximum((float)max);

    qpb->setText(Name);

    layout->addWidget(qpb, 0, 0);
    layout->addWidget(slider, 0, 1);
    layout->addWidget(spinbox, 0, 2);

    setLayout(layout);

    connect(slider, SIGNAL(valueChanged(double)), spinbox, SLOT(setValue(double)));
    connect(spinbox, SIGNAL(valueChanged(double)), slider, SLOT(setValue(double)));
    connect(spinbox, SIGNAL(valueChanged(double)), this, SLOT(slot_valueChanged(double)));

}

FloatSetter::~FloatSetter() {
    disconnect(slider, 0, 0, 0);
    disconnect(spinbox, 0, 0, 0);
}

void FloatSetter::slot_valueChanged(double val) {
    value = val;
    emit signal_valueChanged(val);
}


RGBSetter::RGBSetter(QGroupBox* parent, QString Name) {

    layout = new QGridLayout;

    qpb = new QPushButton;
    qpb->setText(Name);

    frame = new QFrame;
    frame->setLineWidth(2);
    frame->setAutoFillBackground(true);
    frame->setFrameShape(QFrame::Box);
    
    layout->addWidget(qpb, 0, 0);
    layout->addWidget(frame, 0, 1);

    color.setRgb(126, 237, 13);
    QPalette palette(color);
    palette.setColor(QPalette::Window, color);
    frame->setPalette(palette);

    setLayout(layout);

    connect(qpb, SIGNAL(clicked()), this, SLOT(slot_setValue()));
    
}
RGBSetter::~RGBSetter() {

    disconnect(qpb, 0, 0, 0);
}

void RGBSetter::slot_valueChanged(const QColor& val) {
    color = val;

    value[0] = 1.0f / 255.0f * val.red();
    value[1] = 1.0f / 255.0f * val.green();
    value[2] = 1.0f / 255.0f * val.blue();

    QPalette palette(color);
    palette.setColor(QPalette::Window, color);
    frame->setPalette(palette);

    emit signal_valueChanged(color);
}
void RGBSetter::slot_setValue() {
    QColorDialog ColorDialog(color);
    connect(&ColorDialog, SIGNAL(currentColorChanged(const QColor&)), this, SLOT(slot_valueChanged(const QColor&)));
    ColorDialog.exec();
    disconnect(&ColorDialog, SIGNAL(currentColorChanged(const QColor&)), this, SLOT(slot_valueChanged(const QColor&)));
}


    /*

int main(void) {
    const int W_BLACK     = 0;
    const int W_BLUE      = 1;
    const int W_GREEN     = 2;
    const int W_RED       = 4;
    const int W_INTENSITY = 8;
    const int W_CYAN      = W_BLUE | W_GREEN;
    const int W_MAGENTA   = W_BLUE | W_RED;
    const int W_YELLOW    = W_GREEN | W_RED;
    const int W_WHITE     = W_BLUE | W_GREEN | W_RED;
    const int ANSI2WIN[]  = {W_BLACK, W_RED, W_GREEN, W_YELLOW, W_BLUE, W_MAGENTA, W_CYAN, W_WHITE};

    const int RESET   =  0;
    const int BOLD    =  1;
    const int BLACK   = 30;
    const int RED     = 31;
    const int GREEN   = 32;
    const int YELLOW  = 33;
    const int BLUE    = 34;
    const int MAGENTA = 35;
    const int CYAN    = 36;
    const int GRAY    = 37;
    const int WHITE   = 37;

    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
    int initialColor = consoleInfo.wAttributes;

    int state, ansiColor, multiplication, pos, winColor, winIntensity = -1;
    int colors[] = {-1,-1};
    int colorPos = 1;
    int ch;

    while ((ch = getchar()) != EOF) {
        if(ch == '\e') {
            state = '\e';
        } else if (state == '\e' && ch == '[') {
            state = '[';
        } else if (state == '[') {
            if (ch != 'm') {
                colors[colorPos] = ch;
                colorPos--;
            } else {
                // Find ANSI Color
                ansiColor = 0;
                multiplication = 1;
                for (pos = colorPos + 1; pos < 2; pos++) {
                    ansiColor += (colors[pos] - 48) * multiplication;
                    multiplication *= 10;
                }

                // Convert ANSI Color to Windows Color
                if (ansiColor == BOLD) {
                    winIntensity = W_INTENSITY;
                } else if (ansiColor == RESET) {
                    winIntensity = W_BLACK;
                    winColor = initialColor;
                } else if (BLACK <= ansiColor && ansiColor <= WHITE) {
                    winColor = ANSI2WIN[ansiColor - 30];
                } else if (ansiColor == 90) {
                    // Special case for gray (it's really white)
                    winColor = W_WHITE;
                    winIntensity = W_BLACK;
                }

                // initialColor & 0xF0 is to keep the background color
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), winColor | winIntensity | (initialColor & 0xF0));
                colorPos = 1;
                state = -1;
            }
        } else {
            putchar(ch);
        }
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), initialColor);
    return 0;
}

*/







}


