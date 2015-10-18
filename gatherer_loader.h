#ifndef GATHERER_LOADER_GATHERER_LOADER_H
#define GATHERER_LOADER_GATHERER_LOADER_H

#include "Card.h"

// forward declarations
class CDocument;


namespace gatherer
{
Card load_single_card(CDocument & doc);
}

#endif
