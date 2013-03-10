#include "Climate.hxx"
#include "MyWorldConfig.hxx"

namespace GujaratCellphones {

Climate::Climate(const MyWorldConfig & config ) : _randomGenerator((long int)config._climateSeed), _currentRain(0.0f), _uniformDistribution(_randomGenerator, boost::uniform_real <> (0,1))
{
	float mean = config._rainHistoricalDistribMean;
	float stddev = config._rainHistoricalDistribStdDev;

	_alphaRain = (mean*mean)/(stddev*stddev);
	_betaRain = mean/(stddev*stddev);
}

Climate::~Climate() {
}

void Climate::computeRainValue()
{
	boost::gamma_distribution<> gd(_alphaRain);
	boost::variate_generator<boost::mt19937&, boost::gamma_distribution<> >
	var_gamma(_randomGenerator, gd);
	_currentRain = var_gamma()*1.0/_betaRain;
}

const float & Climate::getRain() const {
	return _currentRain;
}

}