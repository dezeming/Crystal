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
	along with this program.  If not, see <https://www.gnu.org/licenses/>.

	Github site: <https://github.com/dezeming/Crystal>
*/


/*
	This code is copy from <https://github.com/ThisIsClark/Qt-RangeSlider>

	The way to use this widget:

	rsH = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, nullptr);
		rsH->setMinimumSize(120,30);
		rsH->SetRange(0, 100);
		rsH->SetLowerValue(0);
		rsH->SetUpperValue(100);

	rsV = new RangeSlider(Qt::Vertical, RangeSlider::Option::DoubleHandles, nullptr);
	rsHsingleLeft = new RangeSlider(Qt::Horizontal, RangeSlider::Option::LeftHandle, nullptr);
	rsVsingleLeft = new RangeSlider(Qt::Vertical, RangeSlider::Option::LeftHandle, nullptr);
	rsHsingleRight = new RangeSlider(Qt::Horizontal, RangeSlider::Option::RightHandle, nullptr);
	rsVsingleRight = new RangeSlider(Qt::Vertical, RangeSlider::Option::RightHandle, nullptr);

*/

#ifndef __QSliderDoubleRange_hpp__
#define __QSliderDoubleRange_hpp__

#pragma once
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class QRangeSlider : public QWidget
{
	Q_OBJECT
		Q_ENUMS(QRangeSliderTypes)

public:
	enum Option {
		NoHandle = 0x0,
		LeftHandle = 0x1,
		RightHandle = 0x2,
		DoubleHandles = LeftHandle | RightHandle
	};
	Q_DECLARE_FLAGS(Options, Option)

	QRangeSlider(QWidget* aParent = Q_NULLPTR);
	QRangeSlider(Qt::Orientation ori, Options t = DoubleHandles, QWidget* aParent = Q_NULLPTR);

	QSize minimumSizeHint() const override;

	int GetMinimun() const;
	void SetMinimum(int aMinimum);

	int GetMaximun() const;
	void SetMaximum(int aMaximum);

	int GetLowerValue() const;
	void SetLowerValue(int aLowerValue);

	int GetUpperValue() const;
	void SetUpperValue(int aUpperValue);

	void SetRange(int aMinimum, int aMaximum);
	void SetTracking(bool enable);

protected:
	void paintEvent(QPaintEvent* aEvent) override;
	void mousePressEvent(QMouseEvent* aEvent) override;
	void mouseMoveEvent(QMouseEvent* aEvent) override;
	void mouseReleaseEvent(QMouseEvent* aEvent) override;
	void changeEvent(QEvent* aEvent) override;

	QRectF firstHandleRect() const;
	QRectF secondHandleRect() const;
	QRectF handleRect(int aValue) const;

signals:
	void lowerValueChanged(int aLowerValue);
	void upperValueChanged(int aUpperValue);
	void rangeChanged(int aMin, int aMax);

public slots:
	void setLowerValue(int aLowerValue);
	void setUpperValue(int aUpperValue);
	void setMinimum(int aMinimum);
	void setMaximum(int aMaximum);

private:
	Q_DISABLE_COPY(QRangeSlider)
	float currentPercentage();
	int validLength() const;

	int mMinimum;
	int mMaximum;
	int mLowerValue;
	int mUpperValue;
	bool mEnableTracking;
	bool mFirstHandlePressed;
	bool mSecondHandlePressed;
	int mInterval;
	int mDelta;
	QColor mBackgroudColorEnabled;
	QColor mBackgroudColorDisabled;
	QColor mBackgroudColor;
	Qt::Orientation orientation;
	Options type;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QRangeSlider::Options)



#endif





