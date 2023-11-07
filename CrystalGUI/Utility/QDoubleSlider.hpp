#pragma once
#ifndef __QDoubleSlider_H__
#define __QDoubleSlider_H__

#include <QSlider>

class QDoubleSlider : public QSlider {
	Q_OBJECT

public:
	QDoubleSlider(QWidget * parent = Q_NULLPTR);
	//~QDoubleSlider();

	/**
	* Note that when using, the parameters inside must be decimal
	* Otherwise, the integer setValue of the parent class will be called!
	*/ 
	void setRange(double Min, double Max);
	void setMinimum(double Min);
	double minimum() const;
	void setMaximum(double Max);
	double maximum() const;
	double value() const;

public slots:
	void setValue(int value);
	

public slots:

	/**
	* Note that when using, the parameters inside must be decimal
	* Otherwise, the integer setValue of the parent class will be called!
	*/
	void setValue(double Value, bool BlockSignals = false);

signals:
	void valueChanged(double Value);
signals:
	void rangeChanged(double Min, double Max);

private:
	double	multiplier;

private:
	
};

#endif



