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


#include "QSliderDoubleRange.hpp"
#include <QDebug>

namespace
{

	const int scHandleSideLength = 11;
	const int scSliderBarHeight = 5;
	const int scLeftRightMargin = 1;

}

QRangeSlider::QRangeSlider(QWidget* aParent)
	: QWidget(aParent),
	mMinimum(0),
	mMaximum(100),
	mLowerValue(0),
	mUpperValue(100),
	mFirstHandlePressed(false),
	mSecondHandlePressed(false),
	mEnableTracking(true),
	mInterval(mMaximum - mMinimum),
	mBackgroudColorEnabled(QColor(0x1E, 0x90, 0xFF)),
	mBackgroudColorDisabled(Qt::darkGray),
	mBackgroudColor(mBackgroudColorEnabled),
	orientation(Qt::Horizontal)
{
	setMouseTracking(true);
}

QRangeSlider::QRangeSlider(Qt::Orientation ori, Options t, QWidget* aParent)
	: QWidget(aParent),
	mMinimum(0),
	mMaximum(100),
	mLowerValue(0),
	mUpperValue(100),
	mFirstHandlePressed(false),
	mSecondHandlePressed(false),
	mEnableTracking(true),
	mInterval(mMaximum - mMinimum),
	mBackgroudColorEnabled(QColor(0x1E, 0x90, 0xFF)),
	mBackgroudColorDisabled(Qt::darkGray),
	mBackgroudColor(mBackgroudColorEnabled),
	orientation(ori),
	type(t)
{
	setMouseTracking(true);
}

void QRangeSlider::paintEvent(QPaintEvent* aEvent)
{
	Q_UNUSED(aEvent);
	QPainter painter(this);

	// Background
	QRectF backgroundRect;
	if (orientation == Qt::Horizontal)
		backgroundRect = QRectF(scLeftRightMargin, (height() - scSliderBarHeight) / 2, width() - scLeftRightMargin * 2, scSliderBarHeight);
	else
		backgroundRect = QRectF((width() - scSliderBarHeight) / 2, scLeftRightMargin, scSliderBarHeight, height() - scLeftRightMargin * 2);

	QPen pen(Qt::gray, 0.8);
	painter.setPen(pen);
	// painter.setRenderHint(QPainter::QtCompatiblePainting);
	QBrush backgroundBrush(QColor(0xD0, 0xD0, 0xD0));
	painter.setBrush(backgroundBrush);
	painter.drawRoundedRect(backgroundRect, 1, 1);

	// First value handle rect
	pen.setColor(Qt::darkGray);
	pen.setWidth(0.5);
	painter.setPen(pen);
	painter.setRenderHint(QPainter::Antialiasing);
	QBrush handleBrush(QColor(0xFA, 0xFA, 0xFA));
	painter.setBrush(handleBrush);
	QRectF leftHandleRect = firstHandleRect();
	if (type.testFlag(LeftHandle))
		painter.drawRoundedRect(leftHandleRect, 2, 2);

	// Second value handle rect
	QRectF rightHandleRect = secondHandleRect();
	if (type.testFlag(RightHandle))
		painter.drawRoundedRect(rightHandleRect, 2, 2);

	// Handles
	painter.setRenderHint(QPainter::Antialiasing, false);
	QRectF selectedRect(backgroundRect);
	if (orientation == Qt::Horizontal) {
		selectedRect.setLeft((type.testFlag(LeftHandle) ? leftHandleRect.right() : leftHandleRect.left()) + 0.5);
		selectedRect.setRight((type.testFlag(RightHandle) ? rightHandleRect.left() : rightHandleRect.right()) - 0.5);
	}
	else {
		selectedRect.setTop((type.testFlag(LeftHandle) ? leftHandleRect.bottom() : leftHandleRect.top()) + 0.5);
		selectedRect.setBottom((type.testFlag(RightHandle) ? rightHandleRect.top() : rightHandleRect.bottom()) - 0.5);
	}
	QBrush selectedBrush(mBackgroudColor);
	painter.setBrush(selectedBrush);
	painter.drawRect(selectedRect);
}

QRectF QRangeSlider::firstHandleRect() const
{
	float percentage = (mLowerValue - mMinimum) * 1.0 / mInterval;
	return handleRect(percentage * validLength() + scLeftRightMargin);
}

QRectF QRangeSlider::secondHandleRect() const
{
	float percentage = (mUpperValue - mMinimum) * 1.0 / mInterval;
	return handleRect(percentage * validLength() + scLeftRightMargin + (type.testFlag(LeftHandle) ? scHandleSideLength : 0));
}

QRectF QRangeSlider::handleRect(int aValue) const
{
	if (orientation == Qt::Horizontal)
		return QRect(aValue, (height() - scHandleSideLength) / 2, scHandleSideLength, scHandleSideLength);
	else
		return QRect((width() - scHandleSideLength) / 2, aValue, scHandleSideLength, scHandleSideLength);
}

void QRangeSlider::mousePressEvent(QMouseEvent* aEvent)
{
	if (aEvent->buttons() & Qt::LeftButton)
	{
		int posCheck, posMax, posValue, firstHandleRectPosValue, secondHandleRectPosValue;
		posCheck = (orientation == Qt::Horizontal) ? aEvent->pos().y() : aEvent->pos().x();
		posMax = (orientation == Qt::Horizontal) ? height() : width();
		posValue = (orientation == Qt::Horizontal) ? aEvent->pos().x() : aEvent->pos().y();
		firstHandleRectPosValue = (orientation == Qt::Horizontal) ? firstHandleRect().x() : firstHandleRect().y();
		secondHandleRectPosValue = (orientation == Qt::Horizontal) ? secondHandleRect().x() : secondHandleRect().y();

		mSecondHandlePressed = secondHandleRect().contains(aEvent->pos());
		mFirstHandlePressed = !mSecondHandlePressed && firstHandleRect().contains(aEvent->pos());
		if (mFirstHandlePressed)
		{
			mDelta = posValue - (firstHandleRectPosValue + scHandleSideLength / 2);
		}
		else if (mSecondHandlePressed)
		{
			mDelta = posValue - (secondHandleRectPosValue + scHandleSideLength / 2);
		}

		if (posCheck >= 2
			&& posCheck <= posMax - 2)
		{
			int step = mInterval / 10 < 1 ? 1 : mInterval / 10;
			if (posValue < firstHandleRectPosValue)
				setLowerValue(mLowerValue - step);
			else if (((posValue > firstHandleRectPosValue + scHandleSideLength) || !type.testFlag(LeftHandle))
				&& ((posValue < secondHandleRectPosValue) || !type.testFlag(RightHandle)))
			{
				if (type.testFlag(DoubleHandles))
					if (posValue - (firstHandleRectPosValue + scHandleSideLength) <
						(secondHandleRectPosValue - (firstHandleRectPosValue + scHandleSideLength)) / 2)
						setLowerValue((mLowerValue + step < mUpperValue) ? mLowerValue + step : mUpperValue);
					else
						setUpperValue((mUpperValue - step > mLowerValue) ? mUpperValue - step : mLowerValue);
				else if (type.testFlag(LeftHandle))
					setLowerValue((mLowerValue + step < mUpperValue) ? mLowerValue + step : mUpperValue);
				else if (type.testFlag(RightHandle))
					setUpperValue((mUpperValue - step > mLowerValue) ? mUpperValue - step : mLowerValue);
			}
			else if (posValue > secondHandleRectPosValue + scHandleSideLength)
				setUpperValue(mUpperValue + step);
		}
	}
}

void QRangeSlider::mouseMoveEvent(QMouseEvent* aEvent)
{
	if (aEvent->buttons() & Qt::LeftButton)
	{
		int posValue, firstHandleRectPosValue, secondHandleRectPosValue;
		posValue = (orientation == Qt::Horizontal) ? aEvent->pos().x() : aEvent->pos().y();
		firstHandleRectPosValue = (orientation == Qt::Horizontal) ? firstHandleRect().x() : firstHandleRect().y();
		secondHandleRectPosValue = (orientation == Qt::Horizontal) ? secondHandleRect().x() : secondHandleRect().y();

		if (mFirstHandlePressed && type.testFlag(LeftHandle))
		{
			if (posValue - mDelta + scHandleSideLength / 2 <= secondHandleRectPosValue)
			{
				setLowerValue((posValue - mDelta - scLeftRightMargin - scHandleSideLength / 2) * 1.0 / validLength() * mInterval + mMinimum);
			}
			else
			{
				setLowerValue(mUpperValue);
			}
		}
		else if (mSecondHandlePressed && type.testFlag(RightHandle))
		{
			if (firstHandleRectPosValue + scHandleSideLength * (type.testFlag(DoubleHandles) ? 1.5 : 0.5) <= posValue - mDelta)
			{
				setUpperValue((posValue - mDelta - scLeftRightMargin - scHandleSideLength / 2 - (type.testFlag(DoubleHandles) ? scHandleSideLength : 0)) * 1.0 / validLength() * mInterval + mMinimum);
			}
			else
			{
				setUpperValue(mLowerValue);
			}
		}
	}
}

void QRangeSlider::mouseReleaseEvent(QMouseEvent* aEvent)
{
	Q_UNUSED(aEvent);
	int aHandleStateChangeIndex = 0;
	if (mFirstHandlePressed) aHandleStateChangeIndex = 1;
	else if (mSecondHandlePressed) aHandleStateChangeIndex = 2;
	mFirstHandlePressed = false;
	mSecondHandlePressed = false;
	if (aHandleStateChangeIndex == 1) setLowerValue(mLowerValue);
	else if (aHandleStateChangeIndex == 2) setUpperValue(mUpperValue);
}

void QRangeSlider::changeEvent(QEvent* aEvent)
{
	if (aEvent->type() == QEvent::EnabledChange)
	{
		if (isEnabled())
		{
			mBackgroudColor = mBackgroudColorEnabled;
		}
		else
		{
			mBackgroudColor = mBackgroudColorDisabled;
		}
		update();
	}
}

QSize QRangeSlider::minimumSizeHint() const
{
	return QSize(scHandleSideLength * 2 + scLeftRightMargin * 2, scHandleSideLength);
}

int QRangeSlider::GetMinimun() const
{
	return mMinimum;
}

void QRangeSlider::SetMinimum(int aMinimum)
{
	setMinimum(aMinimum);
}

int QRangeSlider::GetMaximun() const
{
	return mMaximum;
}

void QRangeSlider::SetMaximum(int aMaximum)
{
	setMaximum(aMaximum);
}

int QRangeSlider::GetLowerValue() const
{
	return mLowerValue;
}

void QRangeSlider::SetLowerValue(int aLowerValue)
{
	setLowerValue(aLowerValue);
}

int QRangeSlider::GetUpperValue() const
{
	return mUpperValue;
}

void QRangeSlider::SetUpperValue(int aUpperValue)
{
	setUpperValue(aUpperValue);
}

void QRangeSlider::setLowerValue(int aLowerValue)
{
	if (aLowerValue > mMaximum)
	{
		aLowerValue = mMaximum;
	}

	if (aLowerValue < mMinimum)
	{
		aLowerValue = mMinimum;
	}

	mLowerValue = aLowerValue;
	if (mEnableTracking) {
		emit lowerValueChanged(mLowerValue);
	}
	else if ((!mEnableTracking) && (!mFirstHandlePressed)) {
		emit lowerValueChanged(mLowerValue);
	}
	update();
}

void QRangeSlider::setUpperValue(int aUpperValue)
{
	if (aUpperValue > mMaximum)
	{
		aUpperValue = mMaximum;
	}

	if (aUpperValue < mMinimum)
	{
		aUpperValue = mMinimum;
	}

	mUpperValue = aUpperValue;
	if (mEnableTracking) {
		emit upperValueChanged(mUpperValue);
	}
	else if ((!mEnableTracking) && (!mSecondHandlePressed)) {
		emit upperValueChanged(mUpperValue);
	}
	update();
}

void QRangeSlider::setMinimum(int aMinimum)
{
	if (aMinimum <= mMaximum)
	{
		mMinimum = aMinimum;
	}
	else
	{
		int oldMax = mMaximum;
		mMinimum = oldMax;
		mMaximum = aMinimum;
	}
	mInterval = mMaximum - mMinimum;
	update();

	//setLowerValue(mMinimum);
	//setUpperValue(mMaximum);

	emit rangeChanged(mMinimum, mMaximum);
}

void QRangeSlider::setMaximum(int aMaximum)
{
	if (aMaximum >= mMinimum)
	{
		mMaximum = aMaximum;
	}
	else
	{
		int oldMin = mMinimum;
		mMaximum = oldMin;
		mMinimum = aMaximum;
	}
	mInterval = mMaximum - mMinimum;
	update();

	//setLowerValue(mMinimum);
	//setUpperValue(mMaximum);

	emit rangeChanged(mMinimum, mMaximum);
}

int QRangeSlider::validLength() const
{
	int len = (orientation == Qt::Horizontal) ? width() : height();
	return len - scLeftRightMargin * 2 - scHandleSideLength * (type.testFlag(DoubleHandles) ? 2 : 1);
}

void QRangeSlider::SetRange(int aMinimum, int mMaximum)
{
	setMinimum(aMinimum);
	setMaximum(mMaximum);
}

void QRangeSlider::SetTracking(bool enable) {
	mEnableTracking = enable;
}







