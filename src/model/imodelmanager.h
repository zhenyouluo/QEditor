/*This file is part of QEditor.

QEditor is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

QEditor is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with QEditor.  If not, see <http://www.gnu.org/licenses/>.*/

#ifndef IMODELMANAGER_H
#define IMODELMANAGER_H

#include <QtCore>

#include "imodelinterface.h"
#include "itexturemanager.h"

struct IModelData
{
    IModelData(QString Category, QImage Image, IModelInterface* ModelInterface)
    {
        category       = Category;
        image          = Image;
        modelInterface = ModelInterface;
    }

    ~IModelData()
    {
        delete modelInterface;
    }

    QString category;
    QImage image;

    IModelInterface* modelInterface;
};

class IModelManager
{
public:
    IModelManager();
    ~IModelManager();

    bool isModelSelected() { return current >= 0; }

    bool loadModel(QString category, QString file);
    void loadModels(QString modelsDirectory);

    QVector<QString> getCategories();
    QVector<QString> getNames();
    QVector<QString> getNames(QString category);

    int getIndex(QString modelPath);
    int getCurrentModel() { return current; }

    IModelData*      getModel(int index);
    ITextureManager* getTextureManager();

    void setCurrentModel(int index) { current = index; }

private:
    ITextureManager* textureManager;

    QMap<QString, IModelData*> data;
    QVector<QString>           categories;

    int current;
};

#endif // IMODELMANAGER_H