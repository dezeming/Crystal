#include "QDoubleSlider.hpp"

QDoubleSlider::QDoubleSlider(QWidget* pParent) :
	QSlider(pParent),
	multiplier(10000.0)
{
	connect(this, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));

	setSingleStep(1);

	setOrientation(Qt::Horizontal);
	setFocusPolicy(Qt::NoFocus);
}

void QDoubleSlider::setValue(int Value)
{
	
	emit valueChanged((double)Value / multiplier);
}

void QDoubleSlider::setValue(double Value, bool BlockSignals)
{
	QSlider::blockSignals(BlockSignals);

	QSlider::setValue(Value * multiplier);

	if (!BlockSignals)
		emit valueChanged(Value);

	QSlider::blockSignals(false);
}

void QDoubleSlider::setRange(double Min, double Max)
{
	QSlider::setRange(Min * multiplier, Max * multiplier);

	emit rangeChanged(Min, Max);
}

void QDoubleSlider::setMinimum(double Min)
{
	QSlider::setMinimum(Min * multiplier);

	emit rangeChanged(minimum(), maximum());
}

double QDoubleSlider::minimum() const
{
	return QSlider::minimum() / multiplier;
}

void QDoubleSlider::setMaximum(double Max)
{
	QSlider::setMaximum(Max * multiplier);

	emit rangeChanged(minimum(), maximum());
}

double QDoubleSlider::maximum() const
{
	return QSlider::maximum() / multiplier;
}

double QDoubleSlider::value() const
{
	int Value = QSlider::value();
	return (double)Value / multiplier;
}

