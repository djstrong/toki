#ifndef AFFIXSPLITLAYER_H
#define AFFIXSPLITLAYER_H

#include "outputqueuelayer.h"

class AffixSplitLayer : public OutputQueueLayer
{
public:
    AffixSplitLayer(TokenSource* input, const Properties& props);
};

#endif // AFFIXSPLITLAYER_H
