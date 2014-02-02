#ifndef WATERTILE_H
#define WATERTILE_H

#include "maptile.h"
#include "waterchunk.h"

class WaterTile
{
public:
    WaterTile(MapTile* parentTil);
    WaterTile(MapTile* parentTile, QFile& file);
    ~WaterTile();

    WaterChunk* getChunk(int x, int y);

    bool hasData();

private:
    World* world;

    MapTile* tile;

    WaterChunk* chunks[CHUNKS][CHUNKS];

    friend class MapTile;
    friend class WaterChunk;
};

#endif // WATERTILE_H