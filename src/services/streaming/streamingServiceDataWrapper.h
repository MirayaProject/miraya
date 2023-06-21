#ifndef STREAMINGSERVICEDATAWRAPPER_H
#define STREAMINGSERVICEDATAWRAPPER_H

#include <QString>

class StreamingServiceDataWrapper
{
public:
	virtual QString getMessage() = 0;
	virtual QString getUsername() = 0;
};

#endif // STREAMINGSERVICEDATAWRAPPER_H
