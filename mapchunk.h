#ifndef MAPCHUNK_H
#define MAPCHUNK_H

#include <QOpenGLContext>
#include <QOpenGLFunctions_4_0_Core>
#include <QOpenGLBuffer>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include <QSharedPointer>
#include <QVector3D>
#include <QFile>

#include "material.h"
#include "world.h"

class MapChunk
{
public:
    MapChunk(World* mWorld, MapTile* tile, int x, int y);
    MapChunk(World* mWorld, MapTile* tile, QFile& file, int x, int y);
    ~MapChunk();

    bool isInVisibleRange(const float& distance, const QVector3D& camera) const;

    void draw();

    /// Terrain
    bool changeTerrain(float x , float z, float change         , const Brush* brush);
    bool flattenTerrain(float x, float z, float y, float change, const Brush* brush);
    bool blurTerrain(float x   , float z, float change         , const Brush* brush);

    bool paintTerrain(float x, float z, float flow, const Brush* brush, TexturePtr texture);

    /// Get
    const float getHeight(const float& x, const float& y) const;
    const float getHeight(const int& x, const int& y) const;
    const float getMapData(const int& index) const;

    const int chunkIndex() const;

    const QVector2D  getBases() const              { return QVector2D(baseX, baseY); }
    const GLuint&    getDisplaySubroutines() const { return displaySubroutines[world->displayMode()]; }
    const bool       getHighlight() const          { return highlight; }

    TexturePtr getTexture(int index) const
    {
        if(index >= MAX_TEXTURES)
            return TexturePtr(new Texture());

        return textures[index];
    }

    QOpenGLShaderProgramPtr getShader() const { return chunkMaterial->shader(); }

    //
    void moveAlphaMap(int index, bool up);
    void deleteAlphaMap(int index);

    /// Set
    enum Border
    {
        Horizontal = 0,
        Vertical   = 1
    };

    void setBorder(Border border, const QVector<QPair<int, float>>& data);

    void setBottomNeighbour(MapChunk* chunk);
    void setLeftNeighbour(MapChunk* chunk);

    void setHighlight(bool on);

    /// ...
    void save(MCNK* chunk);

    void test();

private:
    World* world;

    /// Terrain
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer            patchBuffer;

    QVector<float> positionData;

    int patchCount;

    ChunkMaterial* chunkMaterial;

    TexturePtr terrainData;
    SamplerPtr terrainSampler;

    TexturePtr textures[MAX_TEXTURES];
    TexturePtr alphaMaps[ALPHAMAPS];

    unsigned char* alphaMapsData[ALPHAMAPS];

    float* mapData;
    /// ----------------------------------

    /// Chunk data
    QVector<GLuint> displaySubroutines;

    int chunkX, chunkY;

    float baseX, baseY;
    float chunkBaseX, chunkBaseY;

    bool highlight;

    // Neighbour
    MapChunk* bottomNeighbour;
    MapChunk* leftNeighbour;
    /// ----------------------------------

    int horizToHMapSize(float position);
    float HMapSizeToHoriz(int position);

    void initialize();
};

#endif // MAPCHUNK_H