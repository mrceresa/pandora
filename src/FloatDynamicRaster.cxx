
/*
 * Copyright (c) 2012
 * COMPUTER APPLICATIONS IN SCIENCE & ENGINEERING
 * BARCELONA SUPERCOMPUTING CENTRE - CENTRO NACIONAL DE SUPERCOMPUTACIÓN
 * http://www.bsc.es

 * This file is part of Pandora Library. This library is free software; 
 * you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation;
 * either version 3.0 of the License, or (at your option) any later version.
 * 
 * Pandora is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include <FloatDynamicRaster.hxx>
#include <RasterLoader.hxx>
#include <Exception.hxx>
#include <Logger.hxx>

#include <sstream>
#include <limits>

#include <execinfo.h>

namespace Engine
{

FloatDynamicRaster::FloatDynamicRaster()
{
}

FloatDynamicRaster::~FloatDynamicRaster()
{
}

bool FloatDynamicRaster::operator==(const FloatDynamicRaster& other) const {
	return StaticRaster::operator==(other) &&
	       _currentMinValue == other._currentMinValue &&
	       _currentMaxValue == other._currentMaxValue &&
	       _maxValues == other._maxValues;
}

bool FloatDynamicRaster::operator!=(const FloatDynamicRaster& other) const {
	return !(*this == other);
}

void FloatDynamicRaster::resize( const Size<int> & size )
{
	StaticRaster::resize(size);
	_maxValues.resize(size._width);
	for(int i=0; i<size._width; i++)
	{
		_maxValues[i].resize(size._height);
	}
}

void FloatDynamicRaster::updateRasterIncrement()
/**
 *  I don't understand why someone would want to increment each turn!
 *  made it optional for now
 */
{

	if (not this->_disableAutoIncrement) {
		std::stringstream logName;
		logName << "FloatDynamicRaster::updateRasterIncrement()";
		log_INFO(logName.str(),  " we will comply and autoincrement!");
		for(size_t i=0; i<_values.size(); i++)
		{
			for(size_t j=0; j<_values[i].size(); j++)
			{
				if(_values.at(i).at(j) < _maxValues[i][j])
				{
					_values.at(i).at(j)++;
				}
			}
		}
	}
}

void FloatDynamicRaster::updateRasterToMaxValues()
{
	// std::copy is deep oriented.
	throw Exception("Not implemented for FloatDynamicRaster!");
	//std::copy(_maxValues.begin(), _maxValues.end(), _values.begin());
}

float FloatDynamicRaster::getMaxValue( const Point2D<int>& position ) const
{
	if(position._x<0 || position._x>=_maxValues.size())
	{
		std::stringstream oss;
		oss << "FloatDynamicRaster::getMaxValue - " << position << " x out of bounds: " << _maxValues.size();
		throw Exception(oss.str());
		return -1;
	}
	if(position._y<0 || position._y>=_maxValues[position._x].size())
	{
		std::stringstream oss;
		oss << "FloatDynamicRaster::getMaxValue - " << position << " y out of bounds: " << _maxValues.size() << "/" << _maxValues[position._x].size();
		throw Exception(oss.str());
		return -1;
	}	
	return _maxValues[position._x][position._y];
}

void FloatDynamicRaster::setValue( const Point2D<int>& position, float value )
{

	if(value>_maxValue)
	{
		std::stringstream oss;
		oss << "FloatDynamicRaster::setValue - value: " << value << " bigger than max value: " << _maxValue << " at position: " << position;
		throw Exception(oss.str());

		return;
	}
	if(position._x<0 || position._x>=_values.size())
	{
		std::stringstream oss;
		oss << "FloatDynamicRaster::setValue - " << position << " x out of bounds: " << _values.size();
		throw Exception(oss.str());

		return;
	}
	if(position._y<0 || position._y>=_values[position._x].size())
	{
		std::stringstream oss;
		oss << "FloatDynamicRaster::setValue - " << position << " y out of bounds: " << _values.size() << "/" << _values[position._x].size();
		throw Exception(oss.str());
		return;
	}
	if(value>_maxValues[position._x][position._y])
	{
		std::stringstream oss;
		oss << "FloatDynamicRaster::setValue - value: " << value << " bigger than max value: " << _maxValues[position._x][position._y] << " at position: " << position;
		throw Exception(oss.str());
	}
	_values[position._x][position._y] = value;
}

void FloatDynamicRaster::setMaxValue( const Point2D<int>& position, float value )
{
	if(value>_maxValue)
	{
		std::stringstream oss;
		oss << "FloatDynamicRaster::setMaxValue - value: " << value << " bigger than max value: " << _maxValue << " at pos: " << position;
		throw Exception(oss.str());

		return;
	}

	if(position._x<0 || position._x>=_maxValues.size())
	{
		std::stringstream oss;
		oss << "FloatDynamicRaster::setMaxValue- " << position << " x out of bounds: " << _maxValues.size();
		throw Exception(oss.str());

		return;
	}
	if(position._y<0 || position._y>=_maxValues[position._x].size())
	{
		std::stringstream oss;
		oss << "FloatDynamicRaster::setMaxValue- " << position << " y out of bounds: " << _maxValues.size() << "/" << _maxValues[position._x].size();
		throw Exception(oss.str());
		return;
	}	
	_maxValues[position._x][position._y] = value;
}

void FloatDynamicRaster::setMaxValue( const float & maxValue )
{
	_maxValue = maxValue;
}

void FloatDynamicRaster::setMinValue( const float & minValue )
{
	_minValue = minValue;
}

void FloatDynamicRaster::updateCurrentMinMaxValues()
{
	_currentMinValue = std::numeric_limits<float>::max();
	_currentMaxValue = std::numeric_limits<float>::min();
	for (size_t i = 0; i < _values.size(); i++  )
		for (size_t j = 0; j < _values[i].size(); j++ )
		{
			_currentMaxValue = ( _values[i][j] > _currentMaxValue ? _values[i][j] : _currentMaxValue );
			_currentMinValue = ( _values[i][j] < _currentMinValue ? _values[i][j] : _currentMinValue );
		}
}

void FloatDynamicRaster::setInitValues( float minValue, float maxValue, float defaultValue )
{
	_minValue = _currentMinValue = minValue;
	_maxValue = _currentMaxValue = maxValue;

	for(size_t i=0; i<_values.size(); i++)
	{
		for(size_t j=0; j<_values[i].size(); j++)
		{
			setMaxValue(Point2D<int>(i,j), _maxValue);
			setValue(Point2D<int>(i,j), defaultValue);			
		}
	}
}

} // namespace Engine

